import java.util.Scanner;

public class PlanetLib2 {

  private static Planet2 planet2;
  private static Scanner scanner;

  public static void main(String args[]) {
    planet2 = new Planet2();
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
        if (ans == (ret = planet2.countBorders(n, cityLat, cityLong)))
        {
            ncorrect++;
            System.out.print(".");
        }
        else System.out.print("x"); 
        //else printf("x");
    }
    System.out.print("\nNumber of tests:           " + ntests + "\n");
    System.out.print(  "Number of correct answers: "+ ncorrect + "\n");
    if (ntests == ncorrect) System.out.print("Congratulations! 93fc44df479ed75123bff884f4060ace\n");
    else System.out.print("Wrong answer!\n");

  }
}
