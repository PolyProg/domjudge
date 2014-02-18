<?php

/**
 * Scoreboard
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

$pagename = basename($_SERVER['PHP_SELF']);

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
echo "<hr />";
echo "<h2>Export to HC2 website.</h2>";
echo "<p>This does a cross-site request. You must be logged into the HC2 admin website for this to work.</p>";
?>
<form method="post" action="http://hc2.ch/admin/ranks.php" target="_blank" >
<input value="<?php echo $glres;?>" name="data">
<input type="hidden" value="yes" name="confirm">
<input type="submit" value="Submit">
</form>
<?php

require(LIBWWWDIR . '/footer.php');
