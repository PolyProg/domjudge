public class PrefixLib1 {
  public static void main(String args[]){
    java.util.Scanner sc = new java.util.Scanner(System.in);
    Prefix1 p1 = new Prefix1();
    int ntc = sc.nextInt();
    int tc;
    for(tc=0;tc<ntc;++tc) {
      int nlines = sc.nextInt();
      String[] array = new String[nlines];
      int i;
      for(i=0;i<nlines;++i) {
        array[i] = sc.next();
      }

      boolean result = p1.isValidPrefixSet(nlines, array);
      System.out.printf("%d\n", result?1:0);
    }
  }
}
