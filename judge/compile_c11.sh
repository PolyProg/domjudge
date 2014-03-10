#!/bin/sh

# C++11 compile wrapper-script for 'compile.sh'.
# See that script for syntax and more info.

DEST="$1" ; shift
MEMLIMIT="$1" ; shift
MAINSOURCE="$1"

# -Wall:	Report all warnings
# -O2:		Level 2 optimizations (default for speed)
# -static:	Static link with all libraries
# -pipe:	Use pipes for communication between stages of compilation
# -std=c++11:	Use C++11 conventions
g++ -Wall -O2 -static -pipe -std=gnu++0x -DONLINE_JUDGE -DDOMJUDGE -o $DEST -x c++ "$@"
exit $?
