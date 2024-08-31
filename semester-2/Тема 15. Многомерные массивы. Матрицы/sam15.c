#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FNAME "main.txt"

void solve();
void test_file_fuctions();
void test_multiply();

void print_matrix(int m, int n, int matrix[m][n]);
void save_matrix_to_file(int m, int n, int matrix[m][n]);
void scan_matrix(int m, int n, int matrix[m][n]);
void read_matrix_from_file(int m, int n, int matrix[m][n]);
void rand_fill_matrix(int m, int n, int, int, int matrix[m][n]);

void add(int m, int n, int matrixa[m][n], int matrixb[m][n], int matrixS[m][n]);
void multiply(int ma, int na, int mb, int nb, int matrixa[ma][na], int matrixb[mb][nb], int matrixM[ma][nb]);
void pow(int n, int, int matrix[n][n], int matrixP[n][n]);

void check_add(int, int, int, int);
void check_multiply(int, int);
void check_pow(int, int, int);

void transpose(int m, int n, int matrix[m][n], int matrixT[n][m]);
int is_zero(int m, int n, int matrix[m][n]);
void zero(int m, int n, int matrix[m][n]);
void unit(int n, int matrix[n][n]);
void copy(int m, int n, int matrixa[m][n], int matrixb[m][n]);

int main(void) {
    srand(time(NULL));

    solve();
    //test_file_fuctions();
    //test_multiply();

    return 0;
}

void solve() {
    /*
    3 4
    3 2 4 1 5 2 1 4 1 3 4 2
    4 3
    2 4 5 3 2 1 4 3 3 1 5 2
    */

    int ma, na;
    scanf("%d%d", &ma, &na);
    int matrixa[ma][na];
    scan_matrix(ma, na, matrixa);

    int mb, nb;
    scanf("%d%d", &mb, &nb);
    int matrixb[mb][nb];
    scan_matrix(mb, nb, matrixb);

    int C[ma][nb];
    zero(ma, nb, C);
    multiply(ma, na, mb, nb, matrixa, matrixb, C);

    check_pow(ma, nb, 2);
    int D[ma][nb];
    pow(ma, 2, C, D);

    int E[na][ma];
    transpose(ma, na, matrixa, E);

    int F[ma][ma];
    zero(ma, ma, F);
    multiply(ma, na, na, ma, matrixa, E, F);

    check_add(ma, nb, ma, ma);
    int G[ma][ma];
    add(ma, ma, D, F, G);

    print_matrix(ma, ma, G);
}

void test_file_fuctions() {
    int m, n;
    scanf("%d%d", &m, &n);
    int matrix[m][n];
    rand_fill_matrix(m, n, 1, m * n, matrix);
    save_matrix_to_file(m, n, matrix);
    read_matrix_from_file(m, n, matrix);
    print_matrix(m, n, matrix);
}

void test_multiply() {
    int A[3][3] = {
        {2, 3, 1},
        {4, 7, 2},
        {3, 6, 2}
    }, A_inversed[3][3] = {
        {2, 0, -1},
        {-2, 1, 0},
        {3, -3, 2}
    }, E[3][3];

    zero(3, 3, E);
    multiply(3, 3, 3, 3, A, A_inversed, E);
    print_matrix(3, 3, E);

    /*
    1     0     0
    0     1     0
    0     0     1
    */
}

void print_matrix(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%6d", matrix[i][j]);
        printf("\n");
    }
}

void save_matrix_to_file(int m, int n, int matrix[m][n]) {
    FILE *f;
    f = fopen(FNAME, "w");

    fprintf(f, "%d %d\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            fprintf(f, "%6d", matrix[i][j]);
        fputc('\n', f);
    }
}

void scan_matrix(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);
}

void read_matrix_from_file(int m, int n, int matrix[m][n]) {
    FILE *f;
    f = fopen(FNAME, "r");

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            fscanf(f, "%d", &matrix[i][j]);
}

void rand_fill_matrix(int m, int n, int minx, int maxx, int matrix[m][n]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = minx + rand() % (maxx - minx + 1);
}

void add(int m, int n, int matrixa[m][n], int matrixb[m][n], int matrixS[m][n]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrixS[i][j] = matrixa[i][j] + matrixb[i][j];
}

void multiply(int ma, int na, int mb, int nb, int matrixa[ma][na], int matrixb[mb][nb], int matrixM[ma][nb]) {
    check_multiply(na, mb);

    for (int i = 0; i < ma; i++)
        for (int j = 0; j < nb; j++)
            for (int k = 0; k < na; k++)
                matrixM[i][j] += matrixa[i][k] * matrixb[k][j];
}

void pow(int n, int exp, int matrix[n][n], int matrixP[n][n]) {
    if (is_zero(n, n, matrix)) {
        zero(n, n, matrixP);
        return;
    }

    int matrixTmp[n][n];
    unit(n, matrixP);

    for (int i = 0; i < exp; i++) {
        zero(n, n, matrixTmp);
        multiply(n, n, n, n, matrix, matrixP, matrixTmp);
        copy(n, n, matrixTmp, matrixP);
    }
}

void check_add(int ma, int na, int mb, int nb) {
    if ((ma != mb) || (na != nb)) {
        printf("!1\n");
        exit(0);
    }
}

void check_multiply(int na, int mb) {
    if (na != mb) {
        printf("!2\n");
        exit(0);
    }
}

void check_pow(int m, int n, int exp) {
    if (m != n || exp < 0) {
        printf("!3\n");
        exit(0);
    }
}

void transpose(int m, int n, int matrix[m][n], int matrixT[n][m]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrixT[j][i] = matrix[i][j];
}

int is_zero(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j])
                return 0;
    return 1;
}

void zero(int m, int n, int matrix[m][n]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
}

void unit(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = (i == j) ? 1 : 0;
}

void copy(int m, int n, int matrixa[m][n], int matrixb[m][n]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrixb[i][j] = matrixa[i][j];
}
