#include "seqstek.h"

int push_seq(STEK* s, void* x)
{
    if (s->tos >= s->n)
        return 0;
    (s->array)[++s->tos] = x;
    return 1;
}

void* pop_seq(STEK* s)
{
    if (s->tos == -1)
        return NULL;
    return (s->array)[s->tos--];
}

STEK* newSeqSTEK(int n)
{
    STEK* new = calloc(1, sizeof(STEK));
    new->tos = -1;
    new->n = n;
    new->array = calloc(n, sizeof(void*));
    return new;
}

void delSeqSTEK(STEK** s)
{
    free((*s)->array);
    free(s);
    *s = NULL;
}

void SS_binaryload(STEK** s, int size, int n, FILE* data)
{
    rewind(data);
    void* help = calloc(1, size);
    for (int i = 0; i < n && fread(help, size, 1, data); i++) {
        push_seq(*s, help);
        help = calloc(1, size);
    }
}

void SS_binarysave(STEK* s, int size, FILE* save)
{
    rewind(save);
    for (int i = 0; i < s->n; i++)
        fwrite(s->array[i], size, 1, save);
}