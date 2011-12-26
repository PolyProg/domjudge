<?php
/**
 * $Id: index.php 3631 2011-08-27 19:10:50Z eldering $
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$title = 'Problems';
require(LIBWWWDIR . '/header.php');

echo "<h1>Problem statements</h1>\n\n";
echo "<p>Showing only problems to which you are allowed to submit.</p>\n\n";

$res = list_problems_satisfying_dependency($login);

if( $res->count() == 0 ) {
	echo "<p class=\"nodata\">No problems defined</p>\n\n";
} else {
	echo "<table class=\"list sortable\">\n<thead>\n" .
		"<tr><th scope=\"col\">ID</th><th scope=\"col\">name</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">colour</th>" .
		"</tr></thead>\n<tbody>\n";

	$lastcid = -1;

	while($row = $res->next()) {
                $statementUrl = problemStatementUrl($row['probid']);
		$classes = array();
		$link = '<a href="' . $statementUrl . '">';

		echo "<tr class=\"" . implode(' ',$classes) .
		    "\"><td class=\"probid\">" . $link .
				htmlspecialchars($row['probid'])."</a>".
			"</td><td>" . $link . htmlspecialchars($row['name'])."</a>".
			"</td>".
			( !empty($row['color'])
			? '<td title="' . htmlspecialchars($row['color']) .
		      '">' . $link . '<img style="background-color: ' .
			htmlspecialchars($row['color']) .
		      ';" alt="problem colour ' . htmlspecialchars($row['color']) .
		      '" src="../images/circle.png" /></a>'
			: '<td>' . $link . '&nbsp;</a>' );
			echo "</td></tr>\n";
	}
	echo "</tbody>\n</table>\n\n";
}

require(LIBWWWDIR . '/footer.php');
