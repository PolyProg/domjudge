<?php
/**
 * View/download a problem text
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require('init.php');

$id = @$_REQUEST['id'];
if ( ! preg_match('/^' . IDENTIFIER_CHARS . '*$/', $id) ) error("Invalid problem id");

if (is_independant_problem($id)) {
        putProblemText($id, "problemtext");
} else {
        error("Cannot show problem $id in public view: this problem depends on another problem.");
}
