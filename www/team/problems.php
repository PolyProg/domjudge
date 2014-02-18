<?php
/**
 * List of problems
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');
$title = 'Problems';
require(LIBWWWDIR . '/header.php');

$cid = $cdata['cid'];
$now = now();
$cstarted = difftime($cdata['starttime'],$now) <= 0;
if (!$cstarted) {
			global $teamdata;
			echo "<h2 id=\"teamwelcome\">welcome team <span id=\"teamwelcometeam\">" .
				htmlspecialchars($teamdata['name']) . "</span>!</h2>\n\n";
			echo "<h3 id=\"contestnotstarted\">contest is scheduled to start at " .
				printtime($cdata['starttime']) . "</h3>\n\n";
} else {
  echo "<h1>Problem statements</h1>\n\n";

  $res = list_problems_in_contests();

  $listsolved = list_problems_solved($login);

  if( $res->count() == 0 ) {
          echo "<p class=\"nodata\">No problems defined</p>\n\n";
  } else {
	echo "<table class=\"list sortable\">\n<thead>\n" .
		"<tr><th scope=\"col\">ID</th><th scope=\"col\">name</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">statement</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">files</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">colour</th>" .
		"</tr></thead>\n<tbody>\n";

	$lastcid = -1;

	while($row = $res->next()) {
                $statementUrl = "problem.php?id=".$row['probid'];
                $dataUrl      = "problem.php?cmd=showdata&amp;id=".$row['probid'];
		$classes = array();
                $cansubmit = false;
                if(!$row['depends']) {
                  $cansubmit = true;
                } else if(isset($listsolved[$row['depends']])) {
                  $cansubmit = true;
                }
                if(isset($listsolved[$row['probid']])) {
                  $classes[] = 'solved';
                }
                else if(!$cansubmit) {
                  $classes[] = 'disabled';
                }

                if($cansubmit) {
                  $linkStatement = '<a href="' . $statementUrl . '">';
                  $linkData      = '<a href="' . $dataUrl . '">';
                  $link = $linkStatement;
                } else {
                  $link = '<a>';
                  $linkStatement = '<a>';
                  $linkData = '<a>';
                }
                echo "<tr class=\"" . implode(' ',$classes) .  "\">";
                echo "<td class=\"probid\">" . $link .  htmlspecialchars($row['probid'])."</a></td>";
                echo "<td>" . $link . htmlspecialchars($row['name'])."</a></td>";
                if( !empty($row['problemtext_type']) ) {
                        echo "<td>" . $linkStatement .
                                '<img src="../images/'.$row['problemtext_type'].'.png">' .
                                '</img><u>'.strtoupper($row['problemtext_type']).'</u></a></td>';
                } else {
                        echo '<td></td>';
                }
                if( !empty($row['problemdata_type']) ) {
                        echo "<td>" . $linkData . '<img src="../images/'.$row['problemdata_type'].'.png">' .
                                '</img><u>'.strtoupper($row['problemdata_type']).'</u></a></td>';
                } else {
                        echo '<td></td>';
                }
                if ( !empty($row['color']) ) {
                        echo '<td title="' . htmlspecialchars($row['color']) . '">' .
                                $link . '<img style="background-color: ' .  htmlspecialchars($row['color']) .
                                ';" alt="problem colour ' . htmlspecialchars($row['color']) .
                                '" src="../images/circle.png" /></a></td>';
                } else {
                        echo '<td>' . $link . '&nbsp;</a></td>';
                }
                echo "</tr>\n";

	}

        $linkDoc = '<a target="_blank" href="http://doc.hc2.ch/">';
        echo "<tr><td></td></tr>";
        echo "<tr><td>";
        echo '</td><td>'.$linkDoc.'<strong>Documentation</strong></a>';
        echo '</td><td>'.$linkDoc.'<img src="../images/html.png"></img><u>HTML</u></a>';
        echo "</td><td>";
        echo "</td><td>";
        echo "</td></tr>";
	echo "</tbody>\n</table>\n\n";
  }
}


require(LIBWWWDIR . '/footer.php');

