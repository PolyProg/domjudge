/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class QuarantineLib2 {
  public static final int MAXN = 1000;
  private static final int MAXQ = 10000000;

  private static boolean p[][] = new boolean[MAXN][];
  private static int ps[][] = new int[MAXN+1][];

  private static int x_n = 429584; // initial seed

  private static java.util.Scanner sc;

  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;
      return (x_n & 0x3FFFFFFF);
  }

  private static void create_picture(int N){
          for (int i=0; i<N; i++) {
            p[i] = new boolean[MAXN];
                  for (int j=0; j<N; j++)
                          p[i][j] = (my_rand()%2)==1;
          }
          for (int i=0; i<=N; i++) {
            ps[i] = new int[MAXN+1];
                  ps[i][0] = ps[0][i] = 0;
          }
          for (int i=1; i<=N; i++)
                  for (int j=1; j<=N; j++)
                          ps[i][j] = ps[i][j-1] + ps[i-1][j] - ps[i-1][j-1] + (p[i-1][j-1]?1:0);
  }

  private static boolean judge_query(int r1, int c1, int r2, int c2){
          r2++; c2++;
          return ps[r2][c2] - ps[r2][c1] - ps[r1][c2] + ps[r1][c1] > (r2-r1)*(c2-c1)/2;
  }

  public static void main(String args[]){
          int T, Q, r1, c1, r2, c2;
          int N;	
          int solTeam, solJudge;
          sc = new java.util.Scanner(System.in);
          T = sc.nextInt();
          Q = MAXQ/T;
          for (int i=0; i<T; i++){
                  N = sc.nextInt();
                  create_picture(N);
                  Quarantine2.load_picture(p,N);
                  for (int j=0; j<Q; j++){
                          r1 = my_rand()%N;
                          c1 = my_rand()%N;
                          r2 = my_rand()%N;
                          c2 = my_rand()%N;
                          if (r2<r1) { int t = r1; r1 = r2; r2 = t; }
                          if (c2<c1) { int t = c1; c1 = c2; c2 = t;}
                          solTeam = Quarantine2.query(r1,c1,r2,c2)?1:0;
                          solJudge = judge_query(r1,c1,r2,c2)?1:0;
                          if (solTeam != solJudge){
                                  System.out.printf("INCORRECT - picture %d query %d received %d / expected %d\n",i+1,j+1,solTeam,solJudge);
                                  System.exit(0);
                          }
                  }
          }
          System.out.printf("OK - ea43a765b6871c13a7a9bfd32235c732\n");
  }
}
