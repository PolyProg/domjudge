<?php
/**
 * Download problem as zip archive.
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');

$id = $_GET['id'];
if ( !isset($id) ) {
	error("No problem id given.");
}

$ini_keys = array('probid', 'name', 'timelimit', 'special_run',
		  'special_compare', 'color', 'depends');

$problem = $DB->q('MAYBETUPLE SELECT problemtext, problemtext_type, problemdata, problemdata_type, problemlib, problemlib_type, ' .
                 join(',', $ini_keys) . ' FROM problem p WHERE probid = %s',$id);
if ( empty($problem) ) error ("Problem $id not found");

$inistring = "";
foreach ($ini_keys as $ini_val) {
	if ( !empty($problem[$ini_val]) ) {
		$inistring .= $ini_val . "='" . $problem[$ini_val] . "'\n";
	}
}

$zip = new ZipArchive;
if ( !($tmpfname = mkstemps(TMPDIR."/export-XXXXXX",0)) ) {
	error("Could not create temporary file.");
}

$res = $zip->open($tmpfname, ZipArchive::OVERWRITE);
if ( $res !== TRUE ) {
	error("Could not create temporary zip file.");
}
$zip->addFromString('domjudge-problem.ini', $inistring);

if ( !empty($problem['problemtext']) ) {
	$zip->addFromString('problem.'.$problem['problemtext_type'], $problem['problemtext']);
	unset($problem['problemtext']);
}
if ( !empty($problem['problemdata']) ) {
	$zip->addFromString('data.'.$problem['problemdata_type'], $problem['problemdata']);
	unset($problem['problemdata']);
}
if ( !empty($problem['problemlib']) ) {
	$zip->addFromString('library.'.$problem['problemlib_type'], $problem['problemlib']);
	unset($problem['problemlib']);
}

$testcases = $DB->q('SELECT description, testcaseid, rank FROM testcase
		     WHERE probid = %s ORDER BY rank', $id);
while ($tc = $testcases->next()) {
	$fname = $id . "_" . $tc['rank'] .
	         (empty($tc['description'])?"":"_".$tc['description']);
	foreach(array('in','out') as $inout) {
		$content = $DB->q("VALUE SELECT SQL_NO_CACHE " . $inout . "put FROM testcase
				   WHERE testcaseid = %i", $tc['testcaseid']);
		$curfname = preg_replace('/[^A-Za-z0-9]/', '_', $fname) .  '.' . $inout;
		$zip->addFromString($curfname, $content);
		unset($content);
	}
}
$zip->close();

header("Content-Description: File Transfer");
header("Content-Disposition: attachment; filename=" . $id . ".zip");
header("Content-Type: application/zip");
header("Content-Length: " . filesize($tmpfname) . "\n\n");
header("Content-Transfer-Encoding: binary");

readfile($tmpfname);
unlink($tmpfname);
