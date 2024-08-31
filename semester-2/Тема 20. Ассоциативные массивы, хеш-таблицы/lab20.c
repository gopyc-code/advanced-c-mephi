#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 13
#define FNAME "main.txt"


typedef char *String;

typedef struct node {
    String val;
    struct node *next;
} Node;

typedef struct {
    Node **mas;
    int size;
} HashTable;

typedef HashTable *pHashTable;

pHashTable get_phash_table();
int hash(String);
int search(pHashTable, String);
int longest_chain_len(pHashTable);
int count_nodes(pHashTable);
double get_fill_factor(pHashTable);
void delete_table(pHashTable);
void insert(pHashTable, String);
void print_table(pHashTable);
void scan_file(pHashTable);
void scan(pHashTable);
void empty_string(String);

int main(void) {
    pHashTable table = get_phash_table();

    scan(table);
    //scan_file(table);
    //print_table(table);

    char searchval[20];
    scanf("%s", searchval);
    if (search(table, searchval) != 0)
        printf("%s\n", searchval);
    else
        printf("not found\n");

    printf("%d\n", longest_chain_len(table));
    printf("%1.2lf\n", get_fill_factor(table));

    return 0;
}

int hash(String key) {
    int hsum = 0;

    for (int i = 0; i < strlen(key); i++)
        hsum = (100000 * hsum + (int)key[i]) % SIZE;

    return hsum;
}

pHashTable get_phash_table() {
    pHashTable table = (pHashTable)malloc(sizeof(HashTable));
    table->mas = (Node **)calloc(SIZE, sizeof(Node *));
    table->size = SIZE;

    for (int i = 0; i < table->size; i++)
        table->mas[i] = NULL;

    return table;
}

int search(pHashTable table, String val) {
    int ind = hash(val), cmps = 0;

    Node *cur = table->mas[ind];
    while (cur != NULL) {
        cmps++;
        if (strcasecmp(cur->val, val) == 0)
            return cmps;
        cur = cur->next;
    }

    return 0;
}

int longest_chain_len(pHashTable table) {
    int maxl = 0;

    Node *cur;
    for (int ind = 0; ind < table->size; ind++) {
        int l = 0;
        cur = table->mas[ind];

        while (cur != NULL) {
            cur = cur->next;
            l++;
        }

        if (l > maxl)
            maxl = l;
    }

    return maxl;
}

int count_nodes(pHashTable table) {
    int c = 0;

    Node *cur;
    for (int ind = 0; ind < table->size; ind++) {
        cur = table->mas[ind];

        while (cur != NULL) {
            cur = cur->next;
            c++;
        }
    }

    return c;
}

double get_fill_factor(pHashTable table) {
    return (double)count_nodes(table) / table->size;
}

void delete_table(pHashTable table) {
    Node *cur, *temp;
    for (int ind = 0; ind < table->size; ind++) {
        cur = table->mas[ind];

        while (cur != NULL) {
            temp = cur;
            cur = cur->next;
            free(temp->val);
            free(temp);
        }
    }

    free(table->mas);
    free(table);
}

void insert(pHashTable table, String val) {
    int ind = hash(val);
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = (String)calloc(
                strlen(val) + 1, sizeof(char));
    strcpy(node->val, val);
    node->next = table->mas[ind];
    table->mas[ind] = node;
}

void print_table(pHashTable table) {
    for (int ind = 0; ind < table->size; ind++)
        if (table->mas[ind] != NULL) {
            printf("%2d.", ind);

            Node *cur = table->mas[ind];
            while (cur != NULL) {
                printf(" %s", cur->val);
                cur = cur->next;
            }

            printf("\n");
        }
}

void scan_file(pHashTable table) {
    FILE *f;
    f = fopen(FNAME, "r");

    char curval[20];
    for (int i = 0; i < 10; i++) {
        fscanf(f, "%s", curval);
        insert(table, curval);
        empty_string(curval);
    }
}

void scan(pHashTable table) {
    char curval[20];
    for (int i = 0; i < 10; i++) {
        scanf("%s", curval);
        insert(table, curval);
        empty_string(curval);
    }
}

void empty_string(String s) {
    for (int i = 0; s[i]; i++)
        s[i] = 0;
}

/*
42 7 23 19 5 80 74 6 n
20 31 22 24 10 15 7 1 8 9 n
*/
