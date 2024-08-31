#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} Node;

typedef Node *pNode;

typedef struct qnode {
    pNode val;
    struct qnode *next;
} qNode;

typedef struct {
    qNode *beg;
    qNode *end;
} Queue;

void scan_tree(pNode *);
void insert(pNode *, int);
int count_levels(pNode);
int children_sum(pNode);
void add_random_nodes(pNode *, int, int, int);
void delete_tree(pNode *);

void push_queue(Queue *, pNode);
pNode pop_queue(Queue *);

void print_inorder(pNode);
void print_preorder(pNode);
void print_breadth_first(pNode);
void pretty_print(pNode);
int quick_pow(int, int);
pNode search(pNode, int);

pNode _delete_node(pNode, int);
void _delete_root(pNode *, int);
void delete_node(pNode *, int);
void delete_nodes_by_interval(pNode *, int, int);

int main(void) {
    pNode root = NULL;
    scan_tree(&root);

    int val;
    while (getchar() != '\n');
    scanf("%d", &val);


    //print_preorder(root);
    pretty_print(root);


    printf("\n");
    delete_node(&root, val);


    pretty_print(root);
    //print_preorder(root);


    printf("\n%d\n", children_sum(root));

    return 0;
}

void scan_tree(pNode *p) {
    int d;
    while (scanf("%d", &d) == 1)
        insert(p, d);
}

void insert(pNode *p, int val) {
    if (*p == NULL) {
        *p = (pNode) malloc(sizeof(Node));
        (*p)->val = val;
        (*p)->left = NULL;
        (*p)->right = NULL;
    } else {
        if (val < (*p)->val)
            insert(&((*p)->left), val);
        else
            insert(&((*p)->right), val);
    }
}

int count_levels(pNode p) {
    if (p == NULL)
        return 0;

    int nleft = count_levels(p->left);
    int nright = count_levels(p->right);
    return 1 + ((nleft > nright) ? nleft : nright);
}

int children_sum(pNode p) {
    if (p == NULL)
        return 0;

    int res = 0;
    if (p->left == NULL && p->right == NULL)
        res = p->val;
    res += children_sum(p->left);
    res += children_sum(p->right);

    return res;
}

void add_random_nodes(pNode *p, int n, int a, int b) {
    for (int i = 0; i < n; i++)
        insert(p, a + rand() % (b - a + 1));
}

void delete_tree(pNode *p) {
    if ((*p) != NULL) {
        delete_tree(&((*p)->left));
        delete_tree(&((*p)->right));
        free(*p);
        *p = NULL;
    }
}

void push_queue(Queue *q, pNode val) {
    qNode *el = (qNode *)malloc(sizeof(qNode));
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

pNode pop_queue(Queue *q) {
    if (q->beg == NULL)
        exit(EXIT_FAILURE);

    pNode val = q->beg->val;

    if (q->end == q->beg) {
        q->end = NULL;
        q->beg = NULL;
    } else {
        qNode *el = q->beg;
        q->beg = el->next;
        free(el);
    }

    return val;
}

void print_inorder(pNode p) {
    if (p != NULL) {
        print_preorder(p->left);
        printf("%3d", p->val);
        print_preorder(p->right);
    }
}

void print_preorder(pNode p) {
    if (p != NULL) {
        printf("%3d", p->val);
        print_preorder(p->left);
        print_preorder(p->right);
    }
}

void print_breadth_first(pNode root) {
    if (root == NULL)
        return;

    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->beg = NULL; q->end = NULL;
    push_queue(q, root);

    qNode *p = q->beg;
    while (p != NULL) {
        if (p->val->left != NULL)
            push_queue(q, p->val->left);
        if (p->val->right != NULL)
            push_queue(q, p->val->right);
        p = p->next;
    }

    while (q->beg != NULL)
        printf("%3d", pop_queue(q)->val);
}

void pretty_print(pNode root) {
    if (root == NULL)
        return;

    int n = count_levels(root);
    int N = quick_pow(2, n);
    pNode *a = (pNode *)malloc(N * (sizeof(pNode) + sizeof(Node)));

    a[1] = root;
    for (int i = 2; i < N; i++)
        a[i] = NULL;

    for (int i = 1; i < N; i++)
        if (a[i] != NULL) {
            a[2 * i] = a[i]->left;
            a[2 * i + 1] = a[i]->right;
        }

    N = 2 * N - 1;
    for (int i = 1; i <= n; i++) {
        int lvln = quick_pow(2, i - 1);
        int start_space = (N / lvln - 3) / 2;
        int spaces = (i == 1) ? 0 :
            (N - 2 * start_space - 3 * lvln) / (lvln - 1);

        for (int j = 0; j < start_space; j++)
            printf(" ");
        for (int j = lvln; j < 2 * lvln; j++) {
            if (a[j] != NULL)
                printf("%3d", a[j]->val);
            else
                printf("   ");
            for (int k = 0; k < spaces; k++)
                printf(" ");
        } printf("\n");
    }

    a = NULL;
}

int quick_pow(int a, int n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return a;
    if (n % 2)
        return a * quick_pow(a, n - 1);
    else {
        int r = quick_pow(a, n / 2);
        return r * r;
    }
}

pNode search(pNode root, int val) {
    if (root == NULL)
        return NULL;
    if (root->val == val)
        return root;

    if (val < root->val)
        return search(root->left, val);
    return search(root->right, val);
}

pNode _delete_node(pNode root, int val) {
    if (root == NULL)
        return NULL;

    if (val < root->val)
        root->left = _delete_node(root->left, val);
    else if (val > root->val)
        root->right = _delete_node(root->right, val);
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            pNode el = root->right;
            free(root);
            return el;
        } else if (root->right == NULL) {
            pNode el = root->left;
            free(root);
            return el;
        } else {
            pNode el = root->right;

            while(el->left != NULL)
                el = el->left;

            root->val = el->val;
            root->right = _delete_node(root->right, root->val);
        }
    }

    return root;
}

void _delete_root(pNode *proot, int val) {
    pNode root = *proot;

    if (root->right == NULL) {
        if(root->left == NULL) {
            delete_tree(proot);
        } else {
            root->val = root->left->val;
            root->left = NULL;
        }
    } else {
        if (root->left == NULL) {
            root->val = root->right->val;
            root->right = NULL;
        } else {
            pNode *pel = &((*proot)->right);

            while((*pel)->left != NULL)
                pel = &((*pel)->left);

            (*proot)->val = (*pel)->val;
            (*proot)->right = _delete_node(
                (*proot)->right, (*proot)->val);
        }
    }
}

void delete_node(pNode *proot, int val) {
    pNode root = *proot;

    if (search(root, val) == NULL)
        printf("!\n");

    if (root->val == val)
        _delete_root(proot, val);
    else
        _delete_node(root, val);
}

void delete_nodes_by_interval(pNode *proot, int a, int b) {
    for (int i = a; i <= b; i++)
        delete_node(proot, i);
}

/*
42 7 23 19 5 80 74 6 n
20 31 22 24 10 15 7 1 8 9 n
*/
