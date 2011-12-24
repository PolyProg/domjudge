/* $Id: test-sigfpe.java 3602 2011-08-17 12:57:40Z eldering $
 *
 * This should fail with RUN-ERROR due to integer division by zero.
 *
 * @EXPECTED_RESULTS@: RUN-ERROR
 */

import java.io.*;

class Main {
    public static void main(String[] args) throws Exception {
		int a = 0;
		int b = 10 / a;
		System.out.println(b);
    }
}
