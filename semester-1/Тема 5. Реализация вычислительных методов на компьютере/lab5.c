#include <stdio.h>
#include <stdlib.h>

void root(short isleft) {
    double a = -2.0, b = 2.0, m;

    while ((b - a) > 1e-10) {
        m = (a + b) / 2;
        if ((m * m - m - (double)1 > 0) == isleft)
            a = m;
        else
            b = m;
    }
    printf("%.10lf\n", m);
}

int main(void) {
    root(1);
    root(0);

    return 0;
}
