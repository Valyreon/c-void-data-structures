#include "doublelist.h"

void add(DNODE** head, int n, void* x)
{
    DNODE* point = *head;
    if (n == 0)
        add_to_beginning(head, x);
    else {
        point = access(point, n - 1);
        if (point->next == NULL)
            add_to_end(head, x);
        else {
            DNODE* new = aloc(x);
            connect(new, point->next);
            connect(point, new);
        }
    }
}

void add_to_beginning(DNODE** head, void* x)
{
    DNODE* new = aloc(x);
    if (*head != NULL) {
        (*head)->back = new;
        new->next = *head;
    }
    *head = new;
}

void add_to_end(DNODE** head, void* x)
{
    DNODE* point = *head;
    int sign = ((point == NULL) ? (0) : (1));

    if (sign)
        while (point->next != NULL)
            point = point->next;

    DNODE* new = aloc(x);

    if (!sign)
        *head = new;
    else
        connect(point, new);
}

void rem(DNODE** head, int n)
{
    if (*head != NULL) {
        DNODE* point = access(*head, n);

        if (point != NULL && point != *head && point->next != NULL && point->back != NULL) {
            connect(point->back, point->next);
            free(point->info);
            free(point);
        } else if (point != NULL && point->next == 0 && point->back == 0) {
            free(point->info);
            free(*head);
            *head = NULL;
        } else if (point == *head) {
            *head = point->next;
            free(point->info);
            free(point);
        } else if (point != NULL && point->next == NULL) {
            point->back->next = NULL;
            free(point);
        } else if (point != NULL && point->back == NULL) {
            point->next->back = NULL;
            *head = point->next;
            free(point->info);
            free(point);
        }
    }
}

void remove_all(DNODE** head)
{
    DNODE *point = *head, *save;
    while (point != NULL) {
        save = point->next;
        free(point->info);
        free(point);
        point = save;
    }
    *head = NULL;
}

void sort(DNODE* head, int (*p)(void*, void*))
{
    for (DNODE* i = head; i != NULL; i = i->next) {
        DNODE* best = i;
        for (DNODE* j = i->next; j != NULL; j = j->next)
            if ((*p)(best->info, j->info))
                best = j;

        if (best != i)
            swap_info(best, i);
    }
}

DNODE* access(DNODE* head, int n)
{
    for (int i = 0; i < n && head != NULL; i++)
        head = head->next;
    if (head == NULL)
        return NULL;
    else
        return head;
}

DNODE* aloc(void* x)
{
    DNODE* new = calloc(1, sizeof(DNODE));
    new->info = x;
    return new;
}

void swap_info(DNODE* a, DNODE* b)
{
    void* save = a->info;
    a->info = b->info;
    b->info = save;
}

void print_list(DNODE* head, void (*pr1)(void*))
{
    if (head != NULL)
        printf("\nList: ");
    else
        printf("\nList is empty.");
    while (head != NULL) {
        (*pr1)(head->info);
        head = head->next;
    }
}

void sort_add(DNODE** plist, void* x, int (*cmp)(void*, void*))
{
    DNODE* point = *plist;
    DNODE* new = aloc(x);

    if (point == NULL)
        *plist = new;
    else {
        while (point->next != NULL && (*cmp)(x, point->next->info))
            point = point->next;

        if (point == *plist) {
            connect(new, *plist);
            *plist = new;
        } else if (point->next != NULL) {
            connect(new, point->next);
            connect(point, new);
        } else
            connect(point, new);
    }
}

void connect(DNODE* first, DNODE* second) 
{
    first->next = second;
    second->back=first;
}