# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}Node, *LinkList;

void BinAdd(LinkList L)
{
    Node *p = L -> next, *r = NULL, *s;
    
    while (p)
    {
        if (p -> data == 0)
            r = p;
        p = p -> next;
    }

    if (r == NULL)
    {
        s = (Node*)malloc(sizeof(Node));
        s -> data = 1;
        p = L -> next;
        L -> next = s;
        s -> next = p;
        while (p)
        {
            p -> data = 0;
            p = p -> next;
        }
        return;
    }

    r -> data = 1;
    p = r -> next;
    while (p)
    {
        p -> data = 0;
        p = p -> next;
    }    
}