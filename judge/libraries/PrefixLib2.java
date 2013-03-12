public class PrefixLib2 {
  public static void main(String args[]){
    java.util.Scanner sc = new java.util.Scanner(System.in);
    Prefix2 p2 = new Prefix2();
    int ntc = sc.nextInt();
    int tc;
    for(tc=0;tc<ntc;++tc) {
      int nlines = sc.nextInt();
      String[] array = new String[nlines];
      int i;
      for(i=0;i<nlines;++i) {
        array[i] = sc.next();
      }

      boolean result = p2.isFullPrefixSet(nlines, array);
      System.out.printf("%d\n", result?1:0);
    }
  }
}
