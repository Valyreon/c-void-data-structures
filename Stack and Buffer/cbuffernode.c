#include "cbuffernode.h"

NODE* aloc_NODE(void* x)
{
    NODE* r = calloc(1, sizeof(NODE));
    r->info = x;
    return r;
}

void form_LCB(LCB* line, int n)
{
    line->front = aloc_NODE(NULL);
    NODE* p = line->front;
    for (int i = 1; i < n; i++) {
        p->next = aloc_NODE(NULL);
        p = p->next;
    }
    p->next = line->front;
    line->rear = line->front;
    line->n = 0;
    line->max = n;
}

int LCB_add(LCB* line, void* x)
{
    if (line->n >= line->max)
        return 0;
    line->rear->info = x;
    line->rear = line->rear->next;
    line->n += 1;
    return 1;
}

void LCB_add_OW(LCB* line, void* x)
{
    if (line->n == line->max)
        line->front = line->front->next, line->n -= 1;
    line->rear->info = x;
    line->rear = line->rear->next;
    line->n += 1;
}

void* LCB_take(LCB* line)
{
    if (line->n == 0)
        return NULL;
    void* save = line->front->info;
    line->front->info = NULL;
    line->front = line->front->next;
    line->n--;
    return save;
}

void LCB_del(LCB* line)
{
    for (int i = 0; i < line->max; i++) {
        NODE* save = line->front->next;
        if (line->front->info != NULL)
            free(line->front->info);
        free(line->front);
        line->front = save;
    }
    line->front = line->rear = NULL;
}

void LCB_binaryload(LCB* line, int size, int n, FILE* save)
{
    void* help = calloc(1, size);
    char sign = 1;
    for (int i = 0; i < n && sign && fread(help, size, 1, save); i++) {
        sign = LCB_add(line, help);
        help = calloc(1, size);
    }
}

void LCB_binarysave(LCB* line, int size, FILE* save)
{
    int i = 0;
    for (NODE *point = line->front; i < line->n; point = point->next, i++)
        fwrite(point->info, size, 1, save);
}