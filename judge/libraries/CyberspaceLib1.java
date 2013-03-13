/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class CyberspaceLib1 {

  private static final int MAX_N = 1000001;

  private static int x_n = 429584; // initial seed

  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;

      return (x_n & 0x3FFFFFFF);
  }

  private static int judge_entry_time(int a[], int p[], int N){
          int e=0;
          for (int i=0; i<=N; i++)
                  e = Math.max(a[i],e) + p[i];
          return e;
  }

  public static void main(String args[]){
    java.util.Scanner sc = new java.util.Scanner(System.in);
          int T;
          int solTeam, solJudge;
          int a[] = new int[MAX_N];
          int p[] = new int[MAX_N];
          int N;
          T = sc.nextInt();
          for (int i=0; i<T; i++){
                  N = sc.nextInt();
                  a[0] = my_rand()%1000;
                  p[0] = my_rand()%1000;
                  for (int j=1; j<=N; j++){
                          a[j] = (my_rand()%1000) + a[j-1];
                          p[j] = my_rand()%1000;
                  }
                  solJudge = judge_entry_time(a,p,N);
                  solTeam = Cyberspace1.entry_time(a,p,N);
                  if (solTeam != solJudge){
                          System.out.printf("INCORRECT - test %d received %d / expected %d\n",i+1,solTeam,solJudge);
                          System.exit(0);
                  }
          }
          System.out.printf("OK - b54a18363981c7c9e8c40366ce1a9f8f\n");
  }
}
