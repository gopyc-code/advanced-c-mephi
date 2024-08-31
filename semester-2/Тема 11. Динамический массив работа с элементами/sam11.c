#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define FNAME "main.txt"

void random_fill(int *, int, int, int);
void print(int *a, int n);
void swap(int *, int *);
void swap2m(int *, int, int);
void save_array_to_file(int *, int);
void read_array_from_file(int **, int *);
void insertion(int **, int *, int, int *, int);
void deletion(int **, int *, int, int);

int main(void) {
    srand(time(NULL));

    int n = 20, m;
    int *a = (int *) calloc(n, sizeof(int));
    scanf("%d", &m);

    random_fill(a, 0, 15, n);
    print(a, n);

    swap2m(a, n, m);
    print(a, n);

    int mas[6] = {10, 11, 12, 13, 14, 15},
        masn = 6, pos = 3;
    insertion(&a, &n, pos, mas, masn);
    print(a, n);

    deletion(&a, &n, pos, masn);
    print(a, n);

    save_array_to_file(a, n);

    int *a1, n1;
    read_array_from_file(&a1, &n1);
    print(a1, n1);

    return 0;
}

void random_fill(int *a, int minm, int maxm, int n) {
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

void swap (int *a1, int *a2) {
    int tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}

void swap2m(int *a, int n, int m) {
    if (2 * m > n)
        exit(EXIT_FAILURE);
    for (int i = 0; i < m; i++)
        swap(&a[i], &a[i + m]);
}

void save_array_to_file(int *a, int n) {
    FILE *f;
    f = fopen(FNAME, "w");
    if (f == NULL)
        exit(EXIT_FAILURE);

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d", a[i]);
        if (i + 1 != n)
            fprintf(f, "%c", ' ');
    } fprintf(f, "%s", "\n");
    fclose(f);
}

void read_array_from_file(int **a, int *n) {
    FILE *f;
    f = fopen(FNAME, "r");
    if (f == NULL)
        exit(EXIT_FAILURE);

    fscanf(f, "%d", n);
    int *af = (int *) calloc(*n, sizeof(int));
    if (af == NULL)
        exit(EXIT_FAILURE);

    *a = af;
    for (int i = 0; i < *n; i++)
        fscanf(f, "%d", *a + i);
    fclose(f);
}

void insertion(int **p, int *n,
               int pos, int *mas, int masn) {
    if (pos >= *n || pos < 0)
        exit(EXIT_FAILURE);
    if (!masn)
        return;

    pos--; *n = (*n) + masn;
    int *q = (int *) realloc(*p, (*n) * sizeof(int));
    if (q == NULL)
		exit(EXIT_FAILURE);
    *p = q;

    for (int j = (*n) - 1; j > pos + masn - 1; j--)
        (*p)[j] = (*p)[j - masn];
    for (int j = 0; j < masn; j++)
        (*p)[pos + j] = mas[j];
}

void deletion(int **p, int *n, int pos, int masn) {
    if (pos >= *n || pos < 0 || masn + pos - 1 > *n)
        exit(EXIT_FAILURE);
    if (!masn)
        return;
    if (masn + pos - 1 == *n) {
        free(*p);
        *n = 0;
        return;
    }

    pos--;
    for (int i = 0; i < (*n) - pos; i++)
        (*p)[pos + i] = (*p)[pos + i + masn];

    *n = (*n) - masn;
    int *q = (int *) realloc(*p, (*n) * sizeof(int));
    if (q == NULL)
		exit(EXIT_FAILURE);
    *p = q;
}
