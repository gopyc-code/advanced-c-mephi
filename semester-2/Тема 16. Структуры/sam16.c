#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sportsman {
    char surname[15];
    char name[15];
    struct Address {
        char city[15];
        char street[15];
        int house;
        int flat;
    } address;
    char section[15];
    int point;
};

struct Section {
    int min_point;
    char name[15];
    int finalists_number;
    struct Sportsman finalists[20];
};

struct City {
    char name[15];
    int finalists_number;
};

void scan_sportsman(struct Sportsman *);
void print_sportsman(struct Sportsman);
void swap_sportsman(struct Sportsman *, struct Sportsman *);
void swap_city(struct City *, struct City *);
void copy(struct Sportsman, struct Sportsman *);
int is_equal(struct Sportsman, struct Sportsman);
int point_cmp(struct Sportsman, struct Sportsman);
int section_cmp(struct Sportsman, struct Sportsman);
void quick_sort_sportsman(struct Sportsman *, int, int,
                int (*)(struct Sportsman, struct Sportsman));
void quick_sort_city(struct City *, int, int);
void print_sections_and_min_points(struct Section *, int);
void form_sections(struct Section *, int, struct Sportsman *, int, int);
void print_sections_and_finalists(struct Section *,
                                  int, struct Sportsman *, int);
void get_sections(struct Section *, int *, struct Sportsman *, int);
void get_cities(struct City *, int *, struct Section *, int);
void print_ordered_cities(struct City *, int, struct Sportsman *, int);

int main(void) {
    ///*
    int n;
    scanf("%d", &n);
    struct Sportsman a[n];
    for (int i = 0; i < n; i++)
        scan_sportsman(&a[i]);
    //*/

    /*
    struct Sportsman a[100];
    FILE *f;
    f = fopen("main.txt", "r");

    int n = 0;
    while (!feof(f)) {
        fscanf(f, "%s%s%s%s%d%d%s%d",
          a[n].surname, a[n].name,
          a[n].address.city, a[n].address.street,
          &a[n].address.house, &a[n].address.flat,
          a[n].section, &a[n].point);
        n++;
    }
    */

    int finalists;
    scanf("%d", &finalists);

    struct Section sections[n];
    int sections_number = 0;
    get_sections(sections, &sections_number, a, n);

    struct Sportsman acopy[n];
    for (int i = 0; i < n; i++)
        copy(a[i], &acopy[i]);

    form_sections(sections, sections_number, acopy, n, finalists);
    print_sections_and_min_points(sections, sections_number);
    print_sections_and_finalists(sections, sections_number, a, n);

    struct City cities[n];
    int cities_number = 0;
    get_cities(cities, &cities_number, sections, sections_number);
    printf("%d\n\n", cities_number);
    print_ordered_cities(cities, cities_number, a, n);

    return 0;
}

void scan_sportsman(struct Sportsman *a) {
    scanf("%s%s%s%s%d%d%s%d",
          a->surname, a->name,
          a->address.city, a->address.street,
          &a->address.house, &a->address.flat,
          a->section, &a->point);
}

// Debug
void print_sportsman(struct Sportsman a) {
    printf("%s %s %s %s %d %d %s %d\n",
          a.surname, a.name,
          a.address.city, a.address.street,
          a.address.house, a.address.flat,
          a.section, a.point);
}

void swap_sportsman(struct Sportsman *a, struct Sportsman *b) {
    struct Sportsman tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_city(struct City *a, struct City *b) {
    struct City tmp = *a;
    *a = *b;
    *b = tmp;
}

void copy(struct Sportsman a, struct Sportsman *b) {
    strcpy(b->surname, a.surname);
    strcpy(b->name, a.name);
    strcpy(b->address.city, a.address.city);
    strcpy(b->address.street, a.address.street);
    b->address.house = a.address.house;
    b->address.flat = a.address.flat;
    strcpy(b->section, a.section);
    b->point = a.point;
}

int is_equal(struct Sportsman a, struct Sportsman b) {
    return (
        (strcasecmp(b.surname, a.surname) == 0) &&
        (strcasecmp(b.name, a.name) == 0) &&
        (strcasecmp(b.address.city, a.address.city) == 0) &&
        (strcasecmp(b.address.street, a.address.street) == 0) &&
        (b.address.house == a.address.house) &&
        (b.address.flat == a.address.flat) &&
        (strcasecmp(b.section, a.section) == 0) &&
        (b.point == a.point)
    );
}


int point_cmp(struct Sportsman a, struct Sportsman b) {
    if (a.point > b.point)
        return 1;
    if (a.point == b.point)
        return 0;
    return -1;
}

int section_cmp(struct Sportsman a, struct Sportsman b) {
    return strcasecmp(a.section, b.section);
}

void quick_sort_sportsman(struct Sportsman *A, int first, int last,
                int (*cmp)(struct Sportsman, struct Sportsman)) {
    int l = first, r = last;
    struct Sportsman pivot = A[(l + r) / 2];

    while (l <= r) {
        while (cmp(A[l], pivot) < 0)
            l++;
        while (cmp(A[r], pivot) > 0)
            r--;
        if (l <= r) {
            swap_sportsman(&A[l], &A[r]);
            l++;
            r--;
        }
    }

    if (first < r)
        quick_sort_sportsman(A, first, r, cmp);
    if (l < last)
        quick_sort_sportsman(A, l, last, cmp);
}

void quick_sort_city(struct City *A, int first, int last) {
    int l = first, r = last;
    struct City pivot = A[(l + r) / 2];

    while (l <= r) {
        while (A[l].finalists_number > pivot.finalists_number)
            l++;
        while (A[r].finalists_number < pivot.finalists_number)
            r--;
        if (l <= r) {
            swap_city(&A[l], &A[r]);
            l++;
            r--;
        }
    }

    if (first < r)
        quick_sort_city(A, first, r);
    if (l < last)
        quick_sort_city(A, l, last);
}

void print_sections_and_min_points(struct Section *sections, int sections_number) {
    for (int i = 0; i < sections_number; i++)
        printf("%s %d\n", sections[i].name, sections[i].min_point);
    printf("\n");
}

void form_sections(struct Section *sections, int sections_number,
                   struct Sportsman *acopy, int n, int finalists) {
    quick_sort_sportsman(acopy, 0, n - 1, section_cmp);
    int partition[sections_number + 1];
    partition[0] = 0;
    int partition_pointer = 1;
    for (int i = 1; i <= n; i++)
        if (i == n || strcasecmp(acopy[i].section, acopy[i - 1].section) != 0) {
            partition[partition_pointer] = i;
            quick_sort_sportsman(acopy, partition[partition_pointer - 1],
                       partition[partition_pointer] - 1, point_cmp);
            partition_pointer++;
        }

    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < sections_number; j++)
            if (strcasecmp(sections[j].name, acopy[i].section) == 0 &&
                sections[j].finalists_number < finalists) {
                copy(acopy[i], &(sections[j].finalists[sections[j].finalists_number]));
                (sections[j].finalists_number)++;
                if (sections[j].min_point > acopy[i].point)
                    sections[j].min_point = acopy[i].point;
            }
}

void print_sections_and_finalists(struct Section *sections,
                                  int sections_number, struct Sportsman *a, int n) {
    for (int i = 0; i < sections_number; i++) {
        printf("%s\n", sections[i].name);
        for (int j = 0; j < n; j++)
            for (int k = 0; k < sections[i].finalists_number; k++)
                if (is_equal(sections[i].finalists[k], a[j]))
                    printf(" %s\n", a[j].surname);
    } printf("\n");
}

void get_sections(struct Section *sections, int *sections_number, struct Sportsman *a, int n) {
    int exists;
    for (int i = 0; i < n; i++) {
        exists = 0;
        for (int j = 0; j < *sections_number; j++)
            if (strcasecmp(a[i].section, sections[j].name) == 0) {
                exists = 1;
                break;
            }
        if (!exists) {
            strcpy(sections[*sections_number].name, a[i].section);
            sections[*sections_number].min_point = 100;
            (*sections_number)++;
        }
    }
}

void get_cities(struct City *cities, int *cities_number,
                struct Section *sections, int sections_number) {
    int exists;
    struct Sportsman finalist;
    for (int i = 0; i < sections_number; i++)
        for (int j = 0; j < sections[i].finalists_number; j++) {
            copy(sections[i].finalists[j], &finalist);

            exists = 0;
            for (int k = 0; k < *cities_number; k++)
                if (strcasecmp(finalist.address.city, cities[k].name) == 0) {
                    exists = 1;
                    (cities[k].finalists_number)++;
                    break;
                }
            if (!exists) {
                strcpy(cities[*cities_number].name, finalist.address.city);
                cities[*cities_number].finalists_number = 1;
                (*cities_number)++;
            }
        }
}

void print_ordered_cities(struct City *cities, int cities_number,
                              struct Sportsman *a, int n) {
    quick_sort_city(cities, 0, cities_number - 1);
    for (int i = 1; i < cities_number; i += 2) {
        if (cities[i].finalists_number == cities[i - 1].finalists_number) {
            for (int j = 0; j < n; j++) {
                if (strcasecmp(a[j].address.city, cities[i].name) == 0) {
                    printf("%s %s", cities[i].name, cities[i - 1].name);
                    break;
                } else if (strcasecmp(a[j].address.city, cities[i - 1].name) == 0) {
                    printf("%s %s", cities[i - 1].name, cities[i].name);
                    break;
                }
            }
        } else
            printf("%s %s", cities[i - 1].name, cities[i].name);
        if (n % 2 || i != n - 1)
            printf(" ");
    } if (cities_number % 2)
        printf("%s", cities[cities_number - 1].name);
    printf("\n");
}

/*
25
Popov Artyom Saratov Mira 35 14 Tennis 85
Sokolov Maksim Pyshma Lenin 49 28 Boxing 96
Petrov Ivan Samara Sovetskaya 42 75 Tennis 100
Vassiliev Artyom Samara Sadovaya 11 5 Tennis 89
Fyodorov Danyl Samara Sadovaya 6 96 Boxing 86
Fyodorov Artyom Moscow Sadovaya 19 50 Sprint 95
Morozov Maksim Pyshma Novaya 7 20 Tennis 88
Popov Nikolai Pyshma Tsentralnaya 31 3 Boxing 92
Ivanov Maksim Moscow Oktyabrya 26 57 Boxing 100
Popov Nikolai Pyshma Sadovaya 47 56 Sprint 97
Morozov Roman Pyshma Sadovaya 17 41 Tennis 89
Novikov Denis Moscow Tsentralnaya 16 2 Sprint 87
Petrov Dmitry Moscow Lenin 6 25 Tennis 87
Russkih Artem Moscow Igrovaya 22 8 Dota 100
Smirnov Ivan Pyshma Sadovaya 11 98 Boxing 99
Popov Roman Moscow Lenin 39 25 Boxing 97
Vassiliev Roman Pyshma Sadovaya 39 61 Tennis 90
Petrov Dmitry Pyshma Lenin 23 65 Tennis 88
Novikov Aleksandr Moscow Sovetskaya 2 49 Boxing 91
Fyodorov Yevgeny Samara Sadovaya 13 100 Boxing 87
Popov Ivan Samara Mira 12 20 Boxing 97
Sokolov Denis Samara Lenin 23 0 Sprint 89
Bogatyrev Maksim Murom Knyaz 13 16 Boxing 100
Popov Alexey Moscow Tsentralnaya 14 82 Sprint 99
Morozov Danyl Pyshma Mira 28 86 Tennis 86
5

from random import choice, randint

names = (
    "Artyom", "Aleksandr", "Roman", "Yevgeny", "Ivan",
    "Maksim", "Denis", "Alexey", "Dmitry", "Danyl",
    "Sergey", "Nikolai"
)

surnames = (
    "Ivanov", "Smirnov", "Petrov", "Sidorov", "Popov",
    "Vassiliev", "Sokolov", "Novikov", "Fyodorov", "Morozov"
)

cities = ("Moscow", "Samara", "Saratov", "Pyshma")
streets = (
    "Tsentralnaya", "Sovetskaya", "Sadovaya",
    "Lenin", "Mira", "Novaya", "Oktyabrya"
)
sections = ("Boxing", "Tennis", "Sprint")

for i in range(25):
	print(choice(surnames), choice(names), choice(cities), choice(streets),
		randint(1, 50), randint(1, 100), choice(sections), randint(85, 100))
*/
