/* $Id: test-hello.c++ 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should give CORRECT on the default problem 'hello'.
 *
 * @EXPECTED_RESULTS@: CORRECT
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string hello("Hello world!");
	cout << hello << endl;
	return 0;
}
