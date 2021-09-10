# include <stdio.h>
# include <stdlib.h>

typedef struct Polynode
{
    int coef;         //系数
    int exp;          //指数
    struct Polynode *next;
}PolyNode, *PolyList;

PolyList PolyCreat()
{
    PolyNode *s, *head, *r;
    int c, e;
    head = (PolyList)malloc(sizeof(PolyNode));
    r = head;
    scanf("%d%d", &c, &e);
    while(c != 0)
    {
        s = (PolyNode*)malloc(sizeof(PolyNode));
        s -> coef = c;
        s -> exp = e;
        r -> next = s;
        r = s;
        scanf("%d%d", &c, &e);
    }
    r -> next = NULL;
    return head;
}

void PolyAdd(PolyList polya, PolyList polyb)
{
    PolyNode *a, *b, *tail, *temp;
    int sum;
    a = polya -> next, b = polyb -> next;
    tail = polya;
    while (a -> next != NULL && b -> next != NULL)
    {
        if (a -> exp > b -> exp)
        {
            tail -> next = b;
            tail = b;
            b = b -> next;
        }
        if (a -> exp < b -> exp)
        {
            tail -> next = a;
            tail = a;
            a = a -> next;
        }
        if (a -> exp == b -> exp)
            if ((sum = a -> coef + b -> coef) == 0)
            {
                temp = a;
                a = a -> next;
                free(temp);
                temp = b;
                b = b -> next;
                free(temp);
            }
            else
            {
                a -> coef = sum;
                tail -> next = a;
                tail = a;
                a = a -> next;
                temp = b;
                b = b -> next;
                free(temp);
            }
            
    }
    if (a == NULL)
        tail -> next = b;
    else
        tail -> next = a;

}
