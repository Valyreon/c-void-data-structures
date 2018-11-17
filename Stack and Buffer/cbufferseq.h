#ifndef CBUFFERSEQ_H
#define CBUFFERSEQ_H
#include <stdio.h>
#include <stdlib.h>

typedef struct sline {
    void** array;
    int front, rear, n;
} RED;

RED* start_cBuffer(int n); // for initializing the sequential buffer
int c_buffer_add(RED* line, void* x); // for adding into sb
void c_buffer_add_OW(RED* line, void* x); // for adding into sb with overwrite
void c_buffer_take(void **info,RED* line); // for taking from sb
void del_line(RED **line);
void SCB_binaryload(RED* buf, int size, int n, FILE* save);
void SCB_binarysave(RED* buf, int size, FILE* save);

#endif