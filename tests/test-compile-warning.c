/* $Id: test-compile-warning.c 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should give compiler warnings and fail with NO-OUTPUT
 *
 * @EXPECTED_RESULTS@: NO-OUTPUT
 */

#include <stdio.h>

int main()
{
	char str[1000];

	gets(str);

	return 0;
}
