/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class CyberfoodLib1 {
  static int L, C;

  static private long bijective_encrypt(long x){
	return x ^ 0x7FFFFDEADBEEFFFFL;
  }

  static private long bijective_decrypt(long x){
	return x ^ 0x7FFFFDEADBEEFFFFL;
  }

  public static long eat(long prev){
          prev = bijective_decrypt(prev);
          if (prev<1L*L)
                  prev++;
          else
                  prev = (prev+1-L)%C + L;
          return bijective_encrypt(prev);
  }

  public static void main(String args[]){
          byte[] removing_memory = new byte[32*1024*1024];
          int T;
          int solTeam, solJudge;
          java.util.Scanner sc = new java.util.Scanner(System.in);
          T = sc.nextInt();
          for (int i=0; i<T; i++){
                  L = sc.nextInt();
                  C = sc.nextInt();
                  solTeam = Cyberfood1.count_flavours(bijective_encrypt(1L));
                  solJudge = L+C-1;
                  if (solTeam != solJudge){
                          System.out.printf("INCORRECT - test %d received %d / expected %d\n",i+1,solTeam,solJudge);
                          System.exit(0);
                  }
          }
          System.out.printf("CORRECT - 9f3c69f744434f06c2bfa4a100c30384\n");
  }
}
