#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
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
void scan(List *);
Node *search(List *, int);
void insert(List *, Node *, int);

int main(void) {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL; l->tail = NULL;
    scan(l);

    while (getchar() != '\n');
    int search_val, ins_val;
    scanf("%d%d", &search_val, &ins_val);

    Node *position = search(l, search_val);
    if (position != NULL)
        insert(l, position, ins_val);

    print(l);

    return 0;
}

void push_back(List *l, int val) {
    Node *el = (Node *)malloc(sizeof(Node));
    el->val = val;
    el->next = NULL;

    if (l->tail == NULL) {
        l->head = el;
        l->tail = el;
    } else {
        l->tail->next = el;
        l->tail = el;
    }
}

void push_start(List *l, int val) {
    Node *el = (Node *)malloc(sizeof(Node));
    el->val = val;

    if (l->head == NULL) {
        el->next = NULL;
        l->head = el;
        l->tail = el;
    } else {
        el->next = l->head;
        l->head = el;
    }
}

int pop_back(List *l) {
    if (l->tail == NULL)
        exit(EXIT_FAILURE);

    int val = l->tail->val;
    if (l->tail == l->head) {
        free(l->tail);
        free(l->head);
        l->tail = NULL;
        l->head = NULL;
    } else {
        Node *el = l->head;
        while (el->next->next != NULL)
            el = el->next;
        free(el->next);
        el->next = NULL;
        l->tail = el;
    }

    return val;
}

int pop_start(List *l) {
    if (l->tail == NULL)
        exit(EXIT_FAILURE);

    int val = l->head->val;
    if (l->tail == l->head) {
        free(l->tail);
        free(l->head);
        l->tail = NULL;
        l->head = NULL;
    } else {
        Node *el = l->head;
        l->head = el->next;
        free(el);
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

void scan(List *l) {
    int val;
    while (scanf("%d", &val) == 1)
        push_back(l, val);
}

Node *search(List *l, int val) {
    Node *el = l->head;

    while (el != NULL) {
        if (el->val == val)
            return el;
        el = el->next;
    }

    return NULL;
}

void insert(List *l, Node *next, int val) {
    Node *el = l->head;
    if (el == next) {
        push_start(l, val);
        return;
    }

    while (el->next != next)
        el = el->next;
    Node *ins = (Node *)malloc(sizeof(Node));
    ins->val = val;
    ins->next = next;
    el->next = ins;
}

// 42 7 23 19 5 80 74 6 n
