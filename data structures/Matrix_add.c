# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# define MAXSIZE 50

typedef struct 
{
    int i, j;
    char e;
}Triple;

typedef struct
{
    Triple data[MAXSIZE];
    int m, n, len;
}TSMatrix;

int compire(Triple *a, Triple *b)            //判断按照行主序的前后
{
    if (a -> i == b -> i && a -> j == b -> j)
        return 0;           //位置相同
    else if ((a -> i > b -> i) || (a -> i == b -> i && a -> j > b -> j))
        return 1;           //a在b后面
    else
        return -1;          //a在b前面
}

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ)
{
    if (pM -> m != pN -> m || pM -> n != pN -> n)
    return false;

    pQ -> m = pM -> m;
    pQ -> n = pM -> n;

    int len = 0;
    Triple *m, *n;
    m = pM -> data;
    n = pN -> data;

    while (m < pM -> data + pM -> len && n < pN -> data + pN -> len)
    {
        switch (compire(m, n))
        {
            case 0:
            {
                if (m -> e + n -> e != 0)
                {
                    pQ -> data[len] = *m;
                    (pQ -> data[len]).e += n -> e;
                    len++;
                }
                m++;
                n++;
                break;
            }
            case 1:
            {
                pQ -> data[len] = *n;
                n++;
                len++;
                break;
            }
            case -1:
            {
                pQ -> data[len] = *m;
                m++;
                len++;
                break;
            }
        }
    }

    while (m != pM -> data + pM -> len)
    {
        pQ -> data[len] = *m;
        m++;
        len++;
    }

    while (n != pN -> data + pN -> len)
    {
        pQ -> data[len] = *n;
        n++;
        len++;
    }

    pQ -> len = len;
    return true;
}