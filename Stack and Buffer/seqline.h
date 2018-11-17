#ifndef SEQLINE_H
#define SEQLINE_H
#include <stdio.h>
#include <stdlib.h>

/* Structure for sequential and circular order, different functions are used */
typedef struct sline {
    void** array;
    int front, rear, n;
} RED;

RED* start_sLine(int n); // for initializing an sequential order
int sline_add(RED* line, void* x); // for adding into sequential order
void* sline_take(RED* line); // for taking from sequential order
void del_line(RED **line); // for deleting sequential or circular order
void SR_binaryload(RED** line, int size, int n, FILE* data); // for loading data from file into sequential order
void SR_binarysave(RED* line, int size, FILE* save);// for saving data in sequential order into a file

#endif