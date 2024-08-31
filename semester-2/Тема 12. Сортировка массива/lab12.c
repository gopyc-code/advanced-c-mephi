#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_fill(int *, int, int, int);
void print(int *, int);
void swap(int *, int *);
void selection_sort(int *, int, int *, int *);
void bubble_sort(int *, int, int *, int *);

int main(void) {
    srand(time(NULL));

    int n;
    scanf("%d", &n);
    int *a = (int *) calloc(n, sizeof(int));
    if (a == NULL)
        exit(EXIT_FAILURE);
    int *acopy = (int *) calloc(n, sizeof(int));
    if (acopy == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        acopy[i] = a[i];
    }

    print(a, n);
    printf("\n");
    int assigns, compares;

    selection_sort(a, n, &assigns, &compares);
    print(a, n);
    printf("%d %d\n\n", assigns, compares);

    for (int i = 0; i < n; i++)
        a[i] = acopy[i];

    bubble_sort(a, n, &assigns, &compares);
    print(a, n);
    printf("%d %d\n", assigns, compares);

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

void swap(int *a1, int *a2) {
    int tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}

void selection_sort(int *a, int n, int *assigns, int *compares) {
    int mini;
    *assigns = 0, *compares = 0;

    for (int i = 0; i < n - 1; i++) {
        mini = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[mini])
                mini = j;
            (*compares)++;
        }

        swap(a + mini, a + i);
        *assigns += 3;

        if (i < n - 2) {
            print(a, n);
            printf("\n");
        }
    }
}

void bubble_sort(int *a, int n, int *assigns, int *compares) {
    *assigns = 0, *compares = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                swap(a + j, a + j + 1);
                *assigns += 3;
            } (*compares)++;
        }

        if (i < n - 2) {
            print(a, n);
            printf("\n");
        }
    }
}
