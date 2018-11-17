#include "onelist.h"

ONODE* aloc(void* x)
{
    ONODE* new = calloc(1, sizeof(ONODE));
    new->info = x;
    return new;
}

void swap_info(ONODE* a, ONODE* b)
{
    void* save = a->info;
    a->info = b->info;
    b->info = save;
}

void add_to_beginning(ONODE** p, void* x)
{
    ONODE* new = aloc(x);
    if (*p != NULL)
        new->next = *p;
    *p = new;
}

void add_to_end(ONODE** p, void* x)
{
    ONODE* point = *p;
    ONODE* new = aloc(x);
    if (point != NULL) {
        while (point->next != NULL)
            point = point->next;
        point->next = new;
    } else
        *p = new;
}

void add(ONODE** p, void* x, int n)
{
    if (n == 0)
        add_to_beginning(p, x);
    else {
        ONODE* point = *p;
        int i;

        for (i = 0; i < n - 1 && point->next != NULL; i++)
            point = point->next;

        if (point->next == NULL && i == (n - 1))
            add_to_end(&point, x);
        else if (i == (n - 1)) {
            ONODE* new = aloc(x);
            ONODE* save = point->next;
            point->next = new;
            new->next = save;
        } else
            printf("That space is not available.\n");
    }
}

void rem(ONODE** p, int n)
{
    if (*p == NULL)
        printf("Greska.\n");
    else if ((*p)->next == 0 && n == 0) {
        free((*p)->info);
        free(*p);
        *p = NULL;
    } else if (n == 0) {
        ONODE* save = (*p)->next;
        free((*p)->info);
        free(*p);
        *p = save;
    } else {
        ONODE* point = *p;
        for (int i = 0; i < n - 1 && point != NULL; i++)
            point = point->next;

        if (point == NULL || point->next == NULL)
            printf("That element does not exist.\n");
        else {
            ONODE* save = point->next->next;
            free(point->next->info);
            free(point->next);
            point->next = save;
        }
    }
}

void remove_all(ONODE** p)
{
    ONODE* point = *p;
    while (point != NULL) {
        ONODE* save = point->next;
        if(point->info!=NULL)
            free(point->info);
        free(point);
        point = save;
    }
    *p = NULL;
}

//Funkcija cmp treba da vraca 1 ako se podudaraju
ONODE* search(ONODE* p, int (*cmp)(void*, void*), void* key)
{
    while ((*cmp)(p->info, key) == 0 && p)
        p = p->next;
    if (p)
        return p;
    else
        return NULL;
}

void print_list(ONODE* p, void (*print1)(void*))
{
    for (int i = 1; p != NULL; i++) {
        (*print1)(p->info);
        p = p->next;
    }
}

void sort_list(ONODE* p, int (*cmp)(void*, void*))
{
    for (ONODE* i = p; i != NULL; i = i->next) {
        ONODE* best = i;
        for (ONODE* j = i->next; j != NULL; j = j->next)
            if ((*cmp)(best->info, j->info))
                best = j;

        if (best != i)
            swap_info(best, i);
    }
}

void invert_list1(ONODE** p)
{
    ONODE** indexlist = calloc(10, sizeof(ONODE*));
    ONODE* point = *p;
    int lim = 10;
    int n = 0;

    while (point != NULL) {
        indexlist[n++] = point;
        if (n > lim - 2)
            indexlist = realloc(indexlist, (lim *= 2) * sizeof(ONODE*));
        point = point->next;
    }

    point = *p;

    for (int i = 0; i < n; i++) {
        ONODE* save = point->next;
        if (i == 0)
            point->next = NULL;
        else
            point->next = indexlist[i - 1];
        point = save;
    }

    *p = indexlist[n - 1];
    free(indexlist);
}

void invert_list2(ONODE** p)
{
    ONODE *point = *p, *r, *s, *b;
    if (point->next != NULL && point != NULL) {
        s = point->next;
        point->next = NULL;
        while (s != NULL) {
            r = s->next;
            s->next = point;
            b = s;
            s = r;
            point = b;
        }
        *p = point;
    }
}

void sort_add(ONODE** plist, void* x, int (*cmp)(void*, void*))
{
    ONODE* point = *plist;
    ONODE* new = aloc(x);

    if (point == NULL)
        *plist = new;
    else {
        while (point->next != NULL && (*cmp)(x, point->next->info))
            point = point->next;

        if (point == *plist) {
            new->next = *plist;
            *plist = new;
        } else if (point->next != NULL) {
            new->next = point->next;
            point->next = new;
        } else
            point->next = new;
    }
}

void binaryload(ONODE** plist, int size, int n, FILE *data)
{
    void *help=malloc(size);
    for(int i=0; i<n && fread(help,size,1,data);i++){
        add_to_end(plist, help);
        help=malloc(size);
    }
    free(help);
}

void binarysave(ONODE *plist, int size, FILE *save)
{
    while(plist!=NULL && fwrite(plist->info,size,1,save))
        plist=plist->next;
}