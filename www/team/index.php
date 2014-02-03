<?php
/**
 * $Id$
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$title = htmlspecialchars($teamdata['name']);
require(LIBWWWDIR . '/header.php');
require(LIBWWWDIR . '/forms.php');

$cid = $cdata['cid'];
$now = now();
$cstarted = difftime($cdata['starttime'],$now) <= 0;

// Don't use HTTP meta refresh, but javascript: otherwise we cannot
// cancel it when the user starts editing the submit form. This also
// provides graceful degradation without javascript present.
$refreshtime = 30;

$submitted = @$_GET['submitted'];
$printed = @$_GET['printed'];

#FIXME: JavaScript must be in page <head>
echo "<script type=\"text/javascript\">\n<!--\n";
echo "function getMainExtension(ext)\n{\n";
echo "\tswitch(ext) {\n";
foreach($langexts as $ext => $langid) {
	echo "\t\tcase '" . $ext . "': return '" . $langid . "';\n";
}
echo "\t\tdefault: return '';\n\t}\n}\n\n";
echo "initReload(" . $refreshtime . ");\n";
echo "// -->\n</script>\n";

// Put overview of team submissions (like scoreboard)
putTeamRow($cdata, array($login));

echo "<div id=\"submitlist\">\n";

echo "<h3 class=\"teamoverview\">Submissions</h3>\n\n";

if ( ENABLE_WEBSUBMIT_SERVER && $cstarted ) {
	if ( $submitted ) {
		echo "<p class=\"submissiondone\">submission done <a href=\"./\" style=\"color: red\">x</a></p>\n\n";
	} else if ( $printed) {
		echo "<p class=\"submissiondone\">printout queued <a href=\"./\" style=\"color: red\">x</a></p>\n\n";
	} else {
		echo addForm('upload.php','post',null,'multipart/form-data', null, ' onreset="resetUploadForm('.$refreshtime .');"') .
		"<p id=\"submitform\">\n\n" .
		"<span class=\"fileinputs\">\n\t" .
		"<input type=\"file\" name=\"code\" id=\"code\" size=\"15\" /> " .
		"\n</span>\n";

		echo "<script type=\"text/javascript\">initFileUploads();</script>\n\n";

		$probs = $DB->q('KEYVALUETABLE SELECT probid, CONCAT(probid) as name FROM problem
				 WHERE cid = %i AND allow_submit = 1
				 ORDER BY probid', $cid);
		$probs[''] = 'problem';

		echo addSelect('probid', $probs, '', true);
		$langs = $DB->q('KEYVALUETABLE SELECT langid, name FROM language
				 WHERE allow_submit = 1 ORDER BY name');
		$langs[''] = 'language';
		echo addSelect('langid', $langs, '', true);

		echo addSubmit('submit', 'submit',
			       "return checkUploadFormSubmit();");
		echo addSubmit('print', 'print',
			       "return checkUploadFormPrint();");

		echo addReset('cancel');

		echo "</p>\n</form>\n\n";
	}
}
// call putSubmissions function from common.php for this team.
$restrictions = array( 'teamid' => $login );
putSubmissions($cdata, $restrictions, null, $submitted);

echo "</div>\n\n";

echo "<div id=\"clarlist\">\n";

$requests = $DB->q('SELECT * FROM clarification
                    WHERE cid = %i AND sender = %s
                    ORDER BY submittime DESC, clarid DESC', $cid, $login);

$clarifications = $DB->q('SELECT c.*, u.type AS unread FROM clarification c
                          LEFT JOIN team_unread u ON
                          (c.clarid=u.mesgid AND u.type="clarification" AND u.teamid = %s)
                          WHERE c.cid = %i AND c.sender IS NULL
                          AND ( c.recipient IS NULL OR c.recipient = %s )
                          ORDER BY c.submittime DESC, c.clarid DESC',
                          $login, $cid, $login);

echo "<h3 class=\"teamoverview\">Clarifications</h3>\n";

# FIXME: column width and wrapping/shortening of clarification text 
if ( $clarifications->count() == 0 ) {
	echo "<p class=\"nodata\">No clarifications.</p>\n\n";
} else {
	putClarificationList($clarifications,$login);
}

echo "<h3 class=\"teamoverview\">Clarification Requests</h3>\n";

if ( $requests->count() == 0 ) {
	echo "<p class=\"nodata\">No clarification requests.</p>\n\n";
} else {
	putClarificationList($requests,$login);
}

echo addForm('clarification.php','get') .
	"<p>" . addSubmit('request clarification') . "</p>" .
	addEndForm();


echo "</div>\n";

require(LIBWWWDIR . '/footer.php');
