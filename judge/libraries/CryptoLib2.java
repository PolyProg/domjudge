import java.math.BigInteger;
import java.util.Scanner;

public class CryptoLib2 {

  private static Crypto2 crypto2;
  private static Scanner scanner;

  public static void main(String args[]) {
    crypto2 = new Crypto2();
    scanner = new Scanner(System.in);

    testDecrypt();

    System.out.println();
    System.out.println("OK - b3610618a8655c5f433df47560a8239b");
  }

  private static void unitTest() {
    BigInteger p = BigInteger.valueOf(1000003);
    BigInteger g = BigInteger.valueOf(2);
    BigInteger x = BigInteger.valueOf(4242);
    BigInteger r = BigInteger.valueOf(123456);
    BigInteger m = BigInteger.valueOf(654321);
    BigInteger y = g.modPow(x, p);

    PublicKey pk = new PublicKey();
    pk.p = p;
    pk.g = g;
    pk.y = y;

    Ciphertext ct = new Ciphertext();
    ct.E = BigInteger.valueOf(509777);
    ct.F =BigInteger.valueOf(709498);
    BigInteger mp = crypto2.decrypt(ct, pk);
    if (! mp.equals(m)) {
      System.err.println("Decrypt failed (m' != m).");
      System.err.println("Expected: " + m);
      System.err.println("Got:      " + mp);
      System.exit(0);
    } else {
      System.out.println("OK");
    }
  }

  private static void testDecrypt()
  {
    /*
      Input format is:
      - Number of testcases
      - For each testcase:   E  F  p  g  y  x  m  m2
    */
    int ntc = scanner.nextInt();
    for(int i=0;i<ntc;++i) {
      Ciphertext ct = new Ciphertext();
      ct.E = new BigInteger(scanner.next());
      ct.F = new BigInteger(scanner.next());
      PublicKey pk = new PublicKey();
      pk.p = new BigInteger(scanner.next());
      pk.g = new BigInteger(scanner.next());
      pk.y = new BigInteger(scanner.next());
      BigInteger x = new BigInteger(scanner.next());
      if(! pk.g.modPow(x, pk.p).equals(pk.y)) {
        System.err.println("ERROR: g^x != y  (mod p)");
        System.exit(1);
      }

      BigInteger m = crypto2.decrypt(ct, pk);
      BigInteger expectedM = new BigInteger(scanner.next());
      scanner.next(); // Remove m2 which we don't need for this test.
      if(! m.equals(expectedM)) {
        System.out.println();
        System.out.println("Testcase " + i + "  Wrong answer: expected " + expectedM + " got:");
        System.out.println(m);
        System.exit(0);
      } else {
        System.out.print(i+".");
      }
    }
  }

}

class Ciphertext {
  public BigInteger E;
  public BigInteger F;
}

class PublicKey {
  public BigInteger p;
  public BigInteger g;
  public BigInteger y;
}
