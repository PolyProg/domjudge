<?php
/**
 * Include required files.
 *
 * $Id: init.php 3575 2011-07-30 11:28:24Z eldering $
 *
 * Part of the DOMjudge Programming Contest Jury System and licenced
 * under the GNU GPL. See README and COPYING for details.
 */

require_once('../configure.php');

define('IS_JURY', false);

if( DEBUG & DEBUG_TIMINGS ) {
	require_once(LIBDIR . '/lib.timer.php');
}

require_once(LIBDIR . '/lib.error.php');
require_once(LIBDIR . '/lib.misc.php');
require_once(LIBDIR . '/lib.dbconfig.php');
require_once(LIBDIR . '/use_db.php');

parseLangExts();

set_exception_handler('exception_handler');
setup_database_connection('public');

require_once(LIBWWWDIR . '/common.php');
require_once(LIBWWWDIR . '/print.php');

$cdata = getCurContest(TRUE);
$cid = $cdata['cid'];
