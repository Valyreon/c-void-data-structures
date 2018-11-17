#include "tree.h"

STEKNODE* aloc_NODE(TNODE* x) // for creating a node for stack implemented with linked list
{
    STEKNODE* r = calloc(1, sizeof(STEKNODE));
    r->info = x;
    return r;
}

void push_node(STEK* x, TNODE* info) // for pushing a node on the stack
{
    STEKNODE* new = aloc_NODE(info);
    new->next = x->tos;
    x->tos = new;
    x->n++;
}

TNODE* pop_node(STEK* x) // for taking a node from top of the stack
{
    TNODE* save;
    STEKNODE* nextsave;
    if (x->n != 0) {
        save = x->tos->info;
        nextsave = x->tos->next;
        free(x->tos);
    } else {
        save = NULL;
        nextsave = NULL;
    }
    x->tos = nextsave;
    if (x->n > 0)
        x->n--;
    return save;
}

TNODE* aloc_TNODE(void* info)
{
    TNODE* new = calloc(1, sizeof(TNODE));
    new->info = info;
    return new;
}

void add_left(TNODE* parent, void* info)
{
    TNODE* new = aloc_TNODE(info);
    parent->left = new;
}

void add_right(TNODE* parent, void* info)
{
    TNODE* new = aloc_TNODE(info);
    parent->right = new;
}

/* Function cmp has to return -1 if info needs to go left, 0 if they are the same, otherwise 1. You need to send 
it a pointer to root node and info which needs to be added. */
void rec_add(TNODE** root, void* info, int (*cmp)(void*, void*))
{
    if (*root == NULL) {
        TNODE* new = aloc_TNODE(info);
        *root = new;
    } else {
        if ((*cmp)((*root)->info, info) == 1)
            rec_add(&((*root)->right), info, cmp);
        else
            rec_add(&((*root)->left), info, cmp);
    }
}

void del_tree(TNODE** root)
{
    if (*root != NULL) {
        del_tree(&((*root)->left));
        del_tree(&((*root)->right));
        free((*root)->info);
        free(*root);
        *root = NULL;
    }
}

void Rpreorder_print(TNODE* root, void (*print_one)(void*))
{
    if (root != NULL) {
        (*print_one)(root->info);
        Rpreorder_print(root->left, print_one);
        Rpreorder_print(root->right, print_one);
    }
}

void Rinorder_print(TNODE* root, void (*print_one)(void*))
{
    if (root != NULL) {
        Rinorder_print(root->left, print_one);
        (*print_one)(root->info);
        Rinorder_print(root->right, print_one);
    }
}

void Rpostorder_print(TNODE* root, void (*print_one)(void*))
{
    if (root != NULL) {
        Rpostorder_print(root->left, print_one);
        Rpostorder_print(root->right, print_one);
        (*print_one)(root->info);
    }
}

int count_tnodes(TNODE* root)
{
    if (root == NULL)
        return 0;
    else
        return 1 + count_tnodes(root->left) + count_tnodes(root->right);
}

int count_leaves(TNODE* root)
{
    if (root == NULL)
        return 0;
    else if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return count_leaves(root->left) + count_leaves(root->right);
}

int count_depth(TNODE* root)
{
    if (root != NULL)
        return 1 + MAX(count_depth(root->left), count_depth(root->right));
    else
        return 0;
}

/* Loads the tree from file. */
void tree_dataload(TNODE** root, int size, int n, int (*p)(void*, void*), FILE* data)
{
    void* help = malloc(size);
    for (int i = 0; i < n && fread(help, size, 1, data); i++) {
        rec_add(root, help, p);
        help = malloc(size);
    }
    free(help);
}

/* Saves the tree to file. */
void tree_datasave(TNODE* root, int size, char* order, FILE* data)
{
    if (root != NULL) {
        if (!strcmp(order, "pre")) {
            fwrite(root->info, size, 1, data);
            tree_datasave(root->left, size, order, data);
            tree_datasave(root->right, size, order, data);
        } else if (!strcmp(order, "post")) {
            tree_datasave(root->left, size, order, data);
            tree_datasave(root->right, size, order, data);
            fwrite(root->info, size, 1, data);
        } else {
            tree_datasave(root->left, size, order, data);
            fwrite(root->info, size, 1, data);
            tree_datasave(root->right, size, order, data);
        }
    }
}

/* Function cmp needs to return 0 if key and data are the same, -1 if we need to go left in the tree, 1 if right */
TNODE* search(TNODE* root, int (*cmp)(void*, void*), void* key)
{
    if (root == NULL)
        return NULL;
    else if ((*cmp)(root->info, key) == 0)
        return root;
    else if ((*cmp)(root->info, key) == -1)
        return search(root->left, cmp, key);
    else
        return search(root->right, cmp, key);
}

TNODE* most_left(TNODE* root)
{
    if (root != NULL) {
        while (root->left != NULL)
            root = root->left;
        return root;
    } else
        return NULL;
}

TNODE* most_right(TNODE* root)
{
    if (root != NULL) {
        while (root->right != NULL)
            root = root->right;
        return root;
    } else
        return NULL;
}

TNODE* search_all(TNODE* root, int (*cmp)(void*, void*), void* key)
{
    TNODE *left = NULL, *right = NULL;
    if (root == NULL)
        return NULL;
    if ((*cmp)(root->info, key))
        return root;
    else {
        left = search_all(root->left, cmp, key);
        right = search_all(root->right, cmp, key);
        if (left == NULL && right == NULL)
            return NULL;
        else
            return ((left == NULL) ? (right) : (left));
    }
}

/* print1 is the pointer to function which prints the info in the nodes */
void in_order_iterative_print(TNODE* root, void (*print1)(void*))
{
    STEK x, visited;
    visited.tos = x.tos = NULL;
    visited.n = x.n = 0;
    push_node(&x, root);
    while (x.n != 0) {
        TNODE* top = x.tos->info;
        if (top != NULL) {
            if (!check(&visited, top)) {
                push_node(&x, top->left);
            } else {
                (*print1)(top->info);
                pop_node(&x);
                push_node(&x, top->right);
            }
        } else {
            pop_node(&x);
            if(x.n!=0)
                push_node(&visited, x.tos->info);
        }
    }
    STEKNODE* i = visited.tos;
    while (i != NULL) {
        STEKNODE* save = i->next;
        free(i);
        i = save;
    }
}

int check(STEK* visited, TNODE* x)
{
    for (STEKNODE* i = visited->tos; i != NULL; i = i->next)
        if (i->info == x)
            return 1;
    return 0;
}

void pre_order_iterative_print(TNODE* root, void (*print1)(void*))
{
    if(root==NULL) return;
    STEK x;
    x.tos = NULL;
    x.n = 0;
    TNODE *sljedeci;
    push_node(&x, root);
    while(x.tos) {
        sljedeci = pop_node(&x);
        while(sljedeci) {
            (*print1)(sljedeci->info);
            if(sljedeci->right)
                push_node(&x, sljedeci->right);
            sljedeci= sljedeci->left;
        }
    }
}

void** inorder_array(TNODE *root, int *n)
{
    STEK x, visited;
    *n=0;
    void **niz=calloc(1,sizeof(void*));
    visited.tos = x.tos = NULL;
    visited.n = x.n = 0;
    push_node(&x, root);
    while (x.n != 0) {
        TNODE* top = x.tos->info;
        if (top != NULL) {
            if (!check(&visited, top)) {
                push_node(&x, top->left);
            } else {
                if(*n!=0)
                    niz=realloc(niz, ((*n)+1)*sizeof(void*));
                niz[(*n)++]=top->info;
                pop_node(&x);
                push_node(&x, top->right);
            }
        } else {
            pop_node(&x);
            if(x.n!=0)
                push_node(&visited, x.tos->info);
        }
    }
    STEKNODE* i = visited.tos;
    while (i != NULL) {
        STEKNODE* save = i->next;
        free(i);
        i = save;
    }
    return niz;
}
