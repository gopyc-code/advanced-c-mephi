#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_fill(int *, int, int, int);
void print(int *, int);
void printp(int **, int);
void scan(int **, int *);
void swapp(int **, int **);
void quick_sortp(int **, int, int);

/*
8
8 12 4 19 10 4 15 3
7
8 7 15 1 16 4 15
*/

int main(void) {
    srand(time(NULL));

    int *a, n, *b, m;
    scan(&a, &n);
    scan(&b, &m);

    int **mas = (int **) calloc(n + m, sizeof(int *));
    if (mas == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < n; i++)
        mas[i] = a + i;
    for (int i = 0; i < m; i++)
        mas[i + n] = b + i;

    quick_sortp(mas, 0, n + m - 1);

    print(a, n);
    printf("\n");
    print(b, m);
    printf("\n");
    printp(mas, m + n);
    printf("\n");

    return 0;
}

void random_fill(int *a, int minm, int maxm, int n) {
    for (int i = 0; i < n; i++)
        a[i] = minm + rand() %
        (maxm - minm + 1);
}

void print(int *a, int n) {
    for (int j = 0; j < n; j++)
        printf("%3d", j + 1);
    printf("\n");

    for (int j = 0; j < n; j++)
        printf("%3d", a[j]);
    printf("\n");
}

void printp(int **a, int n) {
    for (int j = 0; j < n; j++)
        printf("%3d", j + 1);
    printf("\n");

    for (int j = 0; j < n; j++)
        printf("%3d", *a[j]);
    printf("\n");
}

void scan(int **a, int *n) {
    scanf("%d", n);

    int *af = (int *) calloc(*n, sizeof(int));
    if (af == NULL)
        exit(EXIT_FAILURE);

    *a = af;
    for (int i = 0; i < *n; i++)
        scanf("%d", *a + i);
}

void swapp(int **a1, int **a2) {
    int **tmp = **a1;
    **a1 = **a2;
    **a2 = **tmp;
}

void quick_sortp(int **a, int first, int last) {
    int l = first, r = last;
    int pivot = *a[(l + r) / 2];

    while (l <= r) {
        while (*a[l] > pivot) l++;
        while (*a[r] < pivot) r--;

        if (l <= r) {
            int *tmp = a[l];
            a[l] = a[r];
            a[r] = tmp;

            l++;
            r--;
        }
    }

    if (first < r)
        quick_sortp(a, first, r);
    if (l < last)
        quick_sortp(a, l, last);
}
