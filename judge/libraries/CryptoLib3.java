import java.math.BigInteger;
import java.util.Scanner;
import java.util.Random;

public class CryptoLib3 {

  private static Crypto3 crypto3;
  private static Scanner scanner;
  private static int x_n = 773137898;

  public static void main(String args[]) {
    crypto3 = new Crypto3();
    scanner = new Scanner(System.in);

    testDecrypt();

    System.out.println();
    System.out.println("OK - a03cf946a04f9ae2fd30c3e7d20a7009");
  }

  private static int my_rand()
  {
    final int A = 1103515245;
    final int C = 12345;
    x_n = A*x_n + C;

    int res = (x_n & 0x3FFFFFFF) / (65536);
    return res;
  }

  private static void unitTest() {
    // Note: in the real test, p will change all the time
    BigInteger p = BigInteger.valueOf(1000003);
    Random random = new Random();
    int correct = 0;
    int ntc = 100;
    for(int i=0;i<ntc;++i) {
      // Note: in the real test: g will be distributed uniformly at random
      // in its domain
      BigInteger g = (new BigInteger(19, random)).add(BigInteger.valueOf(2));
      BigInteger x = new BigInteger(19, random);
      BigInteger r = new BigInteger(19, random);
      BigInteger m1 = new BigInteger(19, random);
      BigInteger m2 = new BigInteger(19, random);
      BigInteger y = g.modPow(x, p);

      PublicKey pk = new PublicKey();
      pk.p = p;
      pk.g = g;
      pk.y = y;

      Ciphertext ct = encrypt(m1, pk, r);

      BigInteger m;
      if (Math.random()>0.5) {
        m = crypto3.decrypt(ct, pk, m1, m2);
      } else {
        m = crypto3.decrypt(ct, pk, m2, m1);
      }

      if(m.equals(m1)) {
        correct++;
      } else {
      }
    }
    System.out.println("You were correct " + correct*100./ntc + "% of the time.");
    System.out.println("(You should aim for 75% correct.)");
  }

  static Ciphertext encrypt(BigInteger plaintext, PublicKey key, BigInteger r) {
    Ciphertext ct = new Ciphertext();
    // E = m * y^r (mod p)
    ct.E = plaintext.multiply(key.y.modPow(r, key.p)).mod(key.p);
    // F = g^(-r)
    ct.F = key.g.modPow(r.negate(), key.p);
    return ct;
  }

  private static void testDecrypt()
  {
    /*
      We want that an algorithm with winning probability 24/32 (=75%)
        wins the game with probability 99.9%
      And that an algorithm with winning probability 23/32 (=71.8%)
        loses the game with probability 99.9%.

      Octave code:
      octave:43> N=7646;X=1:N;[i,iw]=max((binocdf(X, N, 24/32)<=0.001)+(binocdf(X, N, 23/32)>0.999))
      i =  2
      iw =  5616

      octave:45> [binocdf(iw,N,23/32) 1-binocdf(iw,N,24/32)]
      ans =

         0.99901   0.99903

      So with N = 7646 and requiring 5616 tests correct these are the winning probabilities:
      algo 24/32:   passes with probability 0.99903
      algo 23/32:   does not pass with probability 0.99901
    */
    int correct = 0;
    int mincorrect = 5616;
    /*
      Input format is:
      - Number of testcases
      - For each testcase:   E  F  p  g  y  x  m  m2
    */
    int ntc = scanner.nextInt();
    if(ntc != 7646) {
        System.err.println("ERROR: expected exactly 7646 testcases");
        System.exit(1);
    }
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
      BigInteger m1 = new BigInteger(scanner.next());
      BigInteger m2 = new BigInteger(scanner.next());

      BigInteger m;
      if (my_rand()%2 == 0) {
        m = crypto3.decrypt(ct, pk, m1, m2);
      } else {
        m = crypto3.decrypt(ct, pk, m2, m1);
      }

      System.out.print(".");
      if(m.equals(m1)) {
        correct++;
      } else {
      }
    }

    if(correct < mincorrect) {
      System.out.println();
      System.out.println("Not enough correct answers: " + correct + " expected at least: " + mincorrect);
      System.out.println("Peformance: " + correct*100./ntc + "% expected performance: " + mincorrect*100./ntc + "%");
      System.exit(0);
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
