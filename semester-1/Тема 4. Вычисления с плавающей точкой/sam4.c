#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ~3 seconds
// N = 200000000
// S = 0.99999999500000003
int main(void) {
    double Scor = 0.0, S = 0.0, f, eps = 0.5e-8;
    double fcor = 0.0, cor = 0.0;

    long N;
    for (N = 1L; fabs((double)1 - S) > eps; N++) {
        f = (double)1 / N / (N + 1);
        fcor = f - cor;
        Scor = S + fcor;
        cor = (Scor - S) - fcor;
        S = Scor;
    }

    double delta = fabs((double)1 - S);
    int m = 0, k = 0, n;
    while (delta <= (double)1 / 2 * pow((long)10, -k))
        k++;
    k--;

    printf("%.9lf\n%.9lf\n%.9lf\n%ld\n%d\n",
           1.0, S, eps, N, m + k + 1 - 1);

    return 0;
}
