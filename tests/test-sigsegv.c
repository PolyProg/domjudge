/* $Id: test-sigsegv.c 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should fail with RUN-ERROR due to a segmentation fault,
 * giving an exitcode 139.
 *
 * @EXPECTED_RESULTS@: RUN-ERROR
 */

int main()
{
	int a[10];
	int *b;

	b = 10;
	*b = a[-1000000];

	return 0;
}
