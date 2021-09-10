# include <stdio.h>
# include <stdlib.h>

typedef struct DNode
{
    int data;
    struct DNode *prior;
    struct DNode *next;
}DNode, *DoubleList;

int DlinkIns(DoubleList L, int i, int e)
{
    int k = 1;
    DNode *s, *p;
    for (p = L; k < i && p != NULL; p = p -> next, i++)
        ;

    if (p == NULL)
    {
        printf("Iligal position!");
        return 0;
    }

    if (p -> next == NULL)
    {
        s = (DNode*)malloc(sizeof(DNode));
        p -> next = s;
        s -> prior = p;
        s -> next = NULL;
        return 1;    
    }

    s = (DNode*)malloc(sizeof(DNode));
    s -> data = e;
    s -> next = p -> next;
    s -> prior = p;
    p -> next -> prior = s;
    p -> next = s;
    return 1;
}

int DlinkDel(DoubleList L, int i, int *e)
{
    int k = 1;
    DNode *s, *p;
    for (p = L -> next; k < i && p -> next != NULL; p = p -> next, i++)
        ;

    if (p -> next == NULL)
    {
        printf("Iligal position!");
        return 0;
    }

    p -> prior -> next = p -> next;
    p -> next -> prior = p -> prior;
    *e = p -> data;
    free(p);
    return 1;
}
