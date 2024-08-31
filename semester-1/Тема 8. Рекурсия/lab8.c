#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


unsigned long over = 0, depth = 0;

unsigned long f(unsigned long n, unsigned long m);
int sum_over(unsigned long n, unsigned long m);


int main(void) {
    unsigned long a, b;
    scanf("%u%u", &a, &b);

    unsigned long r = f(a, b);
    if (over == 1) {
        printf("overflow\n");
        return 0;
    } else if (depth >= 1e4) {
        printf("endless\n");
        return 0;
    } else
        printf("%lu\n", r);

    return 0;
}

int sum_over(unsigned long n, unsigned long m) {
    return (n > ULONG_MAX - m);
}

unsigned long f(unsigned long n, unsigned long m) {
    if (over)
        return 0;

    if (sum_over(n, m)) {
        over = 1;
        return 0;
    }
    if (depth >= 1e4)
        return 0;
    depth += 1;

    if ((n + m) % 2)
        return (n > m) ? m : n;

    unsigned long f1 = f((n + m) / 2, m),
    f2 = f(n, (n + m) / 2);
    if (sum_over(f1, f2)) {
        over = 1;
        return 0;
    }
    return f1 + f2;
}
