/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

import java.util.Scanner;

public class TakeawayLib1 {
  private static final int MAX_N = 50;
  private static final int UNDEF = -1;

  private static int p[];
  private static int n[];
  private static int t[];
  private static int N;
  private static int T;
  private static int ourGold;
  private static int ourSilver;
  private static int ourBronze;
  private static int yourGold;
  private static int yourSilver;
  private static int yourBronze;
  private static int cnt;
  private static Scanner scanner;

  static void read_case() {
 	N = scanner.nextInt();
        p = new int[N];
        n = new int[N];
        t = new int[N];
          for (int i=0; i<N; i++) {
            p[i] = scanner.nextInt();
            n[i] = scanner.nextInt();
            t[i] = scanner.nextInt();
          }
        ourGold = scanner.nextInt();
        ourSilver = scanner.nextInt();
        ourBronze = scanner.nextInt();
        yourGold = UNDEF;
        yourSilver = UNDEF;
        yourBronze = UNDEF;
        cnt = 0;
  }

  public static void gold_medalist(int yourGoldMedalist) {
          yourGold = yourGoldMedalist;
          cnt++;
  }

  public static void silver_medalist(int yourSilverMedalist) {
          yourSilver = yourSilverMedalist;
          cnt++;
  }

  public static void bronze_medalist(int yourBronzeMedalist) {
          yourBronze = yourBronzeMedalist;
          cnt++;
  }

  public static void main(String args[]) {
  	scanner = new Scanner(System.in);
        Takeaway1 tk1 = new Takeaway1();
        T = scanner.nextInt();
          while (T-- != 0)	{
                  read_case();
                  tk1.find_medalists(N,p,n,t);
                  if (cnt!=3 || ourGold!=yourGold || ourSilver!=yourSilver || ourBronze!=yourBronze) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
                  
          }
          System.out.printf("Correct12ddc26cc360428ead273b131b509946\n");
  }
}
