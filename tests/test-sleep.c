/* $Id: test-sleep.c 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should fail with a TIMELIMIT.
 *
 * @EXPECTED_RESULTS@: TIMELIMIT
 */

#include <unistd.h>

int main()
{
	while ( 1 ) sleep(1);

	return 0;
}
