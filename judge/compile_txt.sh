#!/bin/sh

# POSIX shell compile wrapper-script for 'compile.sh'.
# See that script for syntax and more info.
#
# This script does not actually "compile" the source, but writes a
# shell script that will function as the executable: when called, it
# will execute the source with the correct interpreter syntax, thus
# allowing this interpreted source to be used transparantly as if it
# was compiled to a standalone binary.

SOURCE="$1"
DEST="$2"

RUNOPTIONS=""

# Write executing script:
cat > $DEST <<EOF
#!/bin/sh
# Generated shell-script to execute shell interpreter on source.

cat $SOURCE
EOF

chmod a+x $DEST

exit 0
