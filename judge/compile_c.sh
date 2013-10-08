#!/bin/sh

# C compile wrapper-script for 'compile.sh'.
# See that script for syntax and more info.

SOURCE="$1"
DEST="$2"
LIBRARY="$4"
#STATIC="-static"

echo gcc -Wall -O2 $STATIC -pipe -o $DEST $SOURCE $LIBRARY -lm
# -Wall:	Report all warnings
# -O2:		Level 2 optimizations (default for speed)
# -static:	Static link with all libraries
# -pipe:	Use pipes for communication between stages of compilation
# -lm:		Link with math-library (has to be last argument!)
# -lgmp:        Link with GNU multiprecision library
gcc -Wall -O2 $STATIC -pipe -o $DEST $SOURCE $LIBRARY -lm
exit $?
