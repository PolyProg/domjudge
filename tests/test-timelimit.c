/* $Id: test-timelimit.c 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should give a TIMELIMIT.
 *
 * @EXPECTED_RESULTS@: TIMELIMIT
 */

int main()
{
	int a;

	while ( 1 ) a++;

	return 0;
}
