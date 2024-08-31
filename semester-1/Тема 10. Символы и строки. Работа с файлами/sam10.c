#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define FNAME "main.txt"

void rand_fill_file();
void count_nums_file();
void print_hist(int *num);
void max_num_strs_file();
void empty (char *s, int l);

int main(void) {
    srand(time(NULL));

    //Файловая версия
    /*
    rand_fill_file();
    max_num_strs_file();
    printf("\n\n");
    count_nums_file();
    */

    int num[10], p = 0, rown = 0, maxi = 0;
    long max_in_s[30], maxn;

    for (int i = 0; i < 10; i++)
        num[i] = 0;
    for (int i = 0; i < 30; i++)
        max_in_s[i] = 0;

    char c, prev = 'a', s[20];
    while (!(((c = getchar()) == prev) &&
             (prev == '\n'))) {
        if (isdigit(c)) {
            num[c - 48]++;
            s[p] = c;
            p++;
        } else if (c == ' ' || c == '\n') {
            if (max_in_s[rown] < atol(s))
                max_in_s[rown] = atol(s);
            if (maxn <= max_in_s[rown]) {
                maxn = max_in_s[rown];
                maxi = rown;
            }

            empty(s, 20);
            p = 0;
            if (c == '\n')
                rown++;
        }

        prev = c;
    }

    for (int i = 0; i <= maxi; i++)
        if (max_in_s[i] == maxn) {
            printf("%d", i + 1);
            if (i != maxi)
                printf("%c", ' ');
        } printf("\n\n");

    print_hist(num);


    return 0;
}

void rand_fill_file() {
    FILE *f;
    f = fopen(FNAME, "w");

    int nrow = 1 + rand() % 30, ncol;

    for (int i = 0; i < nrow; i++) {
        ncol = 1 + rand() % 20;
        for (int j = 0; j < ncol; j++) {
            fprintf(f, "%ld", rand() % 100 * rand() % 100000000);
            if (j < ncol - 1)
                fputc(' ', f);
        }
        if (i < nrow - 1)
            fputc('\n', f);
    }

    fclose(f);
}

void count_nums_file() {
    FILE *f;
    f = fopen(FNAME, "r");

    int num[10];
    for (int i = 0; i < 10; i++)
        num[i] = 0;

    char c;
    while ((c = getc(f)) != EOF)
        if (isdigit(c))
            num[c - 48]++;

    fclose(f);

    print_hist(num);
}

void max_num_strs_file() {
    FILE *f;
    f = fopen(FNAME, "r");

    int num[30];
    for (int i = 0; i < 30; i++)
        num[i] = 0;

    long maxn = 0, x;
    while (!feof(f)) {
        fscanf(f, "%ld", &x);
        if (x > maxn)
            maxn = x;
    }
    fseek(f, 0L, SEEK_SET);

    char c, s[20];
    int row = 0, p = 0;
    while (1) {
        c = getc(f);
        if (isdigit(c)) {
            s[p] = c;
            p++;
        } else if (c == ' ' ||
                   c == '\n' ||
                   c == EOF) {
            if (atol(s) == maxn)
                num[row] = 1;
            p = 0;
            empty(s, 20);

            if (c == '\n')
                row++;
            if (c == EOF)
                break;
        }
    }

    int mini = 31, maxi = 0;
    for (int i = 0; i < 30; i++)
        if (num[i]) {
            if (mini > i)
                mini = i;
            if (maxi < i)
                maxi = i;
        }

    for (int i = mini; i <= maxi; i++) {
        if (num[i]) {
            printf("%d", i + 1);
            if (i != maxi)
                printf("%c", ' ');
        }
    }

    fseek(f, 0L, SEEK_SET);
    char strs[30][300];

    int nrows = 0;
    for (; !feof(f); nrows++)
        fgets(strs[nrows], 300, f);

    if (maxi == nrows - 1) {
        strcat(strs[maxi], "\n");
        strs[mini][strlen(strs[mini]) - 1] = 0;
    }

    char swp[300];
    strcpy(swp, strs[mini]);
    empty(strs[mini], 300);
    strcpy(strs[mini], strs[maxi]);
    empty(strs[maxi], 300);
    strcpy(strs[maxi], swp);

    fclose(f);

    FILE *fi;
    fi = fopen(FNAME, "w");
    for (int i = 0; i < nrows; i++)
        fputs(strs[i], fi);
    fclose(fi);
}

void print_hist(int *num) {
    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
        for (int j = 0; j < num[i] / 3; j++)
            printf("%c", '*');
        if (num[i] % 3 == 2)
            printf("%c", '*');
        if (num[i])
            printf("%c", ' ');
        printf("%d\n", num[i]);
    }
}

void empty (char *s, int l) {
    for (int i = 0; i < l; i++)
        s[i] = 0;
}
