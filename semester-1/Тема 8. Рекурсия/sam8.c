#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

int sum_over(long n, long m);
long fib(char k, char lvl, long p);
void save(char arg, long ret, char lvl, long p);
long fib1(char k);

#define N 165000000

char lvls[N], args[N];
long rets[N], calls[N];
int err = 0;

int main(void) {
    setlocale(LC_ALL,"");

    long k;
    scanf("%ld", &k);

    // Ответ на первую часть задания
    long ans = fib1(k);
    if (!err)
        printf("%ld\n", ans);
    else {
        printf("!\n");
    }

    /*
    // Находим, сколько вызовов функции нужно,
    // чтобы вычислить значение промежуточного
    // числа Фибоначчи
    calls[1] = 1, calls[2] = 1;
    for (long i = 3; i <= k; i++) {
        if (sum_over(calls[i - 1] + 1, calls[i - 2])) {
            printf("!\n");
            return 0;
        } calls[i] = 1 + calls[i - 1] + calls[i - 2];
    }

    // Запускаем функцию, проверяем возможность
    // хранения в массивах всех промежуточных чисел.
    // При такой реализации макс. номер не более 39
    ans = fib(k, 0, 0);
    if (err) {
        printf("!\n");
        return 0;
    }

    // Определяем глубину рекурсии для каждого
    // номера числа Фибоначчи
    long max_lvl = 0;
    for (long i = 0; i < calls[k]; i++)
        if (lvls[i] > max_lvl)
            max_lvl = lvls[i];

    // Проходимся по массиву, заполненному
    // рекурсивно вычисленными числами
    // Фибоначчи, и выводим их
    printf("+———————————+———————+————————————+\n");
    printf("|           | Спуск |   Возврат  |\n");
    long start;
    for (long lvl = 0; lvl <= max_lvl; lvl++) {
        printf("|———————————+———————+————————————|\n");
        start = 1;
        for (long i = 0; i < calls[k]; i++)
            if (lvls[i] == lvl) {
                if (start) {
                    printf("|%2ld уровень", lvls[i]);
                    start = 0;
                } else {
                    printf("|          ");
                }
                printf(" | f(%2ld) | %10ld |\n",
                       args[i], rets[i]);
            }
    } printf("+———————————+———————+————————————+\n");
    */

    return 0;
}

// Сохраняем рекурсивно вычисленные числа
// Фибоначчи и их свойства
void save(char arg, long ret, char lvl, long p) {
    args[p] = arg;
    rets[p] = ret;
    lvls[p] = lvl;
}

// Рекурсивно вычисляем числа Фибоначчи
long fib(char k, char lvl, long p) {
    if (p >= N) {
        err = 1;
        return 0;
    }

    if (err)
        return 0;

    if (k < 3) {
        save(k, 1, lvl, p);
        return 1;
    }

    if (sum_over(p, calls[k - 1] + 1)) {
        err = 1;
        return 0;
    }

    long f1 = fib(k - 1, lvl + 1, p + 1);
    long f2 = fib(k - 2, lvl + 1, p + calls[k - 1] + 1);
    if (sum_over(f1, f2)) {
        err = 1;
        return 0;
    }
    save(k, f1 + f2, lvl, p);
    return f1 + f2;
}

// Проверяем переполнение суммы
int sum_over(long n, long m) {
    return (n > LONG_MAX - m);
}

long fib1(char k) {
    if (err)
        return 0;

    if (k < 3) {
        return 1;
    }

    long f1 = fib1(k - 1), f2 = fib1(k - 2);
    if (sum_over(f1, f2)) {
        err = 1;
        return 0;
    } return f1 + f2;
}
