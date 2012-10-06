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
		"<th class=\"sorttable_nosort\" scope=\"col\">HTML</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">PDF</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">Files</th>" .
		"<th class=\"sorttable_nosort\" scope=\"col\">colour</th>" .
		"</tr></thead>\n<tbody>\n";

	$lastcid = -1;

	while($row = $res->next()) {
                $statementUrl = problemStatementUrl($row['probid']);
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
                  $linkPdf = '<a href="' . $statementUrl . '/'.$row['probid'].'.pdf">';
                  $linkZip = '<a href="' . $statementUrl . '/'.$row['probid'].'.zip">';
                  $linkHtml = '<a target="_blank" href="' . $statementUrl . '/'.$row['probid'].'.html">';
                  $link = $linkHtml;
                } else {
                  $link = '<a>';
                  $linkPdf = '<a>';
                  $linkZip = '<a>';
                  $linkHtml = '<a>';
                }
                echo "<tr class=\"" . implode(' ',$classes) .
                    "\"><td class=\"probid\">" . $link .
                                htmlspecialchars($row['probid'])."</a>".
                        "</td><td>" . $link . htmlspecialchars($row['name'])."</a>".
                        "</td><td>" . $linkHtml . '<img src="../images/html.png"></img><u>HTML</u>' ."</a>".
                        "</td><td>" . $linkPdf . '<img src="../images/pdf.png"></img><u>PDF</u>' ."</a>".
                        "</td><td>" . $linkZip . '<img src="../images/zip.png"></img><u>Files</u>' ."</a>".
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
        if (HC2_RULES == '0') {
          $statementUrl = problemStatementUrl('all');
          $link = '<a href="' . $statementUrl . '/all.pdf">';
          $linkPdf = '<a href="' . $statementUrl . '/all.pdf">';
          $linkZip = '<a href="' . $statementUrl . '/all.zip">';
          echo "<tr><td></td></tr>";
          echo "<tr><td>";
          echo "</td><td>" . $link . "<strong>All Problems</strong></a>";
          echo "</td><td>";
          echo "</td><td>" . $linkPdf . '<img src="../images/pdf.png"></img><u>PDF</u>' ."</a>";
          echo "</td><td>" . $linkZip . '<img src="../images/zip.png"></img><u>Files</u>' ."</a>";
          echo "</td><td>";
          echo "</td></tr>";
        }

        $linkDoc = '<a target="_blank" href="http://doc.hc2.ch/">';
        echo "<tr><td></td></tr>";
        echo "<tr><td>";
        echo '</td><td>'.$linkDoc.'<strong>Documentation</strong></a>';
        echo '</td><td>'.$linkDoc.'<img src="../images/html.png"></img><u>HTML</u></a>';
        echo "</td><td>";
        echo "</td><td>";
        echo "</td><td>";
        echo "</td></tr>";
	echo "</tbody>\n</table>\n\n";
  }
}


require(LIBWWWDIR . '/footer.php');
