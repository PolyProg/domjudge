/* $Id: test-exitcode.c 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should fail with RUN-ERROR (due to exitcode != 0)
 *
 * @EXPECTED_RESULTS@: RUN-ERROR
 */

int main()
{
	return 1;
}
