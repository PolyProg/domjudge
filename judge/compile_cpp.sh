#!/bin/sh

# C++ compile wrapper-script for 'compile.sh'.
# See that script for syntax and more info.

SOURCE="$1"
DEST="$2"
LIBRARY="$4"
#STATIC="-static"

echo g++ -Wall -O2 $STATIC -pipe -o $DEST $SOURCE $LIBRARY -lgmp
# -Wall:	Report all warnings
# -O2:		Level 2 optimizations (default for speed)
# -static:	Static link with all libraries
# -pipe:	Use pipes for communication between stages of compilation
# -lgmp:        Link with GNU multiprecision library
# -lgmpxx:      Link with C++ extensions of GNU multiprecision library
g++ -Wall -O2 $STATIC -pipe -o $DEST $SOURCE $LIBRARY -lgmp -lgmpxx
exit $?
