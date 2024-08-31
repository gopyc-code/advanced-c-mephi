#include <stdio.h>
#include <stdlib.h>

void print_matrix(int m, int n, int matrix[m][n]);
void scan_matrix(int m, int n, int matrix[m][n]);
void max_row(int m, int n, int matrix[m][n]);
void saddle_search(int m, int n, int matrix[m][n]);

void print_matrix_addr(int m, int n, int matrix[m][n]);
void scan_matrix_addr(int m, int n, int matrix[m][n]);
void max_row_addr(int m, int n, int matrix[m][n]);
void saddle_search_addr(int m, int n, int matrix[m][n]);

/*
4 3
1 2 3 6 0 0 1 1 1 5 1 0

4 4
1 2 3 4 8 7 6 5 9 10 11 12 16 15 13 13
*/

int main(void) {
    int m, n;
    scanf("%d%d", &m, &n);
    int matrix[m][n];

    /*
    scan_matrix(m, n, matrix);
    print_matrix(m, n, matrix);

    printf("\n");
    max_row(m, n, matrix);
    saddle_search(m, n, matrix);
    */

    scan_matrix_addr(m, n, matrix);
    print_matrix_addr(m, n, matrix);

    printf("\n");
    max_row_addr(m, n, matrix);
    saddle_search_addr(m, n, matrix);


    return 0;
}

void print_matrix(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d", matrix[i][j]);
        printf("\n");
    }

}

void scan_matrix(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++) {
        if ((i + 1) % 2)
            for (int j = 0; j < n; j++)
                scanf("%d", &matrix[i][j]);
        else
            for (int j = n - 1; j >= 0; j--)
                scanf("%d", &matrix[i][j]);
    }
}

void max_row(int m, int n, int matrix[m][n]) {
    int maxs = 0, sums[m];
    for (int i = 0; i < m; i++) {
        sums[i] = 0;
        for (int j = 0; j < n; j++)
            sums[i] += matrix[i][j];
        if (sums[i] > maxs)
            maxs = sums[i];
    }

    int printed = 0;
    for (int i = 0; i < m; i++)
        if (sums[i] == maxs) {
            if (!printed)
                printed = 1;
            else
                printf(" ");
            printf("%d", i + 1);
        }
    printf("\n");
}

void saddle_search(int m, int n, int matrix[m][n]) {
    int saddle, counter = 0;

    int row_min, ok;
    for (int i = 0; i < m; i++) {
        // getting min of row
        row_min = matrix[i][0];
        for (int j = 0; j < n; j++)
            if (matrix[i][j] < row_min)
                row_min = matrix[i][j];

        // checking each minimum element of a row
        // if it is also a saddle element of matrix
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == row_min) {
                ok = 1;
                for (int t = 0; t < m; t++)
                    if (matrix[i][j] < matrix[t][j]) {
                        ok = 0;
                        break;
                    }
                if (ok) {
                    counter++;
                    saddle = matrix[i][j];
                }
            }
    }

    if (!counter) {
        printf("-\n");
        return;
    }

    printf("%d", saddle);
    if (counter != 1)
        printf(" %d", counter);
    printf("\n");
}

//-------------------------------------------------------

void print_matrix_addr(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d", *(*(matrix + i) + j));
        printf("\n");
    }

}

void scan_matrix_addr(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++) {
        if ((i + 1) % 2)
            for (int j = 0; j < n; j++)
                scanf("%d", *(matrix + i) + j);
        else
            for (int j = n - 1; j >= 0; j--)
                scanf("%d", *(matrix + i) + j);
    }
}

void max_row_addr(int m, int n, int matrix[m][n]) {
    int maxs = 0, sums[m];
    for (int i = 0; i < m; i++) {
        *(sums + i) = 0;
        for (int j = 0; j < n; j++)
            *(sums + i) += *(*(matrix + i) + j);
        if (*(sums + i) > maxs)
            maxs = *(sums + i);
    }

    int printed = 0;
    for (int i = 0; i < m; i++)
        if (*(sums + i) == maxs) {
            if (!printed)
                printed = 1;
            else
                printf(" ");
            printf("%d", i + 1);
        }
    printf("\n");
}

void saddle_search_addr(int m, int n, int matrix[m][n]) {
    int saddle, counter = 0;

    int row_min, ok;
    for (int i = 0; i < m; i++) {
        // getting min of row
        row_min = **(matrix + i);
        for (int j = 0; j < n; j++)
            if (*(*(matrix + i) + j) < row_min)
                row_min = *(*(matrix + i) + j);

        // checking each minimum element of a row
        // if it is also a saddle element of matrix
        for (int j = 0; j < n; j++)
            if (*(*(matrix + i) + j) == row_min) {
                ok = 1;
                for (int t = 0; t < m; t++)
                    if (*(*(matrix + i) + j) < *(*(matrix + t) + j)) {
                        ok = 0;
                        break;
                    }
                if (ok) {
                    counter++;
                    saddle = *(*(matrix + i) + j);
                }
            }
    }

    if (!counter) {
        printf("-\n");
        return;
    }

    printf("%d", saddle);
    if (counter != 1)
        printf(" %d", counter);
    printf("\n");
}
