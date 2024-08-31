#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fill(long a, long b, long *m, long n);
void print(long *p, long *q);
void replace(long *a, long *b, long k);

int main(void) {
    long a1, b1, a2, b2, k;
    scanf("%ld%ld%ld%ld%ld",
          &a1, &b1, &a2, &b2, &k);

    long m1[8], m2[12];

    fill(a1, b1, m1, 8);
    fill(a2, b2, m2, 12);

    print(m1, m1 + 8 - 1);
    printf("\n");

    print(m2, m2 + 12 - 1);
    printf("\n");

    replace(m1 + 8, m2, k);
    replace(m2 + 12, m1, k);
    replace(m1 + 8, m1, k);

    print(m1, m1 + 8 - 1);
    printf("\n");

    print(m2, m2 + 12 - 1);

    return 0;
}

void fill(long a, long b, long *m, long n) {
    for (long i = 0; i < n; i++)
        m[i] = a * (i + b);
}

void print(long *p, long *q) {
    for (long i = 0; i <= q - p; i++)
        printf("%5ld", i + 1);
    printf("\n");

    for (long i = 0; i <= q - p; i++)
        printf("%5ld", p[i]);
    printf("\n");
}

void replace(long *a, long *b, long k) {
    long t;
    for (long i = 0; i < k; i++) {
        t = a[- k + i];
        a[- k + i] = b[i];
        b[i] = t;
    }
}
