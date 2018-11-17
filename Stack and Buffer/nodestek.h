#ifndef NODESTEK_H
#define NODESTEK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
    void* info;
    struct snode* next;
} NODE;

NODE* aloc_NODE(void* x); // for creating one node for stack
void push_node(NODE** tos, void* info); 
void* pop_node(NODE** tos);
void del_nodes(NODE **tos);// deletes all nodes from linked stack

void LS_binaryload(NODE** tos, int size, int n, FILE* data);
void LS_binarysave(NODE* tos, int size, FILE* file);

#endif