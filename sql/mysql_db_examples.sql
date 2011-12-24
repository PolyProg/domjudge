-- These are some example/default entries for the DOMjudge database.
--
-- You can pipe this file into the 'mysql' command to insert this
-- data, but preferably use 'dj-setup-database'. Database should be set
-- externally (e.g. to 'domjudge').
--
-- $Id: mysql_db_examples.sql 3575 2011-07-30 11:28:24Z eldering $


-- 
-- Dumping data for table `configuration`
-- 

INSERT INTO `configuration` (`name`, `value`) VALUES ('show_affiliations', '1');

-- 
-- Dumping data for table `contest`
-- 

INSERT INTO `contest` (`cid`, `contestname`, `activatetime`, `starttime`, `freezetime`, `endtime`, `unfreezetime`, `activatetime_string`, `freezetime_string`, `endtime_string`, `unfreezetime_string`) VALUES (1, 'Demo practice session', '2010-01-01 08:30:00', '2010-01-01 09:00:00', NULL, '2010-01-01 11:00:00', NULL, '-1:00', NULL, '+2:00', NULL);
INSERT INTO `contest` (`cid`, `contestname`, `activatetime`, `starttime`, `freezetime`, `endtime`, `unfreezetime`, `activatetime_string`, `freezetime_string`, `endtime_string`, `unfreezetime_string`) VALUES (2, 'Demo contest', '2010-01-01 11:30:00', '2010-01-01 12:00:00', '2012-01-01 16:00:00', '2012-01-01 17:00:00', '2012-01-01 17:30:00', '2010-01-01 11:30:00', '2012-01-01 16:00:00', '2012-01-01 17:00:00', '2012-01-01 17:30:00');

-- 
-- Dumping data for table `judgehost`
-- 

INSERT INTO `judgehost` (`hostname`, `active`) VALUES ('judgehost1', 1);
INSERT INTO `judgehost` (`hostname`, `active`) VALUES ('judgehost2', 1);
INSERT INTO `judgehost` (`hostname`, `active`) VALUES ('sparehost', 0);

-- 
-- Dumping data for table `language`
-- 

INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('c', 'C', 1, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('cpp', 'C++', 1, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('java', 'Java', 1, 1, 1.5);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('pas', 'Pascal', 0, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('hs', 'Haskell', 0, 1, 2);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('pl', 'Perl', 0, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('sh', 'POSIX shell', 0, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('csharp', 'C#', 0, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('awk', 'AWK', 0, 1, 1);
INSERT INTO `language` (`langid`, `name`, `allow_submit`, `allow_judge`, `time_factor`) VALUES ('py', 'Python', 0, 1, 1);

-- 
-- Dumping data for table `problem`
-- 

INSERT INTO `problem` (`probid`, `cid`, `name`, `allow_submit`, `allow_judge`, `timelimit`, `special_run`, `special_compare`, `color`) VALUES ('hello', 2, 'Hello World', 1, 1, 5, NULL, NULL, 'magenta');
INSERT INTO `problem` (`probid`, `cid`, `name`, `allow_submit`, `allow_judge`, `timelimit`, `special_run`, `special_compare`, `color`) VALUES ('fltcmp', 2, 'Float special compare test', 1, 1, 5, NULL, 'float', 'yellow');
INSERT INTO `problem` (`probid`, `cid`, `name`, `allow_submit`, `allow_judge`, `timelimit`, `special_run`, `special_compare`, `color`) VALUES ('boolfind', 2, 'Boolean switch search', 1, 1, 5, 'boolfind', 'boolfind', 'limegreen');

-- 
-- Dumping data for table `team_affiliation`
-- 

INSERT INTO `team_affiliation` (`affilid`, `name`, `country`, `comments`) VALUES ('UU', 'Utrecht University', 'NL', NULL);

-- 
-- Dumping data for table `team_category`
-- 

INSERT INTO `team_category` (`categoryid`, `name`, `sortorder`, `color`, `visible`) VALUES (1, 'Participants', 0, NULL, 1);
INSERT INTO `team_category` (`categoryid`, `name`, `sortorder`, `color`, `visible`) VALUES (2, 'Observers', 1, "#ffcc33", 1);
INSERT INTO `team_category` (`categoryid`, `name`, `sortorder`, `color`, `visible`) VALUES (3, 'Organisation', 1, "#ff99cc", 0);


-- 
-- Dumping data for table `team`
-- 

INSERT INTO `team` (`login`, `name`, `categoryid`, `affilid`, `authtoken`, `hostname`, `room`, `comments`, `teampage_first_visited`) VALUES ('domjudge', 'DOMjudge', 3, 'UU', '127.0.0.1', NULL, NULL, NULL, NULL);
INSERT INTO `team` (`login`, `name`, `categoryid`, `affilid`, `authtoken`, `hostname`, `room`, `comments`, `teampage_first_visited`) VALUES ('coolteam', 'Some very cool teamname!', 1, NULL, MD5('coolteam#mypassword'), NULL, NULL, NULL, NULL);

-- 
-- Dumping data for table `testcase`
-- 

INSERT INTO `testcase` (`testcaseid`, `md5sum_input`, `md5sum_output`, `input`, `output`, `probid`, `rank`, `description`) VALUES (1, 'b026324c6904b2a9cb4b88d6d61c81d1', '59ca0efa9f5633cb0371bbc0355478d8', 0x310a, 0x48656c6c6f20776f726c64210a, 'hello', 1, NULL);
INSERT INTO `testcase` (`testcaseid`, `md5sum_input`, `md5sum_output`, `input`, `output`, `probid`, `rank`, `description`) VALUES (2, '9b05c566cf4d373cd23ffe75787c1f6d', '0b93bf53346750cc7e04c02f31443721', 0x330a312e300a3245300a330a, 0x312e300a302e35303030303030303030310a332e333333333333333333452d310a, 'fltcmp', 1, 'Different floating formats');
INSERT INTO `testcase` (`testcaseid`, `md5sum_input`, `md5sum_output`, `input`, `output`, `probid`, `rank`, `description`) VALUES (3, 'a94c7fc1f4dac435f6fc5d5d4c7ba173', '2c266fa701a6034e02d928331d5bd4ef', 0x320a342e303030303030303030303030300a352e303030303030303030303030310a, 0x302e32350a32452d310a, 'fltcmp', 2, 'High precision inputs');
INSERT INTO `testcase` (`testcaseid`, `md5sum_input`, `md5sum_output`, `input`, `output`, `probid`, `rank`, `description`) VALUES (4, 'fc157fa74267ba846e8ddc9c0747ad53', 'd38340056cc41e311beae85f906d7f24', 0x330a2b300a496e660a6e616e0a, 0x696e660a300a4e614e0a, 'fltcmp', 3, 'Inf/NaN checks');
INSERT INTO `testcase` (`testcaseid`, `md5sum_input`, `md5sum_output`, `input`, `output`, `probid`, `rank`, `description`) VALUES (5, '90864a8759427d63b40f1f5f75e32308', '6267776644f5bd2bf0edccf5a210e087', 0x310a350a310a310a300a310a300a, 0x4f555450555420310a, 'boolfind', 1, NULL);
