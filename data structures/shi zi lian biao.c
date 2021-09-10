# include <stdio.h>
# include <stdlib.h>

typedef int ElemType;

typedef struct OLNode
{
    int row, col;
    ElemType value;
    struct OLNode *right, *down;
}OLNode, *OLink;

typedef struct
{
    OLink *rowhead, *colhead;
    int rows, cols, nums;
}CrossList, *PCrossList;

int init_cross_list(PCrossList L, const ElemType* A, int m, int n)
{
    int x = 0, row, col;
    OLNode *s, *r;
    L -> rows = m;
    L -> cols = n;

    L -> rowhead = (OLink *)malloc(m * sizeof(OLink));
    L -> colhead = (OLink *)malloc(n * sizeof(OLink));

    if (L -> rowhead == NULL)
    {
        printf("Overflow");
        exit(0);
    }
    if (L -> colhead == NULL)
    {
        printf("Overflow");
        exit(0);
    }
    
    for (int i = 0; i < m; i++)
        L -> rowhead[i] = NULL;
    for (int i = 0; i < n; i++)
        L -> colhead[i] = NULL;
        
    for (const ElemType *p = A; p < A + m * n; p++)
        if (*p != 0)
        {
            row = (p - A) / n;
            col = (p - A) % n;
            s = (OLNode *)malloc(sizeof(OLNode));
            s -> value = *p;
            s -> row = row;
            s -> col = col;

            if (L -> rowhead[row] == NULL)
            {
                L -> rowhead[row] = s;
                s -> right = NULL;
            }
            else
            {
                for (r = L -> rowhead[row]; r -> right != NULL && r -> right -> col < col; r = r -> right)
                    ;
                s -> right = r -> right;
                r -> right = s;
            }

            if (L -> colhead[col] == NULL)
            {
                L -> colhead[col] = s;
                s -> down = NULL;
            }
            else
            {
                for (r = L -> colhead[col]; r -> down != NULL && r -> down -> row < row; r = r -> down)
                    ;
                s -> down = r -> down;
                r -> down = s;
            }

            x++;
        }

    L -> nums = x;
    return x;
}

int del_cross_list(PCrossList L, ElemType k)
{
    int n = 0;
    OLNode *p, *rpre, *cpre, *q;
    for (int i = 0; i < L -> cols; i++)
    {
        cpre = NULL;
        p = L -> colhead[i];
        while (p != NULL)
            if (p -> value == k)
            {
                rpre = NULL;
                for (q = L -> rowhead[p -> row]; q != p; rpre = q, q = q -> right)
                    ;

                if (rpre == NULL)
                    L -> rowhead[p -> row] = p -> right;
                else
                    rpre -> right = p -> right;

                if (cpre == NULL)
                {
                    L -> colhead[i] = p -> down;
                    p = p -> down;
                    free(q);
                }
                else
                {
                    cpre -> down = p -> down;
                    free(p);
                    p = cpre -> down;
                }
                
                n++;
            }
            else
            {
                cpre = p;
                p = p -> down;
            }
    }

    L -> nums -= n;
    return n;
}

int main()
{
    CrossList a;
    ElemType b[7][6] = {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 97, 67, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 10, 0, 58, 86, 58, 0, 0, 0};
    init_cross_list(&a, &b[0][0], 7, 6);
    del_cross_list(&a, 58);

    return 0;
}