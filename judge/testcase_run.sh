#!/bin/sh

# Script to test (run and compare) submissions with a single testcase
#
# $Id$

# Usage: $0 <testdata.in> <testdata.out> <timelimit> <workdir>
#           <special-run> <special-compare> <memlimit>
#
# <testdata.in>     File containing test-input.
# <testdata.out>    File containing test-output.
# <timelimit>       Timelimit in seconds.
# <workdir>         Directory where to execute submission in a chroot-ed
#                   environment. For best security leave it as empty as possible.
#                   Certainly do not place output-files there!
# <special-run>     Extension name of specialized run or compare script to use.
# <special-compare> Specify empty string for <special-run> if only
#                   <special-compare> is to be used. The script
#                   'run_<special-run>' or 'compare_<special-compare>'
#                   will be called if argument is non-empty.
# <memlimit>        The memory limit in kilobytes (set this to a very big value for java)
#
# For running the solution a script 'run' is called (default). For
# usage of 'run' see that script. Likewise, for comparing results, a
# program 'compare' is called by default.
#
# The program 'xsltproc' is used to parse the result from
# 'result.xml' according to the ICPC Validator Interface Standard as
# described in http://www.ecs.csus.edu/pc2/doc/valistandard.html.
# If the compare program returns with nonzero exitcode however, this
# is viewed as an internal error.

# Exit automatically, whenever a simple command fails and trap it:
set -e
trap 'cleanup ; error' EXIT

cleanup ()
{
	# Remove some copied files to save disk space
	if [ "$WORKDIR" ]; then
		rm -f "$WORKDIR/dev/null" "$WORKDIR/bin/sh" "$WORKDIR/bin/runpipe"

		# Replace testdata by symlinks to reduce disk usage
		if [ -f "$WORKDIR/testdata.in" ]; then
			rm -f "$WORKDIR/testdata.in"
			ln -s "$TESTIN" "$WORKDIR/testdata.in"
		fi
		if [ -f "$WORKDIR/testdata.out" ]; then
			rm -f "$WORKDIR/testdata.out"
			ln -s "$TESTOUT" "$WORKDIR/testdata.out"
		fi
	fi
}

cleanexit ()
{
	set +e
	trap - EXIT

	cleanup

	logmsg $LOG_DEBUG "exiting"
	exit $1
}

# Runs command without error trapping and check exitcode
runcheck ()
{
	set +e
	$@
	exitcode=$?
	set -e
}

# Error and logging functions
. "$DJ_LIBDIR/lib.error.sh"

# Logging:
LOGFILE="$DJ_LOGDIR/judge.`hostname | cut -d . -f 1`.log"
LOGLEVEL=$LOG_DEBUG
PROGNAME="`basename $0`"

# Check for judge backend debugging:
if [ "$DEBUG" ]; then
	export VERBOSE=$LOG_DEBUG
	logmsg $LOG_NOTICE "debugging enabled, DEBUG='$DEBUG'"
else
	export VERBOSE=$LOG_ERR
fi

# Location of scripts/programs:
SCRIPTDIR="$DJ_LIBJUDGEDIR"
STATICSHELL="$DJ_LIBJUDGEDIR/sh-static"
GAINROOT="sudo"
RUNGUARD="$DJ_BINDIR/runguard"
RUNPIPE="$DJ_BINDIR/runpipe"
PROGRAM="execdir/program"

logmsg $LOG_INFO "starting '$0', PID = $$"

[ $# -ge 7 ] || error "not enough arguments. See script-code for usage."
TESTIN="$1";    shift
TESTOUT="$1";   shift
TIMELIMIT="$1"; shift
WORKDIR="$1";   shift
SPECIALRUN="$1"; shift
SPECIALCOMPARE="$1"; shift
MEMLIMIT="$1";
logmsg $LOG_DEBUG "arguments: '$TESTIN' '$TESTOUT' '$TIMELIMIT' '$WORKDIR'"
logmsg $LOG_DEBUG "           '$SPECIALRUN' '$SPECIALCOMPARE' '$MEMLIMIT'"

COMPARE_SCRIPT="$SCRIPTDIR/compare${SPECIALCOMPARE:+_$SPECIALCOMPARE}"
RUN_SCRIPT="$SCRIPTDIR/run${SPECIALRUN:+_$SPECIALRUN}"
if [ -n "$SPECIALRUN" ]; then
	RUN_JURYPROG="$SCRIPTDIR/runjury_${SPECIALRUN}"
fi

[ -r "$TESTIN"  ] || error "test-input not found: $TESTIN"
[ -r "$TESTOUT" ] || error "test-output not found: $TESTOUT"
[ -d "$WORKDIR" -a -w "$WORKDIR" -a -x "$WORKDIR" ] || \
	error "Workdir not found or not writable: $WORKDIR"
[ -x "$WORKDIR/$PROGRAM" ] || error "submission program not found or not executable"
[ -x "$COMPARE_SCRIPT" ] || error "compare script not found or not executable: $COMPARE_SCRIPT"
[ -x "$RUN_SCRIPT" ] || error "run script not found or not executable: $RUN_SCRIPT"
[ -x "$RUNGUARD" ] || error "runguard not found or not executable: $RUNGUARD"

OLDDIR="$PWD"
cd "$WORKDIR"

# Check whether we're going to run in a chroot environment:
if [ -z "$USE_CHROOT" ] || [ "$USE_CHROOT" -eq 0 ]; then
# unset to allow shell default parameter substitution on USE_CHROOT:
	unset USE_CHROOT
	PREFIX=$PWD
else
	PREFIX=''
fi

# Make testing/execute dir accessible for RUNUSER:
chmod a+x "$WORKDIR" "$WORKDIR/execdir"

# Create files which are expected to exist:
touch error.out                  # Error output
touch compare.out                # Compare output
touch result.xml result.out      # Result of comparison (XML and plaintext version)
touch program.out program.err    # Program output and stderr (for extra information)
touch program.time program.exit  # Program runtime and exitcode

# program.{out,err,time,exit} are written to by processes running as RUNUSER:
chmod a+rw program.out program.err program.time program.exit

logmsg $LOG_INFO "setting up testing (chroot) environment"

# Copy the testdata input
cd "$OLDDIR"
cp "$TESTIN" "$WORKDIR/testdata.in"
cd "$WORKDIR"
chmod a+r testdata.in

mkdir -m 0711 bin dev
# Copy the run-script and a statically compiled shell:
cp -p  "$RUN_SCRIPT"  ./run
cp -pL "$STATICSHELL" ./bin/sh
chmod a+rx run bin/sh
# If using a custom run script, copy additional support programs
# if required:
if [ -n "$SPECIALRUN" -a -f "$RUN_JURYPROG" ]; then
	cp -p "$RUN_JURYPROG" ./runjury
	cp -pL "$RUNPIPE"     ./bin/runpipe
	chmod a+rx runjury bin/runpipe
fi

# We copy /dev/null: mknod (and the major/minor device numbers) are
# not portable, while a fifo link has the problem that a cat program
# must be run and killed.
logmsg $LOG_DEBUG "creating /dev/null character-special device"
$GAINROOT cp -pR /dev/null ./dev/null

# Execute an optional chroot setup script:
if [ "$USE_CHROOT" -a "$CHROOT_SCRIPT" ]; then
	logmsg $LOG_DEBUG "executing chroot script: '$CHROOT_SCRIPT start'"
	"$SCRIPTDIR/$CHROOT_SCRIPT" start
fi

# Run the solution program (within a restricted environment):
logmsg $LOG_INFO "running program (USE_CHROOT = ${USE_CHROOT:-0})"

runcheck $GAINROOT $RUNGUARD ${DEBUG:+-v} ${USE_CHROOT:+-r "$PWD"} -u "$RUNUSER" \
	-t $TIMELIMIT -m $MEMLIMIT -f $FILELIMIT -p $PROCLIMIT -c -o program.time -- \
	$PREFIX/run $PREFIX/$PROGRAM \
	testdata.in program.out program.err program.exit \
	>error.tmp 2>&1

# Execute an optional chroot destroy script:
if [ "$USE_CHROOT" -a "$CHROOT_SCRIPT" ]; then
	logmsg $LOG_DEBUG "executing chroot script: '$CHROOT_SCRIPT stop'"
	"$SCRIPTDIR/$CHROOT_SCRIPT" stop
fi

# Check for still running processes (first wait for all exiting processes):
sleep 1
if ps -u "$RUNUSER" >/dev/null 2>&1 ; then
	error "found processes still running"
fi

# Append (heading/trailing) program stderr to error.tmp:
if [ `wc -l < program.err` -gt 20 ]; then
	echo "*** Program stderr output following (first and last 10 lines) ***" >>error.tmp
	head -n 10 program.err >>error.tmp
	echo "*** <snip> ***"  >>error.tmp
	tail -n 10 program.err >>error.tmp
elif [ -s program.err ]; then
	echo "*** Program stderr output following ***" >>error.tmp
	cat program.err >>error.tmp
fi

# Check for errors from running the program:
logmsg $LOG_DEBUG "checking program run exit-status"
if grep  'timelimit reached: aborting command' error.tmp >/dev/null 2>&1 ; then
	echo "Timelimit exceeded." >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_TIMELIMIT:--1}
fi
if [ ! -r program.exit ]; then
	cat error.tmp >>error.out
	error "'program.exit' not readable"
fi
# Check that program.exit was written to (no runguard error)
if [ "`cat program.exit`" != "0" ]; then
	echo "Non-zero exitcode `cat program.exit`" >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_RUN_ERROR:--1}
fi
if [ $exitcode -ne 0 ]; then
	cat error.tmp >>error.out
	error "exitcode $exitcode without program.exit != 0"
fi

############################################################
### Checks for other runtime errors:                     ###
### Disabled, because these are not consistently         ###
### reported the same way by all different compilers.    ###
############################################################
#if grep  'Floating point exception' error.tmp >/dev/null 2>&1 ; then
#	echo "Floating point exception." >>error.out
#	cleanexit ${E_RUN_ERROR:--1}
#fi
#if grep  'Segmentation fault' error.tmp >/dev/null 2>&1 ; then
#	echo "Segmentation fault." >>tee error.out
#	cleanexit ${E_RUN_ERROR:--1}
#fi
#if grep  'File size limit exceeded' error.tmp >/dev/null 2>&1 ; then
#	echo "File size limit exceeded." >>error.out
#	cat error.tmp >>error.out
#	cleanexit ${E_OUTPUT_LIMIT:--1}
#fi

logmsg $LOG_INFO "comparing output"

# Copy testdata output (first cd to olddir to correctly resolve relative paths)
cd "$OLDDIR"
cp "$TESTOUT" "$WORKDIR/testdata.out"
cd "$WORKDIR"

logmsg $LOG_DEBUG "starting script '$COMPARE_SCRIPT'"

if ! "$COMPARE_SCRIPT" testdata.in program.out testdata.out \
                       result.xml compare.out >compare.tmp 2>&1 ; then
	exitcode=$?
	cat error.tmp >>error.out
	error "compare exited with exitcode $exitcode: `cat compare.tmp`";
fi

# Parse result.xml with xsltproc
xsltproc "$SCRIPTDIR"/parse_result.xslt result.xml > result.out
result=`grep '^result='      result.out | cut -d = -f 2- | tr '[:upper:]' '[:lower:]'`
descrp=`grep '^description=' result.out | cut -d = -f 2-`
descrp="${descrp:+ ($descrp)}"

if [ "$result" = "accepted" ]; then
	echo "Correct${descrp}! Runtime is `cat program.time` seconds." >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_CORRECT:--1}
elif [ "$result" = "presentation error" ]; then
	echo "Presentation error${descrp}." >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_PRESENTATION_ERROR:--1}
elif [ ! -s program.out ]; then
	echo "Program produced no output." >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_NO_OUTPUT:--1}
elif [ "$result" = "wrong answer" ]; then
	echo "Wrong answer${descrp}." >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_WRONG_ANSWER:--1}
else
	echo "Unknown result: Wrong answer${descrp}." >>error.out
	cat error.tmp >>error.out
	cleanexit ${E_WRONG_ANSWER:--1}
fi

# This should never be reached
exit ${E_INTERNAL_ERROR:--1}
