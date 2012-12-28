<?php

/**
 * Scoreboard
 *
 * $Id$
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$refresh = '30;url=scoreboard.php';
$title = 'Scoreboard';
$printercss = TRUE;

// parse filter options
$filter = array();
if ( !isset($_GET['clear']) ) {
	foreach( array('affilid', 'country', 'categoryid') as $type ) {
		if ( !empty($_GET[$type]) ) $filter[$type] = $_GET[$type];
	}
	if ( count($filter) ) $refresh .= '?' . http_build_query($filter);
}

require(LIBWWWDIR . '/header.php');
require(LIBWWWDIR . '/scoreboard.php');

// call the general putScoreBoard function from scoreboard.php
putScoreBoard($cdata, NULL, FALSE, $filter);

$gl = array();
$loc = array();
//Print a little output for writing ranks to the website
foreach(array_keys($rank_by_team) as $key) {
  $loc[] = "$key=" . $rank_by_team[$key];
}
$gl[] = join($loc, '|');$loc=array();
foreach(array_keys($score_by_team) as $key) {
  $loc[] = "$key=" . $score_by_team[$key];
}
$gl[] = join($loc, '|');$loc=array();
foreach(array_keys($penalty_by_team) as $key) {
  $loc[] = "$key=" . $penalty_by_team[$key];
}
$gl[] = join($loc, '|');$loc=array();
foreach(array_keys($time_by_team) as $key) {
  $loc[] = "$key=" . $time_by_team[$key];
}
$gl[] = join($loc, '|');
$glres = join($gl, '@');
echo "<p style='color:silver'>Ranks/Score/Penalty/Time per team (for website)</p>";
echo "<p style='color:silver'>$glres</p>";

require(LIBWWWDIR . '/footer.php');
