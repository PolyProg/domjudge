<?php

/**
 * Common functions in jury interface
 *
 * $Id$
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

/**
 * Return a link to add a new row to a specific table.
 */
function addLink($table, $multi = false)
{
	return "<a href=\"" . htmlspecialchars($table) . ".php?cmd=add\">" .
		"<img src=\"../images/add" . ($multi?"-multi":"") .
		".png\" alt=\"add" . ($multi?" multiple":"") .
		"\" title=\"add" .   ($multi?" multiple":"") .
		" new " . htmlspecialchars($table) . "\" class=\"picto\" /></a>";
}

/**
 * Return a link to edit a specific data element from a given table.
 * Takes the table, the key field to match on and the value.
 * Includes a referrer field, which notes the page on which this function
 * was called, so edit.php can return us back here.
 */
function editLink($table, $value, $multi = false)
{
	return "<a href=\"" . htmlspecialchars($table) . ".php?cmd=edit" .
		($multi ? "" : "&amp;id=" . urlencode($value) ) .
		"&amp;referrer=" . urlencode(basename($_SERVER['SCRIPT_NAME']) .
		(empty($_REQUEST['id']) ? '' : '?id=' . urlencode($_REQUEST['id']))) .
		"\">" .
		"<img src=\"../images/edit" . ($multi?"-multi":"") .
		".png\" alt=\"edit" . ($multi?" multiple":"") .
		"\" title=\"edit " .   ($multi?"multiple ":"this ") .
		htmlspecialchars($table) . "\" class=\"picto\" /></a>";
}

/**
 * Return a link to delete a specific data element from a given table.
 * Takes the table, the key field to match on and the value.
 */
function delLink($table, $field, $value)
{
	return "<a href=\"delete.php?table=" . urlencode($table) . "&amp;" .
		$field . "=" . urlencode($value) ."\"><img src=\"../images/delete.png\" " .
		"alt=\"delete\" title=\"delete this " . htmlspecialchars($table) .
		"\" class=\"picto\" /></a>";
}

/**
 * Returns a form to rejudge all judgings based on a (table,id)
 * pair. For example, to rejudge all for language 'java', call
 * as rejudgeForm('language', 'java').
 */
function rejudgeForm($table, $id)
{
	$ret = addForm('rejudge.php') .
		addHidden('table', $table) .
		addHidden('id', $id);

	$button = 'REJUDGE this submission';
	$question = "Rejudge submission s$id?";
	$disabled = false;

	// special case submission
	if ( $table == 'submission' ) {

		// disable the form button if there are no valid judgings anyway
		// (nothing to rejudge) or if the result is already correct
		global $DB;
		$validresult = $DB->q('MAYBEVALUE SELECT result FROM judging WHERE
		                       submitid = %i AND valid = 1', $id);

		if ( IS_ADMIN ) {
			if ( ! $validresult ) {
				$question = "Restart judging of PENDING submission s$id, " .
					'are you sure?';
				$button = 'RESTART judging';
			} elseif ( $validresult == 'correct' ) {
				$question = "Rejudge CORRECT submission s$id, " .
					'are you sure?';
			}
		} else {
			if ( ! $validresult || $validresult == 'correct' ) {
				$disabled = true;
			}
		}
	} else {
		$button = "REJUDGE ALL for $table $id";
		$question = "Rejudge all submissions for this $table?";
	}

	$ret .= '<input type="submit" value="' . htmlspecialchars($button) . '" ' .
		($disabled ? 'disabled="disabled"' : 'onclick="return confirm(\'' .
		htmlspecialchars($question) . '\');"') . " />\n" . addEndForm();

	return $ret;
}


/**
 * Returns TRUE iff string $haystack ends with string $needle
 */
function ends_with($haystack, $needle) {
	return substr( $haystack, strlen( $haystack ) - strlen( $needle ) )
       		=== $needle;
}

/**
 * tries to open corresponding zip archive
 */
function openZipFile($filename) {
	$zip = new ZipArchive;
	$res = $zip->open($filename, ZIPARCHIVE::CHECKCONS);
	if ($res === ZIPARCHIVE::ER_NOZIP || $res === ZIPARCHIVE::ER_INCONS) {
		error("no valid zip archive given");
	} else if ($res === ZIPARCHIVE::ER_MEMORY) {
		error("not enough memory to extract zip archive");
	} else if ($res !== TRUE) {
		error("unknown error while extracting zip archive");
	}

	return $zip;
}

/**
 * Parse a configuration string
 * (needed if PHP version < 5.3)
 */
if (!function_exists('parse_ini_string')) {
	function parse_ini_string($ini, $process_sections = false, $scanner_mode = null) {
		# Generate a temporary file.
		$tempname = tempnam('/tmp', 'ini');
		$fp = fopen($tempname, 'w');
		fwrite($fp, $ini);
		$ini = parse_ini_file($tempname, !empty($process_sections));
		fclose($fp);
		@unlink($tempname);
		return $ini;
	}
}

/**
 * Read problem description file and testdata from zip archive
 * and update problem with it, or insert new problem when probid=NULL.
 * Returns probid on success, or generates error on failure.
 */
function importZippedProblem($zip, $probid = NULL)
{
        // Add multiple problems
        $probidfromzip = NULL;
        if($probid == NULL) {
              for ($j = 0; $j < $zip->numFiles; $j++) {
                  $filename = $zip->getNameIndex($j);
                  if ( ends_with($filename, ".zip") ) {
                      if ( !($tmpfname = mkstemps(TMPDIR."/subzip-XXXXXX",0)) ) {
                              error("Could not create temporary file.");
                      }
                      file_put_contents($tmpfname, $zip->getFromIndex($j));
                      $subzip = openZipFile($tmpfname);
                      $probidfromzip = importZippedProblem($subzip, NULL);
                      $subzip->close();
                      unlink($tmpfname);
                  }
              }
        }
        if($probidfromzip != NULL) {
          return $probidfromzip;
        }

	global $DB;
	$prop_file = 'domjudge-problem.ini';

	$ini_keys = array('probid', 'depends', 'cid', 'name', 'allow_submit', 'allow_judge',
	                  'timelimit', 'special_run', 'special_compare', 'library_prefix', 'color');

	$def_timelimit = 10;

	// Read problem properties
	$ini_array = parse_ini_string($zip->getFromName($prop_file));

	if ( empty($ini_array) ) {
		if ( $probid===NULL ) error("Need '" . $prop_file . "' file when adding a new problem.");
	} else {
		// Only preserve valid keys:
		$ini_array = array_intersect_key($ini_array,array_flip($ini_keys));

		if ( $probid===NULL ) {
			if ( !isset($ini_array['probid']) ) {
				error("Need 'probid' in '" . $prop_file . "' when adding a new problem.");
			}
			// Set sensible defaults for cid and name if not specified:
			if ( !isset($ini_array['cid'])       ) $ini_array['cid'] = getCurContest();
			if ( !isset($ini_array['name'])      ) $ini_array['name'] = $ini_array['probid'];
			if ( !isset($ini_array['timelimit']) ) $ini_array['timelimit'] = $def_timelimit;

			$DB->q('INSERT INTO problem (' . implode(', ',array_keys($ini_array)) .
			       ') VALUES (%As)', $ini_array);

			$probid = $ini_array['probid'];
		} else {
			// Remove keys that cannot be modified:
			unset($ini_array['probid']);
			unset($ini_array['cid']);

			$DB->q('UPDATE problem SET %S WHERE probid = %s', $ini_array, $probid);
		}
	}

	// Insert/update testcases
	$maxrank = 1 + $DB->q('VALUE SELECT max(rank) FROM testcase
	                       WHERE probid = %s', $probid);
	for ($j = 0; $j < $zip->numFiles; $j++) {
		$filename = $zip->getNameIndex($j);
		if ( ends_with($filename, ".in") ) {
			$basename = basename($filename, ".in");
			$fileout = $basename . ".out";
			$testout = $zip->getFromName($fileout);
			if ($testout !== FALSE) {
				$testin = $zip->getFromIndex($j);

				$DB->q('INSERT INTO testcase (probid, rank,
				        md5sum_input, md5sum_output, input, output, description)
				        VALUES (%s, %i, %s, %s, %s, %s, %s)',
				       $probid, $maxrank, md5($testin), md5($testout),
				       $testin, $testout, $basename);
				$maxrank++;
			}
		}
	}

	// submit reference solutions
	if ( isset($ini_array['allow_submit']) && $ini_array['allow_submit'] ) {
		// First find all submittable languages:
		$langs = $DB->q('KEYVALUETABLE SELECT langid AS extension, langid AS langid FROM language
		                 WHERE allow_submit = 1');

		for ($j = 0; $j < $zip->numFiles; $j++) {
			$filename = $zip->getNameIndex($j);
			$extension = end(explode(".", $filename));
			$langid = getLangID($extension);
			if( !empty($langid) && isset($langs[$langid]) ) {
				if ( !($tmpfname = mkstemps(TMPDIR."/ref_solution-XXXXXX",0)) ) {
					error("Could not create temporary file.");
				}
				file_put_contents($tmpfname, $zip->getFromIndex($j));
				if( filesize($tmpfname) <= SOURCESIZE*1024 ) {
					submit_solution('domjudge', $probid, $langs[$langid], $tmpfname);
				}
				unlink($tmpfname);
			}
		}
	}

	// FIXME: insert PDF into database

	return $probid;
}

/**
 * Reads jury member from POST variables, COOKIE's, returns $default if nothing is set.
 */
function getJuryMember($default = null)
{
	$jury_member = $default;
	if ( ! empty($_COOKIE['domjudge_jury_member']) ) $jury_member = $_COOKIE['domjudge_jury_member'];
	if ( ! empty($_POST['jury_member_selected']) ) $jury_member = $_POST['jury_member_selected'];
	if ( ! empty($_POST['jury_member_typed']) )    $jury_member = $_POST['jury_member_typed'];

	if ( !headers_sent() ) setJuryMember($jury_member);
	return $jury_member;
}

/**
 * Sets jury member in a cookie, only if a non-empty string is given.
 */
function setJuryMember($jury_member)
{
	// Set cookie of jury_member, expiry defaults to end of session.
	if ( !empty($jury_member) && is_string($jury_member) ) {
		if  (version_compare(PHP_VERSION, '5.2') >= 0) {
			// HTTPOnly Cookie, while this cookie is not security critical
			// it's a good habit to get into.
			setcookie('domjudge_jury_member', $jury_member, null, null, null, null, true);
		} else {
			setcookie('domjudge_jury_member', $jury_member);
		}
	}
}

/**
 * Add a both a text field and select box to select a jury member.
 */
function addJuryMemberSelect($default = null)
{
	global $DB;

	$jury_members = $DB->q('COLUMN SELECT DISTINCT jury_member FROM judging
	                     WHERE jury_member IS NOT NULL AND jury_member != ""
			     UNION
			     SELECT DISTINCT jury_member FROM clarification
			     WHERE jury_member IS NOT NULL AND jury_member != ""
	                     ORDER BY jury_member');

 	if ( empty($default) ) $default = null;
	if ( $default!==null && !in_array($default,$jury_members) ) $jury_members[] = $default;

	$res = addInput('jury_member_typed', '', 10, 15);
	if ( count($jury_members) > 0 ) {
		$opts = array(0 => "");
		$opts = array_merge($jury_members, $opts);
		$res .= ' or ' . addSelect('jury_member_selected', $opts, $default);
	}

	return $res;
}
