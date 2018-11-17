#ifndef SEQSTEK_H
#define SEQSTEK_H
#include <stdio.h>
#include <stdlib.h>

typedef struct st {
    void** array;
    int tos, n;
} STEK; // sequential stack structure

int push_seq(STEK* s, void* x);
void* pop_seq(STEK* s);
STEK* newSeqSTEK(int n); // starts seq stek
void delSeqSTEK(STEK** s); //deletes seq stek
void SS_binaryload(STEK** s, int size, int n, FILE* data);
void SS_binarysave(STEK* s, int size, FILE* save);

#endif