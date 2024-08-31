#include <stdio.h>
#include <stdlib.h>

#define LEN 40

/* Тесты:
Для 40 чисел:
От 1 до 10:
2 6 9 10 5 7 3 5 4 2 6 4 7 8 3 4 9 1 8 10 10 6 9 4 1 8 4 2 2 7 5 10 5 5 2 1 1 10 1 1
От 1 до 100:
4 63 64 84 25 49 22 65 36 52 36 65 91 2 17 18 13 11 22 85 27 27 46 15 81 48 100 67 75 5 82 48 33 61 55 100 79 41 91 22

Для 7 чисел:
Плохих:
3 6 6 3 6 6 6
От 1 до 100:
63 96 88 2 94 41 6
Базовый пример из задания:
5 2 6 4 2 7 3
Убывающая последовательность:
7 6 5 4 3 2 1
*/

int max(int a1, int a2);
void seq (int ind, int *stind, int *l,
          int *m, int *st, int maxl);

int main(void) {
    // l[i] — длина самой длинной последовательности,
    // начинающейся с k
    int m[LEN], l[LEN];
    for (int i = 0; i < LEN; i++) {
        scanf("%d", &m[i]);
        l[i] = 1;
    }

    // Ищем макс. длину
    int maxl = 1, result;
    for (int k = LEN - 1; k != -1; k--) {
        result = 1;
        for (int i = k + 1; i < LEN; i++)
            if (m[i] >= m[k])
                result = max(result, 1 + l[i]);
        l[k] = result;
        maxl = max(maxl, result);
    }

    // Выводим макс. длину
    printf("%d\n", maxl);

    // Создаём массив для
    // некоторой подпоследовательности
    // st максимальной длины
    int st[maxl];
    for (int i = 0; i < maxl; i++)
        st[i] = -1;

    int stind = 0;
    for (int ind = 0; ind < LEN; ind++)
        if (l[ind] == maxl) {
            stind = 1;
            st[0] = m[ind];
            // Ищем st
            seq(ind, &stind, l, m, st, maxl);
        }

    return 0;
}

int max(int a1, int a2) {
    return (a1 > a2) ? a1 : a2;
}

void seq (int ind, int *stind, int *l,
          int *m, int *st, int maxl) {
    // Копируем st в stt
    int stt[maxl];
    for (int i = 0; i < maxl; i++)
        stt[i] = st[i];

    // Выводим stt
    if (l[ind] == 1)
        for (int i = 0; i < *stind; i++) {
            printf("%d", stt[i]);
            if (i + 1 != *stind)
                printf("%c", ' ');
            else
                printf("%c", '\n');
        }

    // Ищем другие подпоследовательности
    // макс. длины, начинающиеся на первый
    // элемент stt
    for (int j = ind + 1; j < LEN; j++)
        if ((l[j] == l[ind] - 1) &&
            (m[j] >= m[ind])) {
            stt[*stind] = m[j];
            (*stind)++;
            seq(j, stind, l, m, stt, maxl);
            (*stind)--;
        }
}
