# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
}Node, *LinkList;

void CreateCLinkList(LinkList CL)
{
    Node *r = CL, *s;
    char ch;
    while ((ch = getchar()) != '$')
    {
        s = (Node*)malloc(sizeof(Node));
        s -> data = ch;
        r -> next = s;
        r = s;
    }
    r -> next = CL;
}