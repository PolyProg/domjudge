/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class QuarantineLib1 {
  public static final int MAXN = 1000;
  private static final int MAXQ = 10000000;

  private static boolean p[][] = new boolean[MAXN][];
  private static int row[] = new int[MAXN];
  private static int col[] = new int[MAXN];

  private static int x_n = 429584; // initial seed

  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;

      return (x_n & 0x3FFFFFFF);
  }

  private static void create_picture(int N){
          for (int i=0; i<N; i++)
                  row[i] = col[i] = 0;
          for (int i=0; i<N; i++) {
                  p[i] = new boolean[MAXN];
                  for (int j=0; j<N; j++){
                          p[i][j] = (my_rand()%2)==1;
                          row[i] += p[i][j] ? 1:0;
                          col[j] += p[i][j] ? 1:0;
                  }
                }
  }

  private static boolean judge_query(int r, int c, int N){
          return ( row[r] + col[c] - (p[r][c]?1:0) ) >= N;
  }

  public static void main(String args[]){
          int T, Q, r, c;
          int N;
          int solTeam, solJudge;
          java.util.Scanner sc = new java.util.Scanner(System.in);
          T = sc.nextInt();
          Q = MAXQ/T;
          for (int i=0; i<T; i++){
                  N = sc.nextInt();
                  create_picture(N);
                  Quarantine1.load_picture(p,N);
                  for (int j=0; j<Q; j++){
                          r = my_rand()%N;
                          c = my_rand()%N;
                          solTeam = Quarantine1.query(r,c)?1:0;
                          solJudge = judge_query(r,c,N)?1:0;
                          if (solTeam != solJudge){
                                  System.out.printf("INCORRECT - test %d received %d / expected %d\n",i+1,solTeam,solJudge);
                                  System.exit(0);
                          }
                  }
          }
          System.out.printf("OK - f7e32100ed674311bdff7f3896936962\n");
  }
}
