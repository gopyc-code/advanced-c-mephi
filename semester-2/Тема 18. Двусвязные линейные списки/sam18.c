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
Node *search(List *, int);
void insert(List *, Node *, int);
void insert_nodes(List *, Node *, int *, int);
int remove_node(List *, Node *);

int main(void) {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL; l->tail = NULL;
    scan(l);

    while (getchar() != '\n');
    int search_val, ins_vals[100], n = 0, t;
    scanf("%d", &search_val);
    while (scanf("%d", &t) == 1) {
        ins_vals[n] = t;
        n++;
    }

    Node *position = search(l, search_val);
    if (position != NULL) {
        insert_nodes(l, position, ins_vals, n);
        print(l);
        remove_node(l, position);
    }

    print(l);

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

Node *search(List *l, int val) {
    Node *el = l->head;

    while (el != NULL) {
        if (el->val == val)
            return el;
        el = el->next;
    }

    return NULL;
}

void insert(List *l, Node *prev, int val) {
    if (prev->next == NULL || prev == NULL)
        push_back(l, val);
    else {
        Node *el = (Node *)malloc(sizeof(Node));
        el->val = val;
        el->prev = prev;
        el->next = prev->next;
        prev->next->prev = el;
        prev->next = el;
    }
}

void insert_nodes(List *l, Node *prev, int *a, int n) {
    for (int i = 0; i < n; i++) {
        insert(l, prev, a[i]);
        prev = prev->next;
    }
}

int remove_node(List *l, Node *el) {
    if (el->next == NULL || el == NULL)
        return pop_back(l);
    else {
        int val = el->val;
        el->prev->next = el->next;
        el->next->prev = el->prev;
        free(el);
        return val;
    }
}

/*
42 7 23 19 5 80 74 6 n
19
38 51 n
*/
