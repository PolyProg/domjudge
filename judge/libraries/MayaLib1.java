/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

import java.util.Scanner;
import java.util.Vector;
import java.io.File;

public class MayaLib1 {

  private static Vector<Vector<Integer> > p;
  private static int ourSol;
  private static int yourSol;
  private static int T;
  private static Scanner sc;

  static void read_case() {
          int R, C;
          R = sc.nextInt();
          p = new Vector<Vector<Integer> > (R+1);
          for (int i=0; i<=R; i++) {
                  C = sc.nextInt();
                  p.add(new Vector<Integer> (C));
                  for (int j=0; j<C; j++)
                    p.get(i).add(Integer.valueOf(sc.nextInt()));
          }
          ourSol = sc.nextInt();
  }

  public static void main(String args[]) {
      try{
          sc = new Scanner(System.in);
          T = sc.nextInt();
          Maya1 g2 = new Maya1();
          while (T-- != 0) {
                  read_case();
                  yourSol = g2.fetch_calendar(p)?1:0;
                  if (yourSol != ourSol) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
          }
          System.out.printf("Correct dd4ecd6fa7ca205a407d8d6dcaddaa64\n");
      } catch(Throwable t) {
        System.out.println(t);
      }
  }
}
