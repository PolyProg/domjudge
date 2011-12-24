<?php
// $Id: init.php 3607 2011-08-22 20:27:18Z eldering $
if ( !defined('LIBDIR') ) die ("LIBDIR not defined.");

require(LIBDIR . '/lib.error.php');
require(LIBDIR . '/lib.misc.php');
require(LIBDIR . '/lib.config.php');
require(LIBDIR . '/lib.dbconfig.php');
require(LIBDIR . '/use_db.php');

if ( defined('LANG_EXTS') ) parseLangExts();

// Initialize default timezone to system default. PHP >= 5.3 generates
// E_NOTICE warning messages otherwise.
@date_default_timezone_set(@date_default_timezone_get());

// Here or in script?
//setup_database_connection('jury');
