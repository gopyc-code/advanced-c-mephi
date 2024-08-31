#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
[good test]
100
6 4 5 10 2 7 1 2 3 8 0 4 1 3 6 6 9 7 5 1 7 7 0 0 0 1 9 3 6 8 7 7 8 5 7 3 7 0 10 7 8 9 3 0 6 0 10 8 3 2 7 2 2 10 8 10 9 3 4 1 2 10 7 0 10 7 2 8 0 3 2 2 7 8 10 4 1 2 3 1 3 4 1 6 5 5 3 7 6 0 8 6 6 10 8 10 1 9 9 5
297 1275
297 4950

[bad test]
100
593 792 694 566 462 634 674 214 795 166 343 70 393 324 861 44 753 215 75 989 584 321 698 896 414 817 238 940 43 28 943 816 349 305 684 152 35 430 163 261 717 295 713 276 550 998 865 198 937 36 985 803 195 788 624 89 827 971 713 301 36 370 103 110 828 216 47 842 394 299 571 914 61 623 236 463 705 813 394 253 145 860 176 466 288 877 127 796 854 776 768 762 228 286 519 187 458 673 113 773
714 9728
297 4950
*/

void random_fill(int *, int, int, int);
void print(int *, int);
void swap(int *, int *);
void selection_sort(int *, int, int *, int *);
void modified_selection_sort(int *, int, int *, int *);

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

    modified_selection_sort(a, n, &assigns, &compares);
    print(a, n);
    printf("%d %d\n\n", assigns, compares);

    for (int i = 0; i < n; i++)
        a[i] = acopy[i];

    selection_sort(a, n, &assigns, &compares);
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

/*
assignes N(N - 1) / 2
compares 3(N - 1)
*/
void selection_sort(int *a, int n, int *assigns, int *compares) {
    int mini;
    *assigns = 0, *compares = 0;

    // assignes (n - i - 1) * (n - 1)
    // compares 3 * (n - 1)
    for (int i = 0; i < n - 1; i++) {
        mini = i;
        // compares (n - i - 1)
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[mini])
                mini = j;
            (*compares)++;
        }

        // assignes 3
        swap(a + mini, a + i);
        *assigns += 3;
    }
}

/*
compares 4 * N ^ 2 - N - 2
assignes 4 * N ^ 2 + 5 * N + 1
*/
// Bingo sort
void modified_selection_sort(int *a, int n, int *assigns, int *compares) {
    int mini, nextval, nexti, curval;
    *assigns = 0, *compares = 0;

    // compares 4 * mini ^ 2 - (8n + 5) * mini
    // + 4 * n ^ 2 - n - 2, mini = 0 (max)
    // ѕоиск минимального значени€
    // compares n
    mini = 0, nexti = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[nexti])
            nexti = i;
        (*compares)++;
    }

    // ѕоиск элемента с минимальным значением
    // и максимальным индексом
    nextval = a[nexti];
    // assignes 1
    (*assigns)++;
    // compares n - 1
    while (mini != n - 1 && a[mini] == nextval) {
        (*compares)++;
        mini++;
    } (*compares)++;

    // compares n - 1 - mini
    while (mini != n - 1) {
        curval = nextval;
        nextval = a[mini];
        // assigns 1
        (*assigns)++;
        // assigns 4 * (n - mini)
        // compares 2 * (n - mini)
        for (int i = mini + 1; i < n; i++) {
            // ѕерестановка очередного минимального
            // жлемента из неотсортированной части
            // с первым элементом из этой части
            if (a[i] == curval) {
                swap(a + i, a + mini);
                *assigns += 3;
                mini++;
            }
            // ќпределение текущего минимального
            // значени€
            else if (a[i] < nextval) {
                nextval = a[i];
                (*assigns)++;
            } *compares += 2;
        }

        // ѕоиск элемента с минимальным значением
        // и максимальным индексом
        // compares n - 1 - mini
        while (mini != n - 1 && a[mini] == nextval) {
            (*compares)++;
            mini++;
        } (*compares)++;

        if (mini < n - 2) {
            print(a, n);
            printf("\n");
        }
    }
}
