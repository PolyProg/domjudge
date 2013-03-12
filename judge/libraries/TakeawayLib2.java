/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class TakeawayLib2 {
 private static final int MAX_N = 50;
 private static final int UNDEF  = -1;

  private static int p[];
  private static int n[];
  private static int t[];
  private static int N, T;
  private static int ourMin, ourMax;
  private static int yourMin, yourMax;
  private static int cnt;
  private static java.util.Scanner scanner;

  private static void read_case() {
          N = scanner.nextInt();
          p = new int[N];
          n = new int[N];
          t = new int[N];
          for (int i=0; i<N; i++) {
            p[i] = scanner.nextInt();
            n[i] = scanner.nextInt();
            t[i] = scanner.nextInt();
          }
          ourMin = scanner.nextInt();
          ourMax = scanner.nextInt();
          yourMin = UNDEF;
          yourMax = UNDEF;
          cnt = 0;
  }

  public static void min_balloons(int yourMinBound) {
          yourMin = yourMinBound;
          cnt++;
  }

  public static void max_balloons(int yourMaxBound) {
          yourMax = yourMaxBound;
          cnt++;
  }

  public static void main(String args[]) {
    try {
      		Takeaway2 t2 = new Takeaway2();
          scanner = new java.util.Scanner(System.in);
          T = scanner.nextInt();
          while (T-- != 0)	{
                  read_case();
                  t2.count_balloons(N,p,n,t);
                  if (cnt!=2 || ourMin!=yourMin || ourMax!=yourMax) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
                  
          }
          System.out.printf("Correctf52cac7981d3b301410e7cab97a3c2a5\n");
    } catch(Throwable t) {
      System.out.println(t);
    }
  }
}
