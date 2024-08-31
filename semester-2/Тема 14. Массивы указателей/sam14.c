#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

void scan_for_auto(char *, char **, int *);
void scan(char *, char **, int *);
void scan_file(char *, char **, int *);
void print(char **, int);
void swap(char **, char **);
void quick_sort(char **, int, int);
double dispersion(int *, int *);
void separate(char **, int);

const int POINTS = 3;
const int ALPHA = 26;

int main(void) {
    char buffer[3000], *a[300];
    int n = 0;

    // replace with scan
    scan_for_auto(buffer, a, &n);
    quick_sort(a, 0, n - 1);
    print(a, n);
    printf("\n");
    separate(a, n);

    return 0;
}

void scan_for_auto(char *buffer, char **a, int *n) {
    int pointer = 0;
    *n = 0;

    char curs[20], c;
    int curp;

    int counter = 0;
    c = getchar();
    while (counter != 9) {
        gets(curs);
        a[(*n)++] = &(buffer[pointer]);
        buffer[pointer++] = c;

        curp = 0;
        while (curs[curp] != 0)
            buffer[pointer++] = curs[curp++];

        buffer[pointer++] = '\0';
        c = getchar();
        counter++;
    }
}

void scan(char *buffer, char **a, int *n) {
    int pointer = 0;
    *n = 0;

    char curs[20], c;
    int curp;

    c = getchar();
    while (c != '\n') {
        gets(curs);
        a[(*n)++] = &(buffer[pointer]);
        buffer[pointer++] = c;

        curp = 0;
        while (curs[curp] != 0)
            buffer[pointer++] = curs[curp++];

        buffer[pointer++] = '\0';
        c = getchar();
    }
}

void scan_file(char *buffer, char **a, int *n) {
    FILE *file;
    file = fopen("main.txt", "r");
    int pointer = 0;
    *n = 0;

    char c;
    a[(*n)++] = &buffer[pointer];
    c = fgetc(file);
    while (c != EOF) {
        buffer[pointer++] = c;
        if (c == '\n') {
            a[(*n)++] = &(buffer[pointer]);
        }
        c = fgetc(file);
    }
}

void print(char **a, int n) {
    for (int i = 0; i < n; i++)
        printf("%s\n", a[i]);
}

void swap(char **a1, char **a2) {
    char *tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}

void quick_sort(char **a, int first, int last) {
    int l = first, r = last;
    char *pivot = a[(l + r) / 2];

    while (l <= r) {
        while (strcasecmp(a[l], pivot) < 0) l++;
        while (strcasecmp(a[r], pivot) > 0) r--;

        if (l <= r) {
            swap(&a[l], &a[r]);
            l++;
            r--;
        }
    }

    if (first < r)
        quick_sort(a, first, r);
    if (l < last)
        quick_sort(a, l, last);
}

double dispersion(int *counter, int *t) {
    int s[POINTS + 1];
    for (int i = 0; i < POINTS + 1; i++)
        s[i] = 0;

    for (int i = 1; i < POINTS + 2; i++)
        for (int j = t[i - 1]; j < t[i]; j++)
            s[i - 1] += counter[j];

    for (int i = 0; i < POINTS + 1; i++)
        if (!s[i])
            return DBL_MAX;

    double m = 0., disp = 0.;
    for (int i = 0; i < POINTS + 1; i++)
        m += (double)s[i];
    m = m / (double)(POINTS + 1);

    for (int i = 0; i < POINTS + 1; i++)
        disp += powf(fabs(m - (double)s[i]), 2);

    return sqrt(disp);
}

void separate(char **a, int n) {
    int counter[ALPHA];
    for (int i = 0; i < ALPHA; i++)
        counter[i] = 0;
    for (int i = 0; i < n; i++)
        counter[toupper(a[i][0]) - 65]++;

    int bestt[POINTS + 2], tmpt[POINTS + 2];
    double best_disp = DBL_MAX, tmp_disp;

    for (int i = 1; i < ALPHA; i++) {
        for (int j = i + 1; j < ALPHA; j++) {
            for (int k = j + 1; k < ALPHA; k++) {
                tmpt[0] = 0, tmpt[1] = i, tmpt[2] = j,
                tmpt[3] = k, tmpt[4] = ALPHA;
                tmp_disp = dispersion(counter, tmpt);

                if (tmp_disp < best_disp){
                    best_disp = tmp_disp;
                    bestt[0] = 0, bestt[1] = i, bestt[2] = j,
                    bestt[3] = k, bestt[4] = ALPHA;
                }
            }
        }
    }

    int s[POINTS + 1];
    for (int i = 0; i < POINTS + 1; i++)
        s[i] = 0;

    for (int i = 1; i < POINTS + 2; i++)
        for (int j = bestt[i - 1]; j < bestt[i]; j++)
            s[i - 1] += counter[j];

    for (int i = 1; i < POINTS + 2; i++)
        printf("%c-%c %d\n", 65 + bestt[i - 1], 65 + bestt[i] - 1, s[i - 1]);
}

/* TESTS

-----------DEFAULT----------
Taylor
Davies
Smith
Johnson
Roberts
Brown
Jones
Williams
Evans

----------REPEATS-----------
Taylor
Johnson
Johnson
Davies
Smith
Johnson
Johnson
Roberts
Davies
Davies
Brown
Jones
Johnson
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Davies
Williams
Johnson
Johnson
Evans

----------24 (FIRST LETTER IS UNIQUE)----------
Frye
Leon
Vaughn
Walls
Zoom
Gibson
Hobbs
Monkey
David
East
Norton
Oliver
Qortega
Terrell
Unique
Acosta
Ivan
Jacobson
Kennedy
Beasley
Carter
Potter
Rocha
Santos

----------100 (FIRST LETTER REPEATED)----------
Joseph
Perry
Duran
Vaughn
Kent
Adkins
Brady
Cross
Curry
Barnett
Thompson
Wilson
Lewis
Cabrera
Carey
Little
Rivas
Schwartz
Fields
Ward
Joyce
Ortega
Rasmussen
Case
Davis
Hines
Krueger
Gallegos
Carter
Bradford
Frye
May
Padilla
Calhoun
Bryant
Vance
Spence
Mora
Gallagher
Terrell
Melendez
Leon
Duarte
Johnson
Copeland
Mckenzie
Moore
Phelps
Meyers
David
Hernandez
Deleon
Mahoney
Greene
Davidson
Walls
Moon
Kidd
Ponce
Rocha
Marks
Nunez
Davila
Massey
Berg
Donovan
Beasley
Carney
Dunn
Johnston
Jones
Keith
Maddox
Ware
Branch
Potter
Proctor
Anderson
Johns
Santos
Gibson
Peters
Kennedy
Farley
Smith
Holder
Doyle
Sullivan
Norton
Reid
Gilbert
Hickman
Jacobson
Barrett
Hardin
Oliver
Acosta
Hobbs
Benson
Mathis
*/
