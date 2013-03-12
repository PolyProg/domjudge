/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

class GiftLib1 {

  private static final int MAX_Q = 0;
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
          Gift1 g1 = new Gift1();
          int maxi = 0;
          while (T-- != 0) 	{
                  qCnt = 0;
                  int answer = g1.find_heidi();
                  if (answer != years[T]) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
                  if (qCnt>maxi)
                          maxi = qCnt;
          }
          System.out.printf("Correct 1ac0b464eb2b2ab64c07c357246d46b1\n");
  }
}
