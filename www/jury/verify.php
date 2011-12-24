<?php
/**
 * Change the verification status of a given judging.
 *
 * $Id: verify.php 3487 2010-12-05 12:17:52Z eldering $
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$id    = @$_POST['id'];
$val   = @$_POST['val'];
if ( empty($id) ) error("No judging ID passed to mark as verified.");

$jury_member = getJuryMember();

// Explicitly unset jury_member when unmarking verified: otherwise this
// judging would be marked as "claimed".
$cnt = $DB->q('RETURNAFFECTED UPDATE judging
               SET verified = %i, jury_member = ' . ($val ? '%s ' : 'NULL %_ ') .
              'WHERE judgingid = %i',
              $val, $jury_member, $id);

if ( $cnt == 0 ) {
	error("Judging '$id' not found or nothing changed.");
} else if ( $cnt > 1 ) {
	error("Validated more than one judging.");
}

$jdata = $DB->q('TUPLE SELECT s.submitid, s.cid, s.teamid, s.probid, s.langid
                 FROM judging j
                 LEFT JOIN submission s USING (submitid)
                 WHERE judgingid = %i', $id);

if ( VERIFICATION_REQUIRED ) {
	calcScoreRow($jdata['cid'], $jdata['teamid'], $jdata['probid']);

	// log to event table (case of no verification required is handled
	// in judge/judgedaemon)
	$DB->q('INSERT INTO event (eventtime, cid, teamid, langid, probid, submitid, description)
	        VALUES (%s, %i, %i, %s, %s, %i, "problem judged")',
	       now(), $jdata['cid'], $jdata['teamid'], $jdata['langid'],
	       $jdata['probid'], $jdata['submitid']);
}

/* redirect back to submission page or submissions overview depending
 * on whether judging was (un)verified. */
if ( $val ) {
	header('Location: submissions.php');
} else {
	header('Location: submission.php?id=' .
	       urlencode($jdata['submitid']) . '&jid=' . urlencode($id));
}
