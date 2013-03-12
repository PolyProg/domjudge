public class PrefixLib3 {
  public static void main(String args[]){
    java.util.Scanner sc = new java.util.Scanner(System.in);
    Prefix3 p3 = new Prefix3();
    int ntc = sc.nextInt();
    int tc;
    for(tc=0;tc<ntc;++tc) {
      int nlines = sc.nextInt();
      String[] array = new String[nlines];
      int i;
      for(i=0;i<nlines;++i) {
        array[i] = sc.next();
      }

      int result = p3.minimalNumberToMakeFull(nlines, array);
      System.out.printf("%d\n", result);
    }
  }
}
