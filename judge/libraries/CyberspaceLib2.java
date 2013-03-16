/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class CyberspaceLib2 {
  private static int count_bits(int n){
          int cnt=0;
          while (n!=0){
                  n = n & (n-1);
                  cnt++;
          }
          return cnt;
  }

  private static int judge_place_exit(int N, int M){
          int best=(1<<M)-1;
          for (int i=0; i<=(1<<10); i++)
                  if ( count_bits(i)==M && Math.abs(i+i-N)<Math.abs(N-best-best) )
                          best = i;
          return best;
  }

  public static void main(String args[]) {
          int solJudge, solTeam;
          for (int i=0; i<=(1<<10); i++)
                  for (int j=0; j<10; j++) {
                          solTeam = Cyberspace2.place_exit(i,j);
                          solJudge = judge_place_exit(i,j);
                          if ( count_bits(solTeam)!=j || 
                               Math.min(solTeam+solTeam-i,i-solTeam-solTeam) != Math.min(solJudge+solJudge-i,i-solJudge-solJudge) ){
                                  System.out.printf("INCORRECT : N=%d M=%d , got %d / expected %d\n",i,j,solTeam,solJudge);
                                  System.exit(0);
                          }
                  }
          System.out.printf("OK - dbcd021e0b38b94aa0d34456190233a0\n");
  }
}
