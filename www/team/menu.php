<?php

echo "<nav><div id=\"menutop\">\n";

echo "<a target=\"_top\" href=\"index.php\" accesskey=\"o\">overview</a>\n";
echo "<a target=\"_top\" href=\"problems.php\" accesskey=\"o\">problem statements</a>\n";

if ( have_printing() ) {
	echo "<a target=\"_top\" href=\"print.php\" accesskey=\"p\">print</a>\n";
}
echo "<a target=\"_top\" href=\"scoreboard.php\" accesskey=\"b\">scoreboard</a>\n";

if ( have_logout() ) {
	echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a target=\"_top\" href=\"logout.php\" accesskey=\"l\">logout</a>\n";
}

echo "</div>\n\n<div id=\"menutopright\">\n";

putClock();

echo "</div></nav>\n\n";
