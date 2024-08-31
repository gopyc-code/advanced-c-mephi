#include <stdio.h>
#include <stdlib.h>

void first_num_ascii(x) {
    int cur = 0;

    while (x) {
        cur = x % 10;
        x /= 10;
    }

    cur += 48;
    printf("%d:%5o%5d%5X\n", cur - 48, cur, cur, cur);
}

int main() {
    int a, b, c;
    scanf("%d%d", &a, &b);

    c = 2 * (a + b);

    first_num_ascii(a);
    first_num_ascii(b);
    first_num_ascii(c);


    /*printf("\n");
    for (unsigned i = 0; i < 10; i++) {
        first_num_ascii(i);
    }*/

    return 0;
}
