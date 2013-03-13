/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class QuarantineLib3 {
  private static final int MAXN = 1002;
  private static final int MAXQ = 1000000;

  private static int bit[][] = new int[MAXN][];
  private static int N;

  private static int x_n = 429584; // initial seed

  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;
      return (x_n & 0x3FFFFFFF);
  }

  private static void judge_load_picture(int n){
          N = n + 1;
          for (int i=0; i<=N; i++) {
            bit[i] = new int[MAXN];
                  for (int j=0; j<=N; j++)
                          bit[i][j] = 0;
          }
  }

  private static boolean judge_query(int r, int cc){
          r++; cc++;
          int c;
          int ps=0;
          while (r!=0){
                  c = cc;
                  while (c!=0){
                          ps += bit[r][c];
                          c -= c & -c;
                  }
                  r -= r & -r;
          }
          return (ps%2)==1;
  }

  private static void toggle_bit(int r, int cc){
          int c;
          while (r<=N){
                  c = cc;
                  while (c<=N){
                          bit[r][c]++;
                          c += c & -c;
                  }
                  r += r & -r;
          }
  }

  private static void judge_toggle(int r1, int c1, int r2, int c2){
          r1++; c1++; r2++; c2++;
          if (r1>r2) {int t=r1;r1=r2;r2=t;}
          if (c1>c2) {int t=c1;c1=c2;c2=t;}
          r2++; c2++;
          toggle_bit(r1,c1);
          toggle_bit(r2,c1);
          toggle_bit(r1,c2);
          toggle_bit(r2,c2);
  }

  public static void main(String args[]){
     java.util.Scanner sc = new java.util.Scanner(System.in);
          int T, Q, r1, c1, r2, c2;
          int N;	
          int solTeam, solJudge;
          int cnt;
          T = sc.nextInt();
          for (int i=0; i<T; i++){
                  cnt=0;
                  N = sc.nextInt();
                  Quarantine3.load_picture(N);
                  judge_load_picture(N);
                  Q = MAXQ/T;
                  for (int j=0; j<Q; j++){
                          if (my_rand()%2!=0){
                                  r1 = my_rand()%N;
                                  c1 = my_rand()%N;
                                  r2 = my_rand()%N;
                                  c2 = my_rand()%N;
                                  Quarantine3.toggle(r1,c1,r2,c2);
                                  judge_toggle(r1,c1,r2,c2);
                          }
                          else{
                                  cnt++;
                                  r1 = my_rand()%N;
                                  c1 = my_rand()%N;
                                  solTeam = Quarantine3.query(r1,c1)?1:0;
                                  solJudge = judge_query(r1,c1)?1:0;
                                  if (solTeam != solJudge){
                                          System.out.printf("INCORRECT - picture %d query %d received %d / expected %d\n",i+1,cnt,solTeam,solJudge);
                                          System.exit(0);
                                  }
                          }
                  }
          }
          System.out.printf("OK - c124e57669a5e82fc7c3d5cee8d1642b\n");
  }
}
