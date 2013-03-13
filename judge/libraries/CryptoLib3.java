public class CryptoLib3 {

  private static final int FROM_STDIN = 1;

  private static final int TESTCASES = 10;
  private static final int MAX_BYTE = 1<<8;
  private static final int MAX_WORD = 1<<16;
  private static final int SBOX1_PRIME = 65537;
  private static final int SBOX2_PRIME = 257;
  private static final int NUMBER_OF_SBOXES = 3;
  private static final int KEY_ROUNDS = 16;

  private static final long ONE = 1;
  private static final long SIXTEEN = 16;

  private static void assertByte(int input) {
    if(input<0 || input >= MAX_BYTE) {
      System.err.println("Invalid range: "+input+" is not between 0 and "+(MAX_BYTE-1));
      System.exit(1);
    }
  }

  private static void assertWord(int input) {
    if(input<0 || input >= MAX_WORD) {
      System.err.println("Invalid range: "+input+" is not between 0 and "+(MAX_WORD-1));
      System.exit(1);
    }
  }

  private static int sBox0(int input, int key) {
    assertByte(input);
    assertByte(key);

    return input ^ key;
  }

  private static int sBox1(int input, int key) {
    assertByte(input);
    assertByte(key);

    long e = input + 256*key + 1;
    e = ((e * e) % SBOX1_PRIME) - 1;
    return (int) ((e % MAX_BYTE) ^ ((e / MAX_BYTE) % MAX_BYTE));
  }

  private static int sBox2(int input, int key) {
    assertByte(input);
    assertByte(key);

    return (((input + 1) * (key + 1)) % SBOX2_PRIME) % MAX_BYTE;
  }

  public static int sBox(int input, int key, int sBox) {
    assertByte(input);
    assertByte(key);

    switch(sBox) {
      case 0:
        return sBox0(input, key);
      case 1:
        return sBox1(input, key);
      case 2:
        return sBox2(input, key);
      default:
        System.err.println("Incorrect sBox.");
        System.exit(1);
        return 0;
    }
  }

  public static int keySchedule(int key, int schedule) {
    long extendedKey;

    assertWord(key);

    extendedKey = key | ((long)(key % MAX_BYTE))<<SIXTEEN;
    return (int)((extendedKey>>schedule) % MAX_BYTE);
  }


  public static int feistel(int plaintext, int key) {
    assertWord(plaintext);
    assertWord(key);

    int i;
    for(i=0; i < NUMBER_OF_SBOXES * KEY_ROUNDS; ++i) {
      int keyI, boxI, roundKey, left, right, newLeft, newRight;

      keyI = i / NUMBER_OF_SBOXES;
      boxI = i % NUMBER_OF_SBOXES;

      roundKey = keySchedule(key, keyI);
      left = plaintext % MAX_BYTE;
      right = (plaintext / MAX_BYTE) % MAX_BYTE;

      newLeft = right;
      newRight = left ^ sBox(right, roundKey, boxI);

      plaintext = newLeft + newRight * MAX_BYTE;
    }
    return plaintext;
  }

  public static int encrypt(int plaintext, int key1, int key2) {
    assertWord(plaintext);
    assertWord(key1);
    assertWord(key2);

    return feistel(feistel(plaintext, key1), key2);
  }

  public static long answer(int key1, int key2) {
    assertWord(key1);
    assertWord(key2);

    return key1 + key2*(ONE<<SIXTEEN);
  }

  public static void main(String[] args) {
    if(FROM_STDIN != 0) {
      java.util.Scanner sc = new java.util.Scanner(System.in);
      while(true) {
        int p1, c1, p2, c2, p3, c3;
        p1 = sc.nextInt();
        c1 = sc.nextInt();
        p2 = sc.nextInt();
        c2 = sc.nextInt();
        p3 = sc.nextInt();
        c3 = sc.nextInt();

        if(p1 == -1) {
          break;
        }
        long ans = Crypto3.challenge(p1, c1, p2, c2, p3, c3);
        System.out.println(ans);
      }
    } else {
      int tc, i;
      java.security.SecureRandom r = new java.security.SecureRandom();
      for(tc=0;tc<TESTCASES;++tc) {
        int key1 = Math.abs(r.nextInt()) % MAX_WORD;
        int key2 = Math.abs(r.nextInt()) % MAX_WORD;
        int[] plaintext = new int[3];
        int[] ciphertext = new int[3];
        for(i=0;i<3;++i) {
          plaintext[i] = Math.abs(r.nextInt()) % MAX_WORD;
          ciphertext[i] = encrypt(plaintext[i], key1, key2);
        }
        long ans = Crypto3.challenge(plaintext[0], ciphertext[0],
                                     plaintext[1], ciphertext[1],
                                     plaintext[2], ciphertext[2]);

        if(answer(key1, key2) != ans) {
          System.out.println("Incorrect answer");
          System.exit(1);
        } else {
          System.out.print(".");
        }
      }
    }
  }
}
