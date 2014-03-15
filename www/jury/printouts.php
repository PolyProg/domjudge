<?php
/**
 * Tool to coordinate the handing out of printouts to teams.
 *
 * $Id: printouts.php 3494 2010-12-10 23:23:59Z eldering $
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$title = 'Printout Status';

if ( isset($_POST['done']) ) {
	foreach($_POST['done'] as $done => $dummy) {
		$parts = explode(';', $done);
		$DB->q('UPDATE printout SET delivered=1
			WHERE submitid = %i',
			$parts[0]);
	}
	header('Location: printouts.php');
}

$viewall = TRUE;

// Restore most recent view from cookie (overridden by explicit selection)
if ( isset($_COOKIE['domjudge_printviewall']) ) {
	$viewall = $_COOKIE['domjudge_printviewall'];
}

// Did someone press the view button?
if ( isset($_REQUEST['viewall']) ) $viewall = $_REQUEST['viewall'];

// Set cookie of submission view type, expiry defaults to end of session.
if ( version_compare(PHP_VERSION, '5.2') >= 0 ) {
	// HTTPOnly Cookie, while this cookie is not security critical
	// it's a good habit to get into.
	setcookie('domjudge_printviewall', $viewall, null, null, null, null, true);
} else {
	setcookie('domjudge_printviewall', $viewall);
}

$refresh = '30;url=printouts.php';
require(LIBWWWDIR . '/header.php');

echo "<h1>Printout Status</h1>\n\n";

if ( isset($cdata['freezetime']) &&
     time() > strtotime($cdata['freezetime']) ) {
	echo "<h4>Scoreboard is now frozen.</h4>\n\n";
}

echo addForm('printouts.php', 'get') . "<p>\n" .
    addHidden('viewall', ($viewall ? 0 : 1)) .
    addSubmit($viewall ? 'view undelivered' : 'view all') . "</p>\n" .
    addEndForm();

// Problem metadata: colours and names.
$probs_data = $DB->q('KEYTABLE SELECT probid AS ARRAYKEY,name,color
		      FROM problem WHERE cid = %i', $cid);

// Get all relevant info
$res = $DB->q('SELECT s.*, t.login, t.name AS teamname, t.room, c.name AS catname
               FROM printout s
               LEFT JOIN team t ON (t.login = s.teamid)
               LEFT JOIN team_category c USING(categoryid)
               WHERE s.cid = %i
               ORDER BY s.delivered, s.printed, s.submittime',
              $cid);

/* Loop over the result, store the total of balloons for a team
 * (saves a query within the inner loop).
 * We need to store the rows aswell because we can only next()
 * once over the db result.
 */
$BALLOONS = $TOTAL_BALLOONS = array();
while ( $row = $res->next() ) {
	$BALLOONS[] = $row;
	$TOTAL_BALLOONS[$row['login']][] = $row['probid'];
}

$conteststart  = strtotime($cdata['starttime']);
if ( !empty($cdata['freezetime']) ) {
	$contestfreeze = strtotime($cdata['freezetime']);
}

if ( !empty($BALLOONS) ) {
	echo addForm('printouts.php');

	echo "<table class=\"list sortable balloons\">\n<thead>\n" .
		"<tr><th>ID</th><th>Time</th><th>Printed</th><th>Delivered</th><th align=\"left\">Team</th>\n" .
		"<th></th><th>Room</th><th>Category</th><th></th></tr>\n</thead>\n";

	foreach ( $BALLOONS as $row ) {
		$link = '<a href="printout.php?id=' . $row['submitid'] . '">';
		$begintd = '<td>' . $link;
		$endtd = '</td>';

		if ( !$viewall && $row['delivered'] == 1 ) continue;

		// start a new row, 'disable' if balloon has been handed out already
		echo '<tr'  . ( $row['delivered'] == 1 ? ' class="disabled"' : '' ) . '>';

		echo $begintd . $row['submitid'] . $endtd;

		// Was the printout printed?
		$balloontime = $row['submittime'];

		echo $begintd . $balloontime . $endtd;

                $printedyesno = $row['printed'] ? 'yes' : 'no';
                $printedcol = $row['printed'] ? 'green' : 'darkred';

		echo '<td class="probid">' . $link .
			'<img style="background-color: ' . $printedcol .
			';" alt=" ' . $printedyesno .
		    '" src="../images/circle.png" /> ' . $printedyesno . $endtd;

		// Was the printout delivered?
                $deliveredyesno = $row['delivered'] ? 'yes' : 'no';
                $deliveredcol = $row['delivered'] ? 'lime' : 'red';

		echo '<td class="probid">' . $link .
			'<img style="background-color: ' . $deliveredcol .
			';" alt=" ' . $deliveredyesno .
		    '" src="../images/circle.png" /> ' . $deliveredyesno . $endtd;

		// team name, room and category
		echo '<td class="teamid">' . $link . htmlspecialchars($row['login']) . $endtd . $begintd .
			htmlspecialchars($row['teamname']) . $endtd . $begintd .
			htmlspecialchars($row['room']) . $endtd . $begintd .
			htmlspecialchars($row['catname']) . $endtd . "<td>";

		// 'done' button when balloon has yet to be handed out
		if ( $row['balloon'] == 0 ) {
			echo '<input type="submit" name="done[' .
				htmlspecialchars($row['submitid']) . ']" value="done" />';
		}
		echo "</td></tr>\n";
	}

	echo "</table>\n\n" . addEndForm();
} else {
	echo "<p class=\"nodata\">No printouts yet... keep posted!</p>\n\n";
}


require(LIBWWWDIR . '/footer.php');
