# include <stdio.h>
# include <stdlib.h>

int i = 1;

typedef struct node
{
    int code;
    int sequence;
    int flag;
    struct node *next;
}Node, *CLinkList;

void CreateCLinkList(CLinkList L, int n)
{
    Node *r = L, *s;
    int i, code;
    for (i = 1; i <= n; i++)
    {
        s = (Node*)malloc(sizeof(Node));
        scanf("%d", &code);
        s -> flag = 0;
        s -> code = code;
        r -> next = s;
        r = s;
    }
    r -> next = L -> next;
}

void PrintCLinkList(CLinkList L)
{
    Node *p;
    if (L -> next == NULL)
        return;
    for (p = L -> next; p -> next != L -> next; p = p -> next)
        printf("%d ", p -> sequence);
    printf("%d ", p -> sequence);
}

Node *FindNode(Node *begin, int *m)
{
    int j = 1;
    while (j <= *m)
    {        
        begin = begin -> next;
        if (begin -> flag == 0)
            j++;
    }
    *m = begin -> code;
    begin -> flag = 1;
    begin -> sequence = i++;

    return begin;
}

int main(void)
{
    int m, n;
    n = 7;
    CLinkList L;
    L = (Node*)malloc(sizeof(Node));
    CreateCLinkList(L, n);
    Node *p = L;
    scanf("%d", &m);
    while (i <= n)
        p = FindNode(p, &m);
    PrintCLinkList(L);

    return 0;
}