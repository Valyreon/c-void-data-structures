#include "nodestek.h"

NODE* aloc_NODE(void* x)
{
    NODE* r = calloc(1, sizeof(NODE));
    r->info = x;
    return r;
}

void push_node(NODE** tos, void* info)
{
    NODE* new = aloc_NODE(info);
    new->next = *tos;
    *tos = new;
}

void* pop_node(NODE** tos)
{
    void* save;
    NODE* nextsave;
    if (*tos != NULL) {
        save = (*tos)->info;
        nextsave = (*tos)->next;
        free(*tos);
    } else {
        save = NULL;
        nextsave = NULL;
    }
    *tos = nextsave;
    return save;
}
void del_nodes(NODE** tos)
{
    NODE* point = *tos;
    while (point != NULL) {
        NODE* save = point->next;
        free(point->info);
        free(point);
        point = save;
    }
    *tos = NULL;
}
void LS_binaryload(NODE** tos, int size, int n, FILE* data)
{
    rewind(data);
    void* help = calloc(1, size);
    for (int i = 0; fread(help, size, 1, data) && i < n; i++) {
        push_node(tos, help);
        help = calloc(1, size);
    }
}

void LS_binarysave(NODE* tos, int size, FILE* file)
{
    NODE* point = tos;
    while (point != NULL) {
        fwrite(point->info, size, 1, file);
        point = point->next;
    }
}