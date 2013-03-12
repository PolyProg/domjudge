/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

class GiftLib2 {

  private static final int MAX_Q = 50;
  private static final int MAX_T = 100;

  private static int years[];
  private static int qCnt, T;

  public static int is_heidi_in(double year) {
          if (++qCnt > MAX_Q) {
                  System.out.printf("Too many queries\n");
                  System.exit(0);
          }
          if (year >= years[T])
                  return 0;
          else //if (year < years[T])
                  return 1;
  }

  private static void read_cases() {
  try {
      java.util.Scanner sc = new java.util.Scanner(System.in);

          T = sc.nextInt();
          years = new int[MAX_T];
          int t = T;
          while (t-- != 0)
              years[t] = sc.nextInt();
      } catch(Throwable t) {
        System.out.println(t);
      }
  }

  public static void main(String args[]) {
          read_cases();
          Gift2 g2 = new Gift2();
          int maxi = 0;
          while (T-- != 0) 	{
                  qCnt = 0;
                  int answer = g2.find_heidi();
                  if (answer != years[T]) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
                  if (qCnt>maxi)
                          maxi = qCnt;
          }
          System.out.printf("Correct baeb67954db7e2097645e8013ab2e508\n");
  }
}
