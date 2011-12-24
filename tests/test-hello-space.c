/* $Id: test-hello-space.c 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should give CORRECT, WRONG-ANSWER or PRESENTATION-ERROR on the
 * default problem 'hello' depending on how strict white space is
 * checked for.
 *
 * @EXPECTED_RESULTS@: CORRECT,WRONG-ANSWER,PRESENTATION-ERROR
 */

#include <stdio.h>

int main()
{
	char hello[20] = "Hello   	 world!";
	printf("%s\n",hello);
	return 0;
}
