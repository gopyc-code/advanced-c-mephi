#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LEN 100

void empty (char *s, int l);

int main(void) {
    unsigned char c, s[LEN], maxs[LEN] = "";
    int p = 0;

    //FILE *f;
    //f = fopen("out.txt", "w");

    while ((c = getchar()) != '\n') {
        if (isblank(c)) {
            if (!p)
                continue;
            putchar('\n');
            //putc('\n', f);
            if (strlen(s) >= strlen(maxs)) {
                strcpy(maxs, s);
            }
            p = 0;
            empty(s, LEN);
        } else if (isalpha(c)) {
            putchar(c);
            //putc(c, f);
            s[p] = c;
            p++;
        }
    }

    if (strlen(s) >= strlen(maxs))
        strcpy(maxs, s);

    if (p) {
        //fputs("\n", f);
        printf("\n");
    }
    printf("\n%s\n", maxs);
    //fputs("\n", f); fputs(maxs, f);
    //fputs("\n", f);

    //fclose(f);

    return 0;
}

void empty (char *s, int l) {
    for (int i = 0; i < l; i++)
        s[i] = 0;
}
