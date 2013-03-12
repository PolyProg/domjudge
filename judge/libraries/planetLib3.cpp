//////////////////////////
// DO NOT SUBMIT THIS FILE
//////////////////////////

#include <stdio.h>
#include "planetLib3.hpp"

int main()
{
    int n;
    int ntests = 0, ncorrect = 0;
    while (1 == scanf("%d", &n) && n != 0)
    {
        double* cityLat = new double[n];
        double* cityLong = new double[n];
        for (int i = 0; i < n; i++)
            scanf("%lf%lf", &cityLat[i], &cityLong[i]);
        int ret;
        scanf("%d", &ret);
        ntests++;
        int ans;
        if (ret == (ans = countReachableCountries(n, cityLat, cityLong)))
        {
            ncorrect++;
            printf(".");
        }
        else printf("x");
    }
    printf("\nNumber of tests:           %d\n", ntests);
    printf(  "Number of correct answers: %d\n", ncorrect);
    if (ntests == ncorrect) printf("Congratulations! 531eeb89587b3171bfcfbcbfc5a41e9f\n");
    else printf("Wrong answer!\n");

    return 0;
}
