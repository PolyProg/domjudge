/////////////////////////////
// DO NOT SUBMIT THIS FILE //
/////////////////////////////

import java.util.Scanner;
import java.util.Vector;
import java.io.File;

public class MayaLib2 {

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
          Maya2 g2 = new Maya2();
          while (T-- != 0) {
                  read_case();
                  yourSol = g2.fetch_calendar(p);
                  if (yourSol != ourSol) {
                          System.out.printf("Incorrect\n");
                          System.exit(0);
                  }
          }
          System.out.printf("Correct f3f0a1d7da73769077dc6335cf022fba\n");
      } catch(Throwable t) {
        System.out.println(t);
      }
  }
}
