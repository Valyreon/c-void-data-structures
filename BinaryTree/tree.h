#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) ((a>b)?(a):(b))

typedef struct trnode {
	struct trnode *left, *right;
	void *info;
} TNODE;

typedef struct node{
	struct node *next;
	TNODE *info;
} STEKNODE;

typedef struct {
	STEKNODE *tos;
	int n;
} STEK;

STEKNODE* aloc_NODE(TNODE* x);
void push_node(STEK *x, TNODE* info);
TNODE* pop_node(STEK* x);
TNODE *aloc_TNODE(void *info);

void add_left(TNODE *parent, void *info);
void add_right(TNODE *parent, void *info);
void rec_add(TNODE **root, void *info, int (*cmp)(void*,void*));
void del_tree(TNODE **root);

void Rpreorder_print(TNODE *root, void (*print_one)(void *));
void Rinorder_print(TNODE *root, void (*print_one)(void *));
void Rpostorder_print(TNODE *root, void (*print_one)(void *));
void in_order_iterative_print(TNODE *root, void (*print1)(void*));
void pre_order_iterative_print(TNODE* root, void (*print1)(void*));

int count_leaves(TNODE *root);
int count_depth(TNODE *root);
int count_tnodes(TNODE *root);
int count_right_subtrees(TNODE *root);
int count_left_subtrees(TNODE *root);
void tree_dataload(TNODE** root, int size, int n, int (*p)(void*, void*), FILE* data);
void tree_datasave(TNODE *root, int size,char *order, FILE *data);

TNODE* most_left(TNODE* root);
TNODE* most_right(TNODE* root);
TNODE* search(TNODE *root, int (*cmp)(void*,void*), void *key);
TNODE* search_all(TNODE *root, int (*cmp)(void*,void*), void *key);
int check(STEK *visited, TNODE *x);

void** inorder_array(TNODE *root, int *n);
#endif
