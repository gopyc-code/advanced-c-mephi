#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_fill(int *, int, int, int);
void print(int *, int);
void swap(int *, int *);
void quick_sort(int *, int, int, int, int *, int *);
void _tree_rebuild(int *, int, int, int, int *, int *);
void tree_sort(int *, int, int *, int *);

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
    int assigns = 0, compares = 0;
    quick_sort(a, n, 0, n - 1, &assigns, &compares);
    printf("%d %d\n\n", assigns, compares);

    for (int i = 0; i < n; i++)
        a[i] = acopy[i];

    assigns = 0, compares = 0;
    tree_sort(a, n, &assigns, &compares);
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

void quick_sort(int *A, int n, int first, int last,
                int *assigns, int *compares) {
    int pivot, l = first, r = last;
    pivot = A[(l + r) / 2];
    (*assigns)++;

    while (l <= r) {
        while (A[l] < pivot) {
            (*compares)++;
            l++;
        } (*compares)++;
        while (A[r] > pivot) {
            (*compares)++;
            r--;
        } (*compares)++;
        if (l <= r) {
            swap(&A[l], &A[r]);
            *assigns += 3;

            if (A[l] != A[r]) {
                print(A, n);
                printf("\n");
            }

            l++;
            r--;
        }
    }

    if (first < r)
        quick_sort(A, n, first, r, assigns, compares);
    if (l < last)
        quick_sort(A, n, l, last, assigns, compares);
}

void _tree_rebuild(int *A, int n, int r, int q,
                   int *assigns, int *compares) {
    int v = A[r], i = r, j = 2 * r + 1, pp = 0;
    (*assigns)++;

    int ch;
    while (j <= q && !pp) {
        if (j < q) {
            if (A[j] < A[j + 1])
                j++;
            (*compares)++;
        }
        if (v >= A[j])
            pp = 1;
        else {;
            A[i] = A[j];
            (*assigns)++;

            i = j;
            j = 2 * i + 1;
        }
        (*compares)++;
    }

    ch = (A[i] != v);
    A[i] = v;
    (*assigns)++;
    if (ch) {
        print(A, n);
        printf("\n");
    }
}

void tree_sort(int *A, int n, int *assigns, int *compares) {
    int k = n / 2;
    for (int i = k - 1; i >= 0; i--)
        _tree_rebuild(A, n, i, n - 1, assigns, compares);
    for (int i = n - 1; i >= 1; i--) {
        swap(&A[0], &A[i]);
        *assigns += 3;
        if (&A[0] != &A[i]) {
            print(A, n);
            printf("\n");
        }
        _tree_rebuild(A, n, 0, i - 1, assigns, compares);
    }
}
