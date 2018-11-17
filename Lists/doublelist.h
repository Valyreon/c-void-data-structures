#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next, *back;
    void* info;
} DNODE;

void add(DNODE** head, int n, void* x);
void add_to_beginning(DNODE** head, void* x);
void add_to_end(DNODE** head, void* x);
void rem(DNODE** head, int n);
void remove_all(DNODE** head);
void sort(DNODE* head, int (*p)(void*, void*));
void sort_add(DNODE**, void*, int (*)(void*, void*));
DNODE* access(DNODE* head, int n);
DNODE* aloc(void*);
void swap_info(DNODE* a, DNODE* b);
void print_list(DNODE* head, void (*pr1)(void*));
void connect(DNODE* first, DNODE* second);

#endif