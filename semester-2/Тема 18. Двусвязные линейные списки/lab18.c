#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
    struct node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void push_back(List *, int);
void push_start(List *, int);
int pop_back(List *);
int pop_start(List *);
void print(List *);
void print_reverse(List *);
int sum(List *);
void scan(List *);
void add_random_nodes_to_end(List *, int, int, int);
void clear(List *);

int main(void) {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL; l->tail = NULL;
    scan(l);

    pop_start(l); pop_start(l);
    print(l);
    printf("%d\n", sum(l));

    return 0;
}

void push_back(List *l, int val) {
    Node *el = (Node *)malloc(sizeof(Node));
    el->val = val;
    el->next = NULL;

    if (l->tail == NULL) {
        el->prev = NULL;
        l->head = el;
        l->tail = el;
    } else {
        el->prev = l->tail;
        l->tail->next = el;
        l->tail = el;
    }
}

void push_start(List *l, int val) {
    Node *el = (Node *)malloc(sizeof(Node));
    el->val = val;
    el->prev = NULL;

    if (l->head == NULL) {
        el->next = NULL;
        l->head = el;
        l->tail = el;
    } else {
        el->next = l->head;
        l->head->prev = el;
        l->head = el;
    }
}

int pop_back(List *l) {
    if (l->tail == NULL)
        exit(EXIT_FAILURE);

    int val = l->tail->val;
    if (l->tail == l->head) {
        free(l->tail);
        l->tail = NULL;
        l->head = NULL;
    } else {
        Node *el = l->tail;
        l->tail = el->prev;
        free(el);
        l->tail->next = NULL;
    }

    return val;
}

int pop_start(List *l) {
    if (l->tail == NULL)
        exit(EXIT_FAILURE);

    int val = l->head->val;
    if (l->tail == l->head) {
        free(l->tail);
        l->tail = NULL;
        l->head = NULL;
    } else {
        Node *el = l->head;
        l->head = el->next;
        free(el);
        l->head->prev = NULL;
    }

    return val;
}

void print(List *l) {
    if (l->head == NULL)
        return;

    Node *el = l->head;
    while (el != NULL) {
        printf("%4d", el->val);
        el = el->next;
    } printf("\n");
}

void print_reverse(List *l) {
    if (l->head == NULL)
        return;

    Node *el = l->tail;
    while (el != NULL) {
        printf("%4d", el->val);
        el = el->prev;
    } printf("\n");
}

int sum(List *l) {
    if (l->head == NULL)
        exit(EXIT_FAILURE);

    int s = 0;
    Node *el = l->head;
    while (el != NULL) {
        s += el->val;
        el = el->next;
    }

    return s;
}

void scan(List *l) {
    int val;
    while (scanf("%d", &val) == 1)
        push_back(l, val);
}
void add_random_nodes_to_end(List *l, int n, int a, int b) {
    for (int i = 0; i < n; i++)
        push_back(l, a + rand() %(b - a + 1));
}

void clear(List *l) {
    while (l->head != NULL)
        pop_back(l);
}


// 42 7 23 19 5 80 74 6 n
