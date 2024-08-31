#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int root(int a, int b, int c, double *x1, double *x2);
int pq(double r1, double r2, double *p, double *q);
void cased_out(int c, double a, double b);
void dezero(double *x);

int main(void) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    double x1, x2;
    int flag = root(a, b, c, &x1, &x2);
    cased_out(flag, x1, x2);

    /*
    // обратная задача — по корням r1
    // и r2 найти p, q
    double r1, r2, p, q;
    flag = pq(r1, r2, &p, &q);
    dezero(&p); dezero(&q);
    printf("%d\n%.6f\n%.6f\n", flag, p, q);
    */

    return 0;
}

int root(int a, int b, int c, double *x1, double *x2) {
    double D = (double)b * b - 4 * a * c;
    if (!a && b) {
        *x1 = -(double)c / b;
        return 1;
    } else if (D < 0 || (!b && !a))
        return 2;
    else if (!D) {
        *x1 = -(double)b / (2 * a);
        return 3;
    } else {
        *x1 = (-(double)b - sqrt(D)) / (2 * a);
        *x2 = (-(double)b + sqrt(D)) / (2 * a);
    } return 0;
}

void cased_out(int c, double a, double b) {
    dezero(&a); dezero(&b);

    switch (c) {
        case 0:
            printf("0\n%.6f\n%.6f\n", a, b);
            break;
        case 1:
            printf("1\n%.6f\n", a);
            break;
        case 2:
            printf("2\n");
            break;
        case 3:
            printf("3\n%.6f\n", a);
            break;
    }
}

int pq(double r1, double r2, double *p, double *q) {
    *p = -(r1 + r2);
    *q = r1 * r2;
    dezero(&p); dezero(&q);
    if (r1 == r2)
        return 3;
    return 0;
}

void dezero(double *x) {
    // -0.0000 -> 0.0000
    if (!(*x)) *x = 0;
}
