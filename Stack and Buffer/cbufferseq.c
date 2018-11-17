#include "cbufferseq.h"

RED* start_cBuffer(int n)
{
    RED* new = calloc(1, sizeof(RED));
    new->n = n;
    new->front = -1;
    new->array = calloc(n, sizeof(void*));
    return new;
}

int c_buffer_add(RED* line, void* x)
{
    if ((line->rear) % line->n == line->front)
        return 0;
    if (line->front == -1)
        line->front = 0;
    line->array[line->rear] = x;
    line->rear = (line->rear + 1) % line->n;
    return 1;
}

void c_buffer_add_OW(RED* line, void* x)
{
    if (line->front == -1)
        line->front = 0;
    if ((line->front % line->n) == ((line->rear + 1) % line->n))
        line->front = (line->front + 1) % line->n;
    line->array[line->rear] = x;
    line->rear = (line->rear + 1) % line->n;
}

void c_buffer_take(void** info, RED* line)
{
    if (line->rear == line->front)
        *info = NULL;
    *info = line->array[line->front % line->n];
    line->array[line->front % line->n] = NULL;
    line->front = (line->front + 1) % line->n;
    if ((line->rear) % line->n == line->front)
        line->front = -1;
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
void SCB_binaryload(RED* buf, int size, int n, FILE* save)
{
    void* help = calloc(1, size);
    char sign = 1;
    for (int i = 0; i < n && fread(help, size, 1, save) && sign; i++) {
        sign = c_buffer_add(buf, help);
        help = calloc(1, size);
    }
}

void SCB_binarysave(RED* buf, int size, FILE* save)
{
    for (int i = buf->front; i != buf->rear; i = ((i + 1) % buf->n))
        fwrite(buf->array[i], size, 1, save);
}