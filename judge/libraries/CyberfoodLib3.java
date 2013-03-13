/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class CyberfoodLib3 {
  private static int x_n = 429619; // initial seed
  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;

      return (x_n & 0x3FFFFFFF);
  }

  public static final int TREES = 10;
  public static final int LEAVES = 100;
  public static final int FORESTS = 10000;

  private static double p[] = new double[TREES];
  private static double t[] = new double[LEAVES];
  private static double s[] = new double[LEAVES];
  private static double m[] = new double[LEAVES];
  private static int index;

  private static void create_forest(){
          for (int i=0; i<TREES; i++)
                  p[i] = (1 + my_rand()%999) / 1000.0;
          for (int i=0; i<LEAVES; i++)
                  t[i] = (1 + my_rand()%999) / 1000.0;
          index = 0;
  }

  private static void oracle(){
          int d=0;
          for (int i=1; i<TREES; i++)
                  d = ( p[i] > p[d] ) ? i : d;
          for (int i=0; i<LEAVES; i++)
                  m[i] += ( t[i] < p[d] ) ? 1:0;
  } 

  public static boolean eat(int id){
          if (index>LEAVES){
                  System.out.printf("No leaves left on the tree\n");
                  System.exit(0);
          }
          s[index] += ( t[index] < p[id-1] )?1:0;
          return t[index++] < p[id-1];
  }

  public static void main(String args[]) {
          for (int f=0; f<FORESTS; f++){
                  create_forest();
                  Cyberfood3.happy_meal();
                  oracle();
          }
          for (int i=0; i<LEAVES; i++){
                  s[i] = s[i]/FORESTS + ((i!=0) ? s[i-1] : 0);
                  m[i] = m[i]/FORESTS + ((i!=0) ? m[i-1] : 0);
          }
          boolean ok = s[LEAVES-1]/m[LEAVES-1] >= 0.9;

          if(ok) {
            System.out.printf("CORRECT - b35b997444a2da663d387a90bdb52e73\n");
          } else {
            System.out.printf("%.1lf%% optimal\n", s[LEAVES-1]/m[LEAVES-1]*100);
            System.out.printf("INCORRECT\n");
          }
  }
}
