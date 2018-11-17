#ifndef CBUFFERNODE_H
#define CBUFFERNODE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct snode {
    void* info;
    struct snode* next;
} NODE;

typedef struct cc{
    NODE *front, *rear;
    int max,n;
}LCB; // structure for circular linked buffer

NODE* aloc_NODE(void* x);
void form_LCB(LCB *,int n); // forms circular linked buffer from sequential circular buffer
int LCB_add(LCB *,void *);// adds into lcb
void LCB_add_OW(LCB *, void*);// adds into lcb with overwrite
void* LCB_take(LCB *);// takes from end of the buffer
void LCB_del(LCB*);// deletes the buffer
void LCB_binaryload(LCB* line, int size,int n, FILE* save);
void LCB_binarysave(LCB *line, int size, FILE *save);

#endif