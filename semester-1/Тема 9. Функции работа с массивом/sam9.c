#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Тест 1
10 11 12 13 14
10 11 12 13 14 15
10 11 12 13 14 15 16 17
3 6

Тест 2
10 11 12 13 14
10 10 10 10 10 10
11 11 11 11 11 11 11 11
1 5
*/

void zero(int *a, int n);
void user_fill(int *a, int n);
void random_fill(int minm, int maxm, int *a, int n);
void print(int *a, int n);
int sum(int *a, int n);
double mid_val(int *p, int *q);
void search(int *a, int n, int *l, int ok);


int main(void) {
    srand(time(NULL));

    int m5[5], m6[6], m8[8], l[6];
    int p, q;

    /*
    random_fill(10, 15, m5, 5);
    random_fill(10, 15, m6, 6);
    random_fill(10, 15, m8, 8);
    */

    user_fill(m5, 5);
    user_fill(m6, 6);
    user_fill(m8, 8);

    scanf("%i%i", &p, &q);
    p--; q--;
    zero(l, 6);

    printf("%i %i %i\n", sum(m5, 5),
           sum(m6, 6), sum(m8, 8));
    printf("%.1lf\n", mid_val(m8 + p, m8 + q));

    search(m5, 5, l, 0);
    search(m6, 6, l, 1);
    search(m8, 8, l, 2);

    int maxi;
    for (int i = 0; i < 6; i++)
        if (l[i] == 3)
            maxi = i;
    for (int i = 0; i < 6; i++)
        if (l[i] == 3) {
            printf("%i", i + 10);
            if (i != maxi)
                printf(" ");
            else
                printf("\n");
        }

    return 0;
}

void zero(int *a, int n) {
    for (int i = 0; i < n; i++)
        a[i] = 0;
}

void user_fill(int *a, int n) {
    for (int i = 0; i < n; i++)
        scanf("%i", a + i);
}

void random_fill(int minm, int maxm, int *a, int n) {
    for (int i = 0; i < n; i++)
        a[i] = minm + rand() %
        (maxm - minm + 1);
}

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%i", a[i]);
        if (i + 1 != n)
            printf(" ");
    } printf("\n");
}

int sum(int *a, int n) {
    int res = 0;
    for (int i = 0; i < n; i++)
        res += a[i];

    return res;
}

double mid_val(int *p, int *q) {
    int s = 0, n = q - p + 1;
    for (; p <= q; p++)
        s += *p;

    return (double)s / n;
}

void search(int *a, int n, int *l, int ok) {
    for(int i = 0; i < n; i++)
        if (l[a[i] - 10] == ok)
            l[a[i] - 10]++;
}
