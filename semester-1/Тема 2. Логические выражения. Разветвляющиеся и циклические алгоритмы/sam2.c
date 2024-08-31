#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void fib_sum(int k) {
    long sum = 1;
    long fib1 = 1L, fib2 = 0L;

    long x[3] = {1, 2, 4};
    int max_fib_num;
    for (int i = 1;
        LONG_MAX - fib1 > sum ||
        LONG_MAX - fib2 > sum;
        i++)
    {
        if (i <= k)
            printf("%3d  %ld\n", i, sum);
        if (i == k)
            printf("\n");

        if (fib2 >= fib1)
            fib1 += fib2;
        else
            fib2 += fib1;
        sum += (fib1 > fib2) ? fib1 : fib2;

        x[0] = x[1];
        x[1] = x[2];
        x[2] = sum;
        max_fib_num = i + 1;
    }

    for (int i = 0; i < 3; i++)
        printf("%3d  %ld\n", max_fib_num - 3 + i + 1, x[i]);
}

void inside(int x, int y) {
    if (
        (x * x + y * y < 90000) && (
        !((-150 <= x && x <= 150) &&
          (0 <= y && y <= 150)) && (y > 0) ||
         (y < -150 &&
          y < -x &&
          y < x))
        ) printf("inside\n\n");
    else
        printf("outside\n\n");
}

int main(void) {
    int x, y;
    scanf("%d%d", &x, &y);

    int k;
    scanf("%d", &k);

    inside(x, y);
    fib_sum(k);
    return 0;
}
