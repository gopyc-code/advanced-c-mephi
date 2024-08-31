#include <stdio.h>
#include <stdlib.h>

int main(void) {
    long a, b, c;
    scanf("%ld%ld%ld", &a, &b, &c);

    long m, k;
    scanf("%ld", &m);

    // mid one number
    if (a < b && b < c)
        printf("%ld", b);
    else if (a < c && c < b)
        printf("%ld", c);
    else if (b < a && a < c)
        printf("%ld", a);
    else if (b < c && c < a)
        printf("%ld", c);
    else if (c < a && a < b)
        printf("%ld", a);
    else if (c < b && b < a)
        printf("%ld", b);

    // all equal
    if (a == b && b == c)
        printf("%ld=%ld=%ld", a, b, c);

    // 2 max 1 min
    else if (a == b && b > c)
        printf("%ld=%ld>%ld", b, a, c);
    else if (a == c && c > b)
        printf("%ld=%ld>%ld", a, c, b);
    else if (c == b && b > a)
        printf("%ld=%ld>%ld", c, b, a);

    // 2 min 1 max
    else if (a == b && b < c)
        printf("%ld=%ld<%ld", b, a, c);
    else if (a == c && c < b)
        printf("%ld=%ld<%ld", a, c, b);
    else if (c == b && b < a)
        printf("%ld=%ld<%ld", c, b, a);

    printf("\n\n");




    // k
    long mul = 1;
    for (int i = 0; ; i++) {
        if (mul > m) {
            printf("%ld\n\n", i);
            break;
        }
        mul *= 3L;
    }

    // stepeni 1 3 / 2 9 / 3 27
    mul = 1;
    for (int i = 1; i <= 15; i++) {
        mul *= 3;
        printf("%3ld  %ld\n", i, mul);
    }

    return 0;
}
