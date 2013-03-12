//////////////////////////
// DO NOT SUBMIT THIS FILE
//////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "planetLib1.h"

// Robert's RNG
static int x_n = 773137898;
static int my_rand()
{
  const int A = 1103515245;
  const int C = 12345;
  int res;
  x_n = A*x_n + C;

  res = (x_n & 0x3FFFFFFF) / (65536);
  return res;
}

static double my_drand()
{
    return (my_rand() * (1 << 14) + my_rand()) / (double)(1 << 28);
}

int main()
{
    int n;
    int ntests = 0, ncorrect = 0;
    while (1 == scanf("%d", &n) && n != 0)
    {
	int automatic = 0;
	if (n < 0) {n = -n; automatic = 1;}
	
        double* cityLat = (double*) malloc(n * sizeof(double));
        double* cityLong = (double*) malloc(n * sizeof(double));
        double startLat, walkDistance, planetRadius;
        scanf("%lf%lf%lf", &startLat, &walkDistance, &planetRadius);
	if (automatic)
	{
	    int i;
	    for (i = 0; i < n; i++)
	    {
		cityLat[i] = my_drand() * 180.0 - 90;
		cityLong[i] = my_drand() * 360.0;
	    }
	}
	else
	{
	    int i;
	    for (i = 0; i < n; i++)
		scanf("%lf%lf", &cityLat[i], &cityLong[i]);
	}
	int ans, ret;
        scanf("%d", &ans);
        ntests++;
        if (ans == (ret = countReachable(startLat, walkDistance, planetRadius, n, cityLat, cityLong)))
        {
            ncorrect++;
            printf(".");
        }
        //else {printf("x %d\n", ret);} 
        else printf("x");
        free(cityLat);
        free(cityLong);
    }
    printf("\nNumber of tests:           %d\n", ntests);
    printf(  "Number of correct answers: %d\n", ncorrect);
    if (ntests == ncorrect) printf("Congratulations! 02a979deadeff4795edb020a544f9656\n");
    else printf("Wrong answer!\n");

    return 0;
}
