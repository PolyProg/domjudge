import java.util.Scanner;

public class PlanetLib3 {

  private static Planet3 planet3;
  private static Scanner scanner;

  public static void main(String args[]) {
    planet3 = new Planet3();
    scanner = new Scanner(System.in);

    int n;
    int ntests = 0, ncorrect = 0;
    while ((n = scanner.nextInt())!= 0)
    {

        double[] cityLat = new double[n];
        double[] cityLong = new double[n];
	for (int i = 0; i < n; i++)
	{
	    cityLat[i] = scanner.nextDouble();
	    cityLong[i] = scanner.nextDouble();
	}
	int ans, ret;
        ans = scanner.nextInt();
        ntests++;
        if (ans == (ret = planet3.countReachableCountries(n, cityLat, cityLong)))
        {
            ncorrect++;
            System.out.print(".");
        }
        else System.out.print("x"); 
        //else printf("x");
    }
    System.out.print("\nNumber of tests:           " + ntests + "\n");
    System.out.print(  "Number of correct answers: "+ ncorrect + "\n");
    if (ntests == ncorrect) System.out.print("Congratulations! 531eeb89587b3171bfcfbcbfc5a41e9f\n");
    else System.out.print("Wrong answer!\n");

  }
}
