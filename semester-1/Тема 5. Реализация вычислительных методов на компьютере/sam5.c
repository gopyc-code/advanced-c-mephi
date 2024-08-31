#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double root(short isleft) {
    double a = 0.0, b = 4.0, m;

    while ((b - a) > 1e-7) {
        m = (a + b) / 2;
        if (((sin(m) - (double)0.4) > 0) == isleft)
            a = m;
        else
            b = m;
    }
    printf("%.7lf\n%.8lf\n", m,
           fabs((sin(b) - sin(a)) * 0.5));
    return m;
}

void descr(double x) {
    double S = 0.0, Scor = 0.0, cor = 0.0;
    double fcor = 0.0, i, f = x;

    for (long N = 0; fabs(sin(x) - S) > 1e-6; N++) {
        i = (double)N;
        if (N) f *= -x / (i * 2.0 + 1.0) * x / (i * 2.0);

        fcor = f - cor;
        Scor = S + fcor;
        cor = (Scor - S) - fcor;
        S = Scor;
    }
    printf("%.6lf\n%ld\n", S, (long)i);
}

int main(void) {
    descr(root(1));
    descr(root(0));

    return 0;
}
