#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void line();
void random_fill(int *, int, int, int);
void print(int *, int);
void swap(int *, int *);
void selection_sort(int *, int, int *, int *);
void _tree_rebuild(int *, int, int, int, int *, int *);
void tree_sort(int *, int, int *, int *);
void test(int);

int main(void) {
    srand(time(NULL));

    line();
    printf("|      |     Selection    |      Tree      |          |         |\n");
    printf("|   N  +-------+----------+-------+--------+ (N-1)N/2 | N+NlogN |\n");
    printf("|      | assgn |   comps  | assgn |  comps |          |         |\n");
    line();
    int N[4] = {100, 500, 1000, 5000};
    for (int i = 0; i < 4; i++)
        test(N[i]);

    return 0;
}

void line() {
    printf("+------+-------+----------+-------+--------+----------+---------+\n");

}
void test(int n) {
    int *a = (int *) calloc(n, sizeof(int));
    if (a == NULL)
        exit(EXIT_FAILURE);
    random_fill(a, 0, n, n);
    int *acopy = (int *) calloc(n, sizeof(int));
    if (acopy == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < n; i++) {
        acopy[i] = a[i];
    }

    int assigns = 0, compares = 0;
    selection_sort(a, n, &assigns, &compares);
    printf("| %4d | %5d | %8d |", n, assigns, compares);

    for (int i = 0; i < n; i++)
        a[i] = acopy[i];

    assigns = 0, compares = 0;
    tree_sort(a, n, &assigns, &compares);
    printf(" %5d | %6d | %8d |  %5d  |\n", assigns, compares,
           (n - 1) * n / 2, (int) (log(n) / log(2) * n) + n);
    line();
    free(a); free(acopy);
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
    }
}

void _tree_rebuild(int *A, int n, int r, int q,
                   int *assigns, int *compares) {
    int v = A[r], i = r, j = 2 * r + 1, pp = 0;
    (*assigns)++;

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

    A[i] = v;
    (*assigns)++;
}

void tree_sort(int *A, int n, int *assigns, int *compares) {
    int k = n / 2;
    for (int i = k - 1; i >= 0; i--)
        _tree_rebuild(A, n, i, n - 1, assigns, compares);
    for (int i = n - 1; i >= 1; i--) {
        swap(&A[0], &A[i]);
        *assigns += 3;
        _tree_rebuild(A, n, 0, i - 1, assigns, compares);
    }
}
