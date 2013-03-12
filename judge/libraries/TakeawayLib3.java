/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

public class TakeawayLib3 {
  public static void main(String args[]) {
     Takeaway3 t3 = new Takeaway3();
          if (t3.ready_for_contest().equals("We hereby digitally sign the hc2 terms and conditions")) {
                  System.out.printf("51785494e5ad0efbb1856b0a4a9b8422Correct\n");
                  return ;
          }
          if (t3.ready_for_contest().equals("Hiermit unterzeichnen wir digital die hc2 Bedingungen und Konditionen")) {
                  System.out.printf("51785494e5ad0efbb1856b0a4a9b8422Correct\n");
                  return ;
          }
          if (t3.ready_for_contest().equals("Par la presente, nous signons numeriquement les conditions de participation au concours hc2")) {
                  System.out.printf("51785494e5ad0efbb1856b0a4a9b8422Correct\n");
                  return ;
          }
          System.out.printf("Incorrect\n");
          return ;
  }
}
