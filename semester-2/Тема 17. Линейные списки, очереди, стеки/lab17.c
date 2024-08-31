#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;

typedef struct {
    Node *beg;
    Node *end;
} Queue;

void push(Queue *, int);
int pop(Queue *);
void print(Queue *);
int sum(Queue *);
void scan(Queue *);
void add_random_nodes(Queue *, int, int, int);
void clear(Queue *);

int main(void) {
    Queue *q = (Queue *)malloc(sizeof(Queue));

    scan(q);
    pop(q); pop(q);
    print(q);
    printf("%d\n", sum(q));

    return 0;
}

void push(Queue *q, int val) {
    Node *el = (Node *)malloc(sizeof(Node));
    el->val = val;
    el->next = NULL;

    if (q->end == NULL) {
        q->beg = el;
        q->end = el;
    } else {
        q->end->next = el;
        q->end = el;
    }
}

int pop(Queue *q) {
    if (q->end == NULL)
        exit(EXIT_FAILURE);

    int val = q->beg->val;
    if (q->end == q->beg) {
        free(q->end);
        free(q->beg);
        q->end = NULL;
        q->beg = NULL;
    } else {
        Node *el = q->beg;
        q->beg = el->next;
        free(el);
    }

    return val;
}

void print(Queue *q) {
    if (q->beg == NULL)
        return;

    Node *el = q->beg;
    while (el != NULL) {
        printf("%4d", el->val);
        el = el->next;
    } printf("\n");
}

int sum(Queue *q) {
    if (q->beg == NULL)
        exit(EXIT_FAILURE);

    int s = 0;
    Node *el = q->beg;
    while (el != NULL) {
        s += el->val;
        el = el->next;
    }

    return s;
}

void scan(Queue *q) {
    int val;
    while (scanf("%d", &val) == 1 && getchar() != 'n')
        push(q, val);
}

void add_random_nodes(Queue *q, int n, int a, int b) {
    for (int i = 0; i < n; i++)
        push(q, a + rand() %(b - a + 1));
}

void clear(Queue *q) {
    while (q->beg != NULL)
        pop(q);
}

// 42 7 23 19 5 80 74 6 n
