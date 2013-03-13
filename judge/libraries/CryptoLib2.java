public class CryptoLib2 {

  private static final int TESTCASES = 100000;
  private static final int MAX_BYTE = 1<<8;
  private static final int MAX_WORD = 1<<16;
  private static final int SBOX1_PRIME = 65537;
  private static final int SBOX2_PRIME = 257;
  private static final int NUMBER_OF_SBOXES = 3;
  private static final int KEY_ROUNDS = 16;

  private static int x_n = 429584; // initial seed

  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;

      return (x_n & 0x3FFFFFFF);
  }

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

  public static void main(String[] args) {
    int tc, i;
    for(tc=0;tc<TESTCASES;++tc) {
      int key1 = Math.abs(my_rand()) % MAX_WORD;
      int key2 = Math.abs(my_rand()) % MAX_WORD;
      int plaintext = Math.abs(my_rand()) % MAX_WORD;
      int ciphertext = encrypt(plaintext, key1, key2);
      int ans = Crypto2.decrypt(ciphertext, key1, key2);
      if(plaintext != ans) {
        System.out.println("Incorrect answer");
        System.exit(0);
      }
    }
    System.out.print("OK - 983b6576e1b54131fc6d1c5a6629d176\n");
  }
}
