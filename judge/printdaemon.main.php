<?php
/**
 * Request a yet unprinted printout from the database, print it and
 * update the database.
 * 
 * You must not run several copies of this program at the same time,
 * else you might end up with duplicate printouts.
 *
 * $Id: printdaemon.main.php 3724 2011-11-09 13:36:59Z kink $
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */
if ( isset($_SERVER['REMOTE_ADDR']) ) die ("Commandline use only");

require(ETCDIR . '/judgehost-config.php');

// Set environment variables for passing path configuration to called programs
putenv('DJ_BINDIR='      . BINDIR);
putenv('DJ_ETCDIR='      . ETCDIR);
putenv('DJ_JUDGEDIR='    . JUDGEDIR);
putenv('DJ_LIBDIR='      . LIBDIR);
putenv('DJ_LIBJUDGEDIR=' . LIBJUDGEDIR);
putenv('DJ_LOGDIR='      . LOGDIR);

// Set other configuration variables for called programs
putenv('RUNUSER='       . RUNUSER);
putenv('USE_CHROOT='    . (USE_CHROOT ? '1' : ''));
putenv('CHROOT_SCRIPT=' . CHROOT_SCRIPT);
putenv('COMPILETIME='   . COMPILETIME);
putenv('MEMLIMIT='      . MEMLIMIT);
putenv('FILELIMIT='     . FILELIMIT);
putenv('PROCLIMIT='     . PROCLIMIT);

foreach ( $EXITCODES as $code => $name ) {
	$var = 'E_' . strtoupper(str_replace('-','_',$name));
	putenv($var . '=' . $code);
}

$waittime = 5;

$myhost = trim(`hostname | cut -d . -f 1`);

define ('SCRIPT_ID', 'printdaemon');
define ('LOGFILE', LOGDIR.'/printdaemon.'.$myhost.'.log');
define ('PIDFILE', RUNDIR.'/printdaemon.pid');

// Pass SYSLOG variable via environment for compare program
if ( defined('SYSLOG') && SYSLOG ) putenv('DJ_SYSLOG=' . SYSLOG);

require(LIBDIR . '/init.php');

function usage()
{
	echo "Usage: " . SCRIPT_ID . " [OPTION]...\n" .
	    "Start the printdaemon.\n\n" .
	    "  -d       daemonize after startup\n" .
	    "  -v       set verbosity to LEVEL (syslog levels)\n" .
	    "  -m       Don't print, just output ps files\n" .
	    "  -h       display this help and exit\n" .
	    "  -V       output version information and exit\n\n";
	exit;
}

$options = getopt("dmv:hV");
// FIXME: getopt doesn't return FALSE on parse failure as documented!
if ( $options===FALSE ) {
	echo "Error: parsing options failed.\n";
	usage();
}
if ( isset($options['d']) ) $options['daemon']  = $options['d'];
if ( isset($options['m']) ) $options['mock']  = $options['m'];
if ( isset($options['v']) ) $options['verbose'] = $options['v'];

if ( isset($options['V']) ) version();
if ( isset($options['h']) ) usage();

setup_database_connection('jury');

$verbose = LOG_INFO;
if ( isset($options['verbose']) ) $verbose = $options['verbose'];

if ( DEBUG & DEBUG_JUDGE ) {
	$verbose = LOG_DEBUG;
	putenv('DEBUG=1');
}

system("pgrep -u ".RUNUSER, $retval);
if ($retval == 0) {
	error("Still some processes by ".RUNUSER." found, aborting");
}
if ($retval != 1) {
	error("Error while checking processes for user " . RUNUSER);
}

logmsg(LOG_NOTICE, "Judge started on $myhost [DOMjudge/".DOMJUDGE_VERSION."]");

// Tick use required between PHP 4.3.0 and 5.3.0 for handling signals,
// must be declared globally.
if ( version_compare(PHP_VERSION, '5.3', '<' ) ) {
	declare(ticks = 1);
}
initsignals();

if ( isset($options['daemon']) ) daemonize(PIDFILE);

database_retry_connect($waittime);

$first = True;
while( !$exitsignalled )
{
	try {
		// Retrieve hostname and check database for judgehost entry
		$row = $DB->q('MAYBETUPLE SELECT * FROM judgehost WHERE hostname = %s'
		             , $myhost);
		if ( ! $row ) {
			if($first)
				logmsg(LOG_WARNING, "No database entry found for me ($myhost)");
			$first = False;
			sleep($waittime);
			continue;
		}
		$myhost = $row['hostname'];
		unset($first);
		break;
	}
	catch( Exception $e ) {
		$msg = "MySQL server has gone away";
		if( ! strncmp($e->getMessage(), $msg, strlen($msg)) ) {
			logmsg(LOG_WARNING, $msg);
			database_retry_connect();
			continue;
		}
		throw $e;
	}
}

// Create directory where to test submissions
$workdirpath = JUDGEDIR . "/$myhost" . "-printouts";
system("mkdir -p $workdirpath", $retval);
if ( $retval != 0 ) error("Could not create $workdirpath");

$waiting = FALSE;
$active = TRUE;
$cid = null;

// Constantly check database for unjudged submissions
while ( TRUE ) {

	// Check whether we have received an exit signal
	if ( function_exists('pcntl_signal_dispatch') ) pcntl_signal_dispatch();
	if ( $exitsignalled ) {
		logmsg(LOG_NOTICE, "Received signal, exiting.");
		exit;
	}

	try {
		// Check that this judge is active, else wait and check again later
		$row = $DB->q('TUPLE SELECT * FROM judgehost WHERE hostname = %s'
		             , $myhost);
		$DB->q('UPDATE LOW_PRIORITY judgehost SET polltime = NOW()
		       WHERE hostname = %s', $myhost);
	}
	catch( Exception $e ) {
		$msg = "MySQL server has gone away";
		if( ! strncmp($e->getMessage(), $msg, strlen($msg)) ) {
			logmsg(LOG_WARNING, $msg);
			database_retry_connect();
			continue;
		}
		throw $e;
	}

	if ( $row['active'] != 1 ) {
		if ( $active ) {
			logmsg(LOG_NOTICE, "Not active, waiting for activation...");
			$active = FALSE;
		}
		sleep($waittime);
		continue;
	}
	if ( ! $active ) {
		logmsg(LOG_INFO, "Activated, checking print queue...");
		$active = TRUE;
		$waiting = FALSE;
	}

	$contdata = getCurContest(TRUE);
	$newcid = $contdata['cid'];
	$oldcid = $cid;
	if ( $oldcid !== $newcid ) {
		logmsg(LOG_NOTICE, "Contest has changed from " .
		       (isset($oldcid) ? "c$oldcid" : "none" ) . " to " .
		       (isset($newcid) ? "c$newcid" : "none" ) );
		$cid = $newcid;
	}

	// First, use a select to see whether there are any judgeable
	// submissions. This query is query-cacheable, and doing a select
	// first prevents a write-lock on the submission table if nothing is
	// to be judged, and also prevents throwing away the query cache every
	// single time
	$numopen = $DB->q('VALUE SELECT COUNT(*) FROM printout where printed = 0');

	// nothing updated -> no open submissions
	if ( $numopen == 0 ) {
		if ( ! $waiting ) {
			logmsg(LOG_INFO, "No printouts in queue, waiting...");
			$waiting = TRUE;
		}
		sleep($waittime);
		continue;
	}

	// we have marked a submission for judging
	$waiting = FALSE;

	// get maximum runtime, source code and other parameters
	$row = $DB->q('TUPLE SELECT *
                       FROM printout p
                       LEFT JOIN team t ON (t.login  = p.teamid)
                       WHERE printed = 0
                       LIMIT 1');

	logmsg(LOG_INFO, "Printing $row[submitid]");

	doprint($row);

	// restart the judging loop
}

function doprint($row)
{
	global $DB, $workdirpath, $options;
        $id = $row['submitid'];

        $body = $row['sourcecode'];

	$srcfile = "$workdirpath/$id.txt";
	if ( file_put_contents($srcfile, $body) === FALSE ) {
		error("Could not create $srcfile");
	}
	unset($row['sourcecode']);
	unset($body);

	$commandline = "/usr/bin/a2ps" .
                       " -a1-20" .
                       " -2" .
                       " -f8" .
                       " -s2" .
                       " --header" .
                       " --left-title=" . escapeshellarg($row['room']) .
                       " --center-title=" . escapeshellarg($row['login'] . ' - ' . substr($row['name'], 0, 12)) .
                       " --footer=" . escapeshellarg($row['submittime']) .
                       " --left-footer=" . escapeshellarg($row['name']) .
                       " --right-footer=" . escapeshellarg('ID: ' . $row['submitid']) .
                       " ". escapeshellarg($srcfile);

        if ( isset($options["mock"]) ) {
          $commandline .= " -o " . escapeshellarg($srcfile . ".ps");
        }

        system($commandline, $retval);
        if ($retval == 0) {
          $row = $DB->q('UPDATE printout
                         SET printed = 1
                         WHERE submitid = %i',
                         $id);
        } else {
            logmsg(LOG_WARNING, "Can't print $id.");
        }
}

function database_retry_connect()
{
	global $DB, $exitsignalled, $waittime;

	$first = True;
	while( !$exitsignalled )
	{
		try {
			$DB->reconnect();
			logmsg(LOG_INFO, "Connected to database");
			break;
		}
		catch( Exception $e ) {
			$msg = "Could not connect to database server";
			if( ! strncmp($e->getMessage(), $msg, strlen($msg)) ) {
				if($first) logmsg(LOG_WARNING, $msg);
				$first = False;
				sleep($waittime);
				continue;
			}
			throw $e;
		}
	}
}
