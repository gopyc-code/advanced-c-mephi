#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char surname[15];
    char name[15];
    int year;
    struct Marks {
        int mat;
        int phys;
        int inf;
    } marks;
};

void scan_student(struct Student *);
void print_student(struct Student);
int marks_sum(struct Student);
void swap(struct Student *, struct Student *);
void copy(struct Student, struct Student *);
void quick_sort(struct Student *, int, int, int);

int main(void) {

    int n;
    scanf("%d", &n);

    struct Student a[n];
    for (int i = 0; i < n; i++)
        scan_student(&a[i]);

    for (int i = 0; i < n; i++)
        print_student(a[i]);
    printf("\n");

    struct Student acopy[n];
    for (int i = 0; i < n; i++)
        copy(a[i], &acopy[i]);
    quick_sort(acopy, n, 0, n - 1);

    int max_marks = 0;
    for (int i = n - 1; i >= 0; i--)
        if (acopy[i].year == 1 && marks_sum(acopy[i]) > max_marks)
            max_marks = marks_sum(acopy[i]);

    for (int i = 0; i < n; i++)
        if (a[i].year == 1 && marks_sum(a[i]) == max_marks)
            printf("%s %s\n", a[i].surname, a[i].name);
    printf("\n");

    for (int i = 0; i < n; i++)
        if (a[i].year != 1 && marks_sum(a[i]) >= max_marks)
            printf("%s %s\n", a[i].surname, a[i].name);

    return 0;
}

void scan_student(struct Student *a) {
    scanf("%s%s%d%d%d%d",
          a->surname, a->name,
          &a->year, &a->marks.mat,
          &a->marks.phys, &a->marks.inf);
}

void print_student(struct Student a) {
    printf("%-15s%-15s%5d%5d%5d%5d\n",
          a.surname, a.name,
          a.year, a.marks.mat,
          a.marks.phys, a.marks.inf);
}

int marks_sum(struct Student a) {
    return a.marks.mat + a.marks.phys + a.marks.inf;
}

void swap(struct Student *a, struct Student *b) {
    struct Student tmp = *a;
    *a = *b;
    *b = tmp;
}

void copy(struct Student a, struct Student *b) {
    strcpy(b->surname, a.surname);
    strcpy(b->name, a.name);
    b->year = a.year;
    b->marks.mat = a.marks.mat;
    b->marks.phys = a.marks.phys;
    b->marks.inf = a.marks.inf;
}

void quick_sort(struct Student *A, int n, int first, int last) {
    int l = first, r = last;
    struct Student pivot = A[(l + r) / 2];

    while (l <= r) {
        while (marks_sum(A[l]) < marks_sum(pivot))
            l++;
        while (marks_sum(A[r]) > marks_sum(pivot))
            r--;
        if (l <= r) {
            swap(&A[l], &A[r]);
            l++;
            r--;
        }
    }

    if (first < r)
        quick_sort(A, n, first, r);
    if (l < last)
        quick_sort(A, n, l, last);
}

/*
7
Ivanov Alex 1 85 100 75
Andreev Leonid 1 95 100 95
Tsarev Anatoliy 4 100 100 100
Sergeev Ivan 2 95 70 85
Petrov Viktor 1 100 90 95
Topolev Alexey 1 100 95 95
Denisov Nikolay 2 100 95 100
*/
