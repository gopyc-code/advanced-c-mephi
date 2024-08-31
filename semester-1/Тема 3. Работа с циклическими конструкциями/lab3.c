#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int max_i, max_s = 0;
    for (unsigned i = 180; i <= 210; i++) {
        printf("%u  ", i);

        int c = 0, s = 0;
        for (int j = 2; j <= i / 2 + 1; j++) {
            if (!(i % j)) {
                printf("%3d", j);
                c++;
                s += j;

                int ok = 1;
                for (int k = j + 1; k <= i / 2 + 1; k++)
                    if (!(i % k)) {
                        printf(",");
                        break;
                    }

                if (!(c % 4) && j != i / 2 && j != i / 3) {
                    printf("\n     ");
                }
            }
        }
        if (!(c % 4)) {
            if (!c)
                for (int i3 = 0; i3 <= 14; i3++)
                    printf(" ");
            printf("   %3d", s);
        } else {
            for (int i2 = 0; i2 < (4 - (c % 4)) * 4 + 3; i2++)
                printf(" ");
            printf("%3d", s);
        }
        printf("\n");

        if (s >= max_s) {
            max_s = s;
            max_i = i;
        }
    }
    printf("\n%d\n", max_i);
}
