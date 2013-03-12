import java.util.Scanner;

public class PlanetLib1 {

  private static Planet1 planet1;
  private static Scanner scanner;
  private static int x_n = 773137898;

  public static void main(String args[]) {
    planet1 = new Planet1();
    scanner = new Scanner(System.in);

    int n;
    int ntests = 0, ncorrect = 0;
    while ((n = scanner.nextInt())!= 0)
    {
	boolean automatic = false;
	if (n < 0) {n = -n; automatic = true;}
	
        double[] cityLat = new double[n];
        double[] cityLong = new double[n];
        double startLat, walkDistance, planetRadius;
        //scanf("%lf%lf%lf", &startLat, &walkDistance, &planetRadius);
	startLat = scanner.nextDouble();
	walkDistance = scanner.nextDouble();
	planetRadius = scanner.nextDouble();
	if (automatic)
	{
	    for (int i = 0; i < n; i++)
	    {
		cityLat[i] = my_drand() * 180.0 - 90;
		cityLong[i] = my_drand() * 360.0;
	    }
	}
	else
	{
	    for (int i = 0; i < n; i++)
	    {
		cityLat[i] = scanner.nextDouble();
		cityLong[i] = scanner.nextDouble();
	    }
	}
	int ans, ret;
        ans = scanner.nextInt();
        ntests++;
        if (ans == (ret = planet1.countReachable(startLat, walkDistance, planetRadius, n, cityLat, cityLong)))
        {
            ncorrect++;
            System.out.print(".");
        }
        else System.out.print("x"); 
        //else printf("x");
    }
    System.out.print("\nNumber of tests:           " + ntests + "\n");
    System.out.print(  "Number of correct answers: "+ ncorrect + "\n");
    if (ntests == ncorrect) System.out.print("Congratulations! 02a979deadeff4795edb020a544f9656\n");
    else System.out.print("Wrong answer!\n");

  }

  private static int my_rand()
  {
    final int A = 1103515245;
    final int C = 12345;
    x_n = A*x_n + C;

    int res = (x_n & 0x3FFFFFFF) / (65536);
    return res;
  }

  private static double my_drand()
  {
    return (my_rand() * (1 << 14) + my_rand()) / (double)(1 << 28);
  }
}
