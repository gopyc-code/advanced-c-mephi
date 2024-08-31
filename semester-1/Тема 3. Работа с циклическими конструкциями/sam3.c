#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// multiplication overflow
short mof(long a, long b) {
    if (!(a && b)) return 1;
    long x = a * b;
    return (a != x / b);
}

// sum overflow
short sof(long a, long b) {
    return (a > LONG_MAX - b);
}

// safe binary pow
long bin_pow(long x, long n) {
    if (!n)
        return 1;
    else if (n % 2) {
        long before  = bin_pow(x, n - 1);
        return (mof(before, x)) ? 0 : before * x;
    }
    long before = bin_pow(x, n / 2);
    return (mof(before, before)) ? 0 : before * before;
}

int main(void) {
    long k;
    scanf("%ld", &k);

    // punct 1
    unsigned ways = 0;
    for (unsigned i1 = 0; i1 <= 8; i1++)
        for (unsigned i3 = 0; i3 <= 7; i3++)
            for (unsigned i5 = 0; i5 <= 4; i5++)
                if (i1 + i3 + i5 <= 11 && i1 + i3 * 3 + i5 * 5 == 21)
                    ways++;
    printf("%u\n\n", ways);

    // punct 2
    long maxs, maxn, sum, cur;
    short ok, error_code;
    for (long n = 0; ; n++) {
        sum = 0;
        ok = 1;

        for (long i = 1; i <= k; i++) {
            cur = bin_pow(i, n);
            if (!cur) {
                ok = 0;
                error_code = 0;
                break;
            }
            if (!sof(sum, cur)) sum += cur;
            else {
                ok = 0;
                error_code = 1;
                break;
            }
        }
        if (ok && (maxs <= sum)) {
            maxs = sum;
            maxn = n;
        }
        if (!ok) break;
    }

    printf("%ld\n%ld\n", maxs, maxn);
    if (error_code == 0) printf("*\n");
    else printf("+\n");

    return 0;
}
