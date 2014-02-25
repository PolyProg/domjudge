<?php
/**
 * View the details of a specific printout
 *
 * $Id: printout.php 3632 2011-08-27 19:13:39Z eldering $
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

$pagename = basename($_SERVER['PHP_SELF']);

$id = (int)@$_REQUEST['id'];
if ( !empty($_GET['jid']) ) $jid = (int)$_GET['jid'];

// Also check for $id in claim POST variable as submissions.php cannot
// send the submission ID as a separate variable.
if ( is_array(@$_POST['claim']) ) {
	foreach( $_POST['claim'] as $key => $val ) $id = (int)$key;
}
if ( is_array(@$_POST['unclaim']) ) {
	foreach( $_POST['unclaim'] as $key => $val ) $id = (int)$key;
}

require('init.php');

$title = 'Printout '.@$id;

if ( ! $id ) error("Missing or invalid printout id");

$submdata = $DB->q('MAYBETUPLE SELECT s.teamid, s.sourcecode,
                    s.submittime, s.printed, s.delivered, c.cid, c.contestname,
                    t.name AS teamname
                    FROM printout s
                    LEFT JOIN team     t ON (t.login  = s.teamid)
                    LEFT JOIN contest  c ON (c.cid    = s.cid)
                    WHERE submitid = %i', $id);

if ( ! $submdata ) error ("Missing submission data");

// Headers might already have been included.
require_once(LIBWWWDIR . '/header.php');

echo "<h1>Printout ".$id;
if ( !$submdata['delivered'] ) {
	echo "</h1>\n\n";
} else {
	echo " (delivered)</h1>\n\n";
}

?>
<table>
<caption>Printout</caption>
<tr><td scope="row">Contest:</td><td>
	<a href="contest.php?id=<?php echo urlencode($submdata['cid'])?>">
	<?php echo htmlspecialchars($submdata['contestname'])?></a></td></tr>
<tr><td scope="row">Team:</td><td>
	<a href="team.php?id=<?php echo urlencode($submdata['teamid'])?>">
	<span class="teamid"><?php echo htmlspecialchars($submdata['teamid'])?></span>:
	<?php echo htmlspecialchars($submdata['teamname'])?></a></td></tr>
<tr><td scope="row">Submitted:</td><td><?php echo  htmlspecialchars($submdata['submittime']) ?></td></tr>
<tr><td scope="row">Printed:</td><td><?php echo  ($submdata['printed']?'yes':'no') ?></td></tr>
<tr><td scope="row">Delivered:</td><td><?php echo  ($submdata['delivered']?'yes':'no') ?></td></tr>
</table>
<hr />
<?php
require(LIBWWWDIR . '/highlight.php');
echo highlight_native($submdata['sourcecode'], 'txt');
echo '<hr />';

// We're done!

require(LIBWWWDIR . '/footer.php');
