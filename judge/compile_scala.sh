#!/bin/sh

# Scala compile wrapper-script for 'compile.sh'.
# See that script for syntax and more info.
#
# NOTICE: this compiler script cannot be used with the USE_CHROOT
# configuration option turned on, unless proper preconfiguration of
# the chroot environment has been taken care of!

DEST="$1" ; shift
MEMLIMIT="$1" ; shift
MAINSOURCE="$1"

scalac "$@"
EXITCODE=$?
[ "$EXITCODE" -ne 0 ] && exit $EXITCODE

# Look for class that has the 'main' function:
for cn in $(find * -type f -regex '^.*\.class$' \
		| sed -e 's/\.class$//' -e 's/\//./'); do
	javap "$cn" \
	| egrep -q 'public static (|final )void main\(java.lang.String(\[\]|\.\.\.)\)' \
	&& {
		if [ -n "$MAINCLASS" ]; then
			echo "Warning: found another 'main' in '$cn'"
		else
			echo "Info: using 'main' from '$cn'"
			MAINCLASS=$cn
		fi
	}
done
if [ -z "$MAINCLASS" ]; then
	echo "Error: no 'main' found in any class file."
	exit 1
fi

cat > $DEST <<EOF
#!/bin/sh
# Generated shell-script to execute scala interpreter on source.

# Detect dirname and change dir to prevent class not found errors.
if [ "\${0%/*}" != "\$0" ]; then
    cd "\${0%/*}"
fi

exec scala -J-Xrs -J-Xss8m -J-DONLINE_JUDGE=1 -J-DDOMJUDGE=1 -J-Xmx${MEMLIMIT}k $MAINCLASS "\$@"
EOF

chmod a+x $DEST

exit 0
