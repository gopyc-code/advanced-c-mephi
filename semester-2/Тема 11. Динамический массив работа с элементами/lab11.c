#include <stdio.h>
#include <stdlib.h>

void insertion(int **, int, int, int);
void swap(int **, int);
void print (int *, int);

int main() {
    int n, a, k, b;
    int *p;
    scanf("%d", &n);
    p = (int *) calloc(n, sizeof(int));
    if (p == NULL)
		exit(EXIT_FAILURE);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    scanf("%d%d%d",&a, &k, &b);
    k--; b--;

    print(p, n);
    printf("\n");
    insertion(&p, n, a, k);
    swap(&p, b);
    print(p, n + 1);

    free(p);

    return 0;
}

void insertion(int **p, int n, int a, int k) {
    int *q = (int *) realloc(*p, (n + 1)*sizeof(int));
    if (q == NULL)
		exit(EXIT_FAILURE);
	else {
		*p = q;
        for (int j = n; j > k; j--)
            (*p)[j] = (*p)[j - 1];
        (*p)[k] = a;
	}
}

void swap (int **p, int i) {
    int tmp = (*p)[0];
    (*p)[0] = (*p)[i];
    (*p)[i] = tmp;
}

void print (int *p, int n) {
    for (int j = 0; j < n; j++)
        printf("%3d", j + 1);
    printf("\n");

    for (int j = 0; j < n; j++)
        printf("%3d", p[j]);
    printf("\n");
}
