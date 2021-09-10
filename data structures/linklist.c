# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    char data;
    struct node *next;
}Node, *LinkList;

void ReverseList(LinkList L)
{
    Node *p = NULL, *r = L -> next, *t;
    while (r != NULL)
    {
        t = r -> next;
        L -> next = r;
        r -> next = p;
        p = r;
        r = t;
    }
}

void CreateLinkList(LinkList L)
{
    Node *r = L, *s;
    char ch;
    while ((ch = getchar()) != '$')
    {
        s = (Node*)malloc(sizeof(Node));
        s -> data = ch;
        r -> next = s;
        r = s;
        getchar();
    }
    r -> next = NULL;
}

void PrintLinkList(LinkList L)
{
    Node *p;
    for (p = L -> next; p != NULL; p = p -> next)
        printf("%c", p -> data);
}

void changelist(LinkList L)
{
    if (L -> next == NULL)
        return;

    Node *first = L -> next, *cur, *pre;
    pre = first;
    cur = pre -> next;
    while (cur != NULL)
        if (cur -> data < first -> data)
        {
            pre -> next = cur -> next;
            cur -> next = L -> next;
            L -> next = cur;
            cur = pre -> next;
        }
        else
        {
             pre = cur;
             cur = cur -> next;
        }
    pre -> next = NULL;
}

LinkList AddList_reverse(LinkList LA, LinkList LB)
{
    LinkList LC = LA;
    Node *p = LA -> next, *q = LB -> next, *r, *t;
    LC -> next = NULL;
    r = LC -> next;
    while (p && q)
    {
        if (p -> data < q -> data)
        {
            t = p -> next;
            LC -> next = p;
            p -> next = r;
            r = p;
            p = t;
        }
        else
        {
            t = q -> next;
            LC -> next = q;
            q -> next = r;
            r = q;
            q = t;
        }
    }

    if (p)
        while (q)
        {
            t = q -> next;
            LC -> next = q;
            q -> next = r;
            r = q;
            q = t;
        }
    else
        while(p)
        {
             t = p -> next;
            LC -> next = p;
            p -> next = r;
            r = p;
            p = t;
        }
        
    return LC;
}

int loop(LinkList L)
{
    Node *quick, *slow;
    quick = slow = L -> next;
    int flag = 0, r = 1;

    if (L -> next -> next == NULL)
        return 0;
    
    while (quick)
    {
        quick = quick -> next;
        if (quick)
            quick = quick -> next;
        slow = slow -> next;
        if (slow == quick)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        return 0;

    Node *t = quick;
    quick = quick -> next -> next;
    slow = slow -> next;
    while (quick != slow)
    {
        r++;
        quick = quick -> next -> next;
        slow = slow -> next;
    }
    quick = L -> next;
    slow = t;
    while (quick != slow)
    {
        quick = quick -> next;
        slow = slow -> next;
    }
    printf("%d %c", r, quick -> data);
    return 1;
    
}

void transit_1(LinkList L)
{
    if (L -> next == NULL)
        return;
    Node *p = L -> next -> next, *left = L -> next, *right = left, *t;
    int i = 2;
    while (p)
        if (i % 2 == 0)
        {
            t = p -> next;
            p -> next = left;
            left = p;
            p = t;
            i++;
        }
        else
        {
            right -> next = p;
            right = p;
            p = p -> next;
            i++;
        }
    L -> next = left;
    right -> next = NULL;
}

int main(void)
{
    LinkList L;
    L = (Node*)malloc(sizeof(Node));
    CreateLinkList(L);
    transit_1(L);
    PrintLinkList(L);
}