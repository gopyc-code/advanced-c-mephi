#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, a_copy;
    scanf("%d", &a);
    a_copy = a;

    int mul = 1;
    while (a) {
        mul *= a % 10;
        a /= 10;
    }

    printf("%d\n", a_copy % mul);
    return 0;
}
