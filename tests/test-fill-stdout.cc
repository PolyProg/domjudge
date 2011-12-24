/* $Id: test-fill-stdout.cc 3602 2011-08-17 12:57:40Z eldering $
 *
 * Floods stdout and should fail with TIME-LIMIT or RUN-ERROR
 * depending on whether timelimit or filesize limit is reached first.
 *
 * @EXPECTED_RESULTS@: TIME-LIMIT,RUN-ERROR
 */

#include <iostream>
#include <string>

int main()
{
	while ( 1 ) std::cout << "Fill stdout with nonsense, to test filesystem stability.\n";

	return 0;
}
