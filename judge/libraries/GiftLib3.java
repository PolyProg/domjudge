/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////


class GiftLib3 {
  private static final int MAX_Q = 200;
  private static final int MAX_T = 1000;

  private static int years[];
  private static int qCnt, T;
  private static boolean canLie;
  private static java.util.Scanner sc;
  private static int lCnt;

  private static int x_n = 879788114;
  private static int myrand()
  {
    final int A = 1103515245;
    final int C = 12345;
    int res;
    x_n = A*x_n + C;

    res = (x_n & 0x3FFFFFFF) / (65536);
    return res;
  }

  private static boolean is_heidi_really_in(double year) {
          if (++qCnt > MAX_Q) {
                  System.out.printf("Too many queries\n");
                  System.exit(0);
          }
          if (year >= years[T])
                  return false;
          else //if (year < years[T])
                  return true;
  }

  public static boolean is_heidi_in(double year) {
          boolean correct = is_heidi_really_in(year);
          if (canLie && myrand()%(1+T/100)< 1 && year > 100000 && year < 900000) {
                  canLie = false;
                  ++lCnt;
                  return !correct;
          }
          else {
                  canLie = true;
                  return correct;
          }		
  }

  private static void read_cases() {
      try{
          sc = new java.util.Scanner(System.in);
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
          Gift3 g3 = new Gift3();
          int maxi = 0;
          while (T-- != 0) 	{
                  qCnt = 0;
                  lCnt = 0;
                  canLie = (myrand()%2 == 1);
                  TAnswer answer = g3.find_heidi();
                  if (answer.year1 != years[T] && answer.year2 != years[T]) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
                  if (qCnt>maxi)
                          maxi = qCnt;
          }
              System.out.printf("Correct f11cc9de4736bbc2719aa318ecfbecf2\n");
  }
}

class TAnswer {
  public int year1;
  public int year2;
  public TAnswer(){}
  public TAnswer(int year1, int year2) {
    this.year1 = year1;
    this.year2 = year2;
  }
}
