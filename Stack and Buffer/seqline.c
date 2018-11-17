#include "seqline.h"

RED* start_sLine(int n)
{
    RED* new = calloc(1, sizeof(RED));
    new->rear = 0;
    new->front = -1;
    new->n = n;
    new->array = calloc(n, sizeof(void*));
    return new;
}

int sline_add(RED* line, void* x)
{
    if (line->rear >= line->n)
        return 0;
    (line->array)[line->rear++] = x;
    if (line->front < 0)
        line->front = 0;
    return 1;
}

void* sline_take(RED* line)
{
    if (line->front < 0 || line->front == line->rear)
        return NULL;
    void* save = (line->array)[line->front];
    (line->array)[line->front] = NULL;
    line->front += 1;
    return save;
}

void del_line(RED** line)
{
    for (int i = 0; i < (*line)->n; i++)
        if (((*line)->array)[i] != NULL)
            free(((*line)->array)[i]);
    free((*line)->array);
    free(*line);
    *line = NULL;
}

void SR_binaryload(RED** line, int size, int n, FILE* data)
{
    rewind(data);
    void* help = calloc(1, size);
    for (int i = 0; i < n && fread(help, size, 1, data); i++) {
        sline_add(*line, help);
        help = calloc(1, size);
    }
}

void SR_binarysave(RED* line, int size, FILE* save) 
{
    for (int i = line->front; i < line->rear; i++)
        fwrite(line->array[i], size, 1, save);
}