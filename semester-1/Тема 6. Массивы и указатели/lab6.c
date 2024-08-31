#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    /*
    int minm, maxm, m[40];
    scanf("%d%d", &minm, &maxm);

    for (int i = 0; i < 40; i++) {
        m[i] = minm + rand() %
        (maxm - minm + 1);
    }

    for (int i = 0; i < 40; i++)
        printf("%2d %d\n", i, m[i]);
    */

    int m[40];

    for (int i = 0; i < 40; i++)
        scanf("%d", &m[i]);

    int a;
    scanf("%d", &a);

    int s = 0, c = 0;
    for (int i = 0; i < 40; i++) {
        if (m[i] > a) {
            s += m[i];
            c++;
        }
    }

    double mid = (c) ? (double)s / c : 0;
    int mina = INT_MAX, minc = 0; c = 0;
    for (int i = 0; i < 40; i++) {
        if (m[i] > mid) {
            c++;
            if (mina > m[i]) {
                mina = m[i];
                minc = 1;
            } else if (mina == m[i])
                minc++;
        }
    }
    printf("%.4lf\n%d\n%d %d\n",
           mid, c, mina, minc);
    return 0;
}
