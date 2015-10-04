<?php
/**
 * View the problems
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$title = 'Problems';

require(LIBWWWDIR . '/header.php');

echo "<h1>Problems</h1>\n\n";

if ( IS_ADMIN && isset($_POST['deleteall']) && isset($_POST['confirm'])) {
  $DB->q('DELETE from problem');
}

// Select all data, sort problems from the current contest on top.
$res = $DB->q('SELECT p.probid,p.name,p.allow_submit,p.allow_judge,p.timelimit,p.color,
               p.problemtext_type,p.problemdata_type,p.problemlib_type,p.depends,p.library_prefix,p.special_runtime,
               c.*, COUNT(testcaseid) AS testcases
               FROM problem p
               NATURAL JOIN contest c
               LEFT JOIN testcase USING (probid)
               GROUP BY probid ORDER BY (p.cid = %i) DESC, p.cid, probid', $cid);

if( $res->count() == 0 ) {
	echo "<p class=\"nodata\">No problems defined</p>\n\n";
} else {
	echo "<table class=\"list sortable\">\n<thead>\n" .
	     "<tr><th scope=\"col\">ID</th><th scope=\"col\">name</th>" .
	     "<th scope=\"col\" class=\"sorttable_numeric\">contest</th>" .
	     "<th scope=\"col\">allow<br />submit</th>" .
	     "<th scope=\"col\">allow<br />judge</th>" .
	     "<th scope=\"col\">time<br />limit</th>" .
	     "<th class=\"sorttable_nosort\" scope=\"col\">colour</th>" .
	     "<th scope=\"col\">test<br />cases</th>" .
	     "<th scope=\"col\">depends</th>" .
	     "<th scope=\"col\">text</th>" .
	     "<th scope=\"col\">data</th>" .
	     "<th scope=\"col\">lib</th>" .
	    ( IS_ADMIN ? "<th scope=\"col\"></th>" : '' ) .
	     "</tr></thead>\n<tbody>\n";

	$lastcid = -1;

	while($row = $res->next()) {
		$classes = array();
		if ( $row['cid'] != $cid ) $classes[] = 'disabled';
		if ( $row['cid'] != $lastcid ) {
			if ( $lastcid != -1 ) $classes[] = 'contestswitch';
			$lastcid = $row['cid'];
		}
		$link = '<a href="problem.php?id=' . urlencode($row['probid']) . '">';

		echo "<tr class=\"" . implode(' ',$classes) .
		    "\"><td class=\"probid\">" . $link .
				htmlspecialchars($row['probid'])."</a>".
			"</td><td>" . $link . htmlspecialchars($row['name'])."</a>".
			"</td><td title=\"".htmlspecialchars($row['contestname'])."\">".
			$link . 'c' . htmlspecialchars($row['cid']) . "</a>" .
			"</td><td class=\"tdcenter\">" . $link .
			printyn($row['allow_submit']) . "</a>" .
			"</td><td class=\"tdcenter\">" . $link .
			printyn($row['allow_judge']) . "</a>" .
			"</td><td>" . $link . (int)$row['timelimit'] .
                        (($row['special_runtime']!="")?(" (".$row['special_runtime'].")"):"")
                        . "</a>" .
			"</td>".
			( !empty($row['color'])
			? '<td title="' . htmlspecialchars($row['color']) .
		      '">' . $link . '<img class="balloonimage" style="background-color: ' .
			htmlspecialchars($row['color']) .
		      ';" alt="problem colour ' . htmlspecialchars($row['color']) .
		      '" src="../images/circle.png" /></a>'
			: '<td>' . $link . '&nbsp;</a>' );
		echo "</td><td><a href=\"testcase.php?probid=" . $row['probid'] .
		    "\">" . $row['testcases'] . "</a></td>";

		echo "<td class=\"probid\">" . $link .  htmlspecialchars($row['depends'])."</a>"."</td>";
		if ( !empty($row['problemtext_type']) ) {
			echo '<td title="view problem description">' .
			     '<a href="problem.php?id=' . urlencode($row['probid']) .
			     '&amp;cmd=viewtext"><img src="../images/' . urlencode($row['problemtext_type']) .
			     '.png" alt="problem text" /></a></td>';
		} else {
			echo '<td></td>';
		}
		if ( !empty($row['problemdata_type']) ) {
			echo '<td title="view problem data for contestant">' .
			     '<a href="problem.php?id=' . urlencode($row['probid']) .
			     '&amp;cmd=viewdata"><img src="../images/' . urlencode($row['problemdata_type']) .
			     '.png" alt="problem text" /></a></td>';
		} else {
			echo '<td></td>';
		}
		if ( !empty($row['problemlib_type']) ) {
			echo '<td title="view problem library for judge">' .
			     '<a href="problem.php?id=' . urlencode($row['probid']) .
			     '&amp;cmd=viewlib"><img src="../images/' . urlencode($row['problemlib_type']) .
			     '.png" alt="problem text" />'.$row['library_prefix'].'</a></td>';
		} else {
			echo '<td>'.$row['library_prefix'].'</td>';
		}
		if ( IS_ADMIN ) {
			echo '<td title="export problem as zip-file">' .
			     exportLink($row['probid']) . '</td>' .
			     "<td class=\"editdel\">" .
			     editLink('problem', $row['probid']) . " " .
			     delLink('problem','probid',$row['probid']) . "</td>";
		}
		echo "</tr>\n";
	}
	echo "</tbody>\n</table>\n\n";
}

if ( IS_ADMIN ) {
	echo "<p>" . addLink('problem') . "</p>\n\n";
	if ( class_exists("ZipArchive") ) {
		echo "\n" . addForm('problem.php', 'post', null, 'multipart/form-data') .
	 		'Problem archive(s): ' .
	 		addFileField('problem_archive[]', null, ' required multiple accept="application/zip"') .
	 		addSubmit('Upload', 'upload') .
	 		addEndForm() . "\n";
	}
        echo "<p><p />";
        echo "\n" . addForm('problems.php', 'post', null, 'multipart/form-data') .
                addCheckBox('confirm') . "Confirm&nbsp;" .
                addSubmit('Delete all problems', 'deleteall') .
                addEndForm() . "\n";
        echo "<p><p />";
}

require(LIBWWWDIR . '/footer.php');
