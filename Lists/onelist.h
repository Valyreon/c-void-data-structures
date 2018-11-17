#ifndef ONELIST_H
#define ONELIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct onode {
    struct onode* next;
    void* info;
} ONODE;

void add_to_beginning(ONODE**, void*);
void add_to_end(ONODE**, void*);
void add(ONODE**, void*, int);
void rem(ONODE**, int);
void remove_all(ONODE**);
ONODE* search(ONODE*, int (*cmp)(void*, void*), void* key);
void print_list(ONODE*, void (*print1)(void*));
void sort_list(ONODE*, int (*cmp)(void*, void*));
void invert_list1(ONODE**);
void invert_list2(ONODE** p);
ONODE* aloc(void*);
void swap_info(ONODE*, ONODE*);
void sort_add(ONODE** plist, void* x, int (*cmp)(void*, void*));
void binaryload(ONODE** plist, int size, int n, FILE *data);
void binarysave(ONODE *plist, int size, FILE *save);
#endif