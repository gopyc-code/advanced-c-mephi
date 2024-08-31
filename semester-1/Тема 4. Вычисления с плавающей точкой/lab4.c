#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    double S = 0.0, Scor = 0.0, cor = 0.0;
    double R = 0.0, fcor = 0.0, f = 0.0, i;
    for (long N = 1; N <= 2e+8; N++) {
        i = (double)N;
        f = sqrt((1 + 3 * i * i) / (3 + i * i));
        R += f;
        fcor = f - cor;
        Scor = S + fcor;
        cor = (Scor - S) - fcor;
        S = Scor;
        if (N && !(N % (long)2e+7))
            printf("%9d%18.4lf%18.4lf%10.4lf\n", N, R, Scor, R - Scor);
    }

    return 0;
}
