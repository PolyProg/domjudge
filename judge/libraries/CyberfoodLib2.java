/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class CyberfoodLib2 {
  private static long solJudge, solTeam;
  private static int nSamples;
  private static int score=0;

  private static int x_n = 429588; // initial seed
  private static int my_rand()
  {
      final int A = 1664525;
      final int C = 1013904223;
      x_n = A*x_n + C;

      return (x_n & 0x3FFFFFFF);
  }
  private static long my_rand_long() {
    return my_rand() + my_rand()*0x40000000L;
  }

  public static long eat(){
          if (nSamples==0){
                  System.out.printf("Too many samples\n");
                  System.exit(0);
           }
           nSamples--;
           return 1+my_rand_long()%solJudge;
  }

  public static void main(String args[]) {
          int T;
          double tol;
          java.util.Scanner sc = new java.util.Scanner(System.in);
          T = sc.nextInt();
          for (int i=0; i<T; i++){
                  solJudge = sc.nextLong();
                  tol = sc.nextDouble();
                  nSamples = (int) ( Math.ceil( Math.log(1/(1-0.95)) / Math.log(0.01*tol+1) ) );
                  solTeam = Cyberfood2.estimate_flavours(nSamples);
                  score += (Math.max(solTeam,solJudge)-Math.min(solTeam,solJudge) <= tol*solJudge*0.01)?1:0;
          }
          if ( score/(0.01*T) >= 95.00 ) {
                  System.out.printf("CORRECT - 780977ab23bb95e3b52b1af9408fce96\n");
          }
          else {
                  System.out.printf("Solved %.3lf%% of tests\n", score/(0.01*T));
                  System.out.printf("INCORRECT\n");
          }
  }
}
