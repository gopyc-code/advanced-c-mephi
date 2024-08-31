#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 13
#define STR_LEN 20
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
void insert_val(pHashTable, String);
int remove_val(pHashTable, String);
void print_table(pHashTable);
void scan_file(pHashTable);
void scan(pHashTable);
void empty_string(String);

int main(void) {
    pHashTable table = get_phash_table();

    //scan(table);
    scan_file(table);
    print_table(table);

    char ins1[STR_LEN], ins2[STR_LEN];
    scanf("%s%s", ins1, ins2);
    insert_val(table, ins1);
    insert_val(table, ins2);

    char rem[STR_LEN];
    scanf("%s", rem);
    if (remove_val(table, rem) == 0)
        printf("!\n");

    printf("%d\n", longest_chain_len(table));
    printf("%1.2lf\n", get_fill_factor(table));

    print_table(table);

    delete_table(table);

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

void insert_val(pHashTable table, String val) {
    int ind = hash(val);
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = (String)calloc(
                strlen(val) + 1, sizeof(char));
    strcpy(node->val, val);
    node->next = table->mas[ind];
    table->mas[ind] = node;
}

int remove_val(pHashTable table, String val) {
    int ind = hash(val);
    Node **node = &(table->mas[ind]);

    if (*node == NULL)
        return 0;

    if (strcasecmp((*node)->val, val) == 0) {
        Node *tmp = (*node)->next;
        free((*node)->val);
        free(*node);
        table->mas[ind] = tmp;
        return 1;
    }

    while ((*node)->next != NULL) {
        if (strcasecmp((*node)->next->val, val) == 0) {
            Node *tmp = (*node)->next;
            (*node)->next = (*node)->next->next;
            free(tmp->val);
            free(tmp);
            return 1;
        } node = &((*node)->next);
    } return 0;
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

    char curval[STR_LEN];
    for (int i = 0; i < 10; i++) {
        fscanf(f, "%s", curval);
        insert_val(table, curval);
        empty_string(curval);
    }
}

void scan(pHashTable table) {
    char curval[STR_LEN];
    for (int i = 0; i < 10; i++) {
        scanf("%s", curval);
        insert_val(table, curval);
        empty_string(curval);
    }
}

void empty_string(String s) {
    for (int i = 0; s[i]; i++)
        s[i] = 0;
}

/*
Alexey
Ivan
Danyl
Artyom
Maksim
Nikolai
Boris
Viktor
Sergey
Artur

Afanasiy
Anatoliy
Petr
*/
