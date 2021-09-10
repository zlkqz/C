# include <stdio.h>
# define MAXSIZE 20

typedef struct
{
    int elem[MAXSIZE];
    int last;
}SeqList;

void delx(SeqList *L, int x)
{
    int i, j;
    for (i = 0, j = 0; i <= L -> last; i++)
        if (L -> elem[i] != x)
            L -> elem[j++] = L -> elem[i];
    L -> last = j -1;
}

void del_dupnum(SeqList* L)
{
    int flag, i = 0 , j = 0;
    while (i <= L -> last)
    {
        flag = L -> elem[i];
        int k;
        for (k = i + 1; k <= L -> last; k++)
            if (L -> elem[k] != flag)
                break;
        i = k;
        L -> elem[j++] = flag;
    }
    L -> last = j - 1;
}

void odd_even(SeqList* L)
{
    int i = 0, j = L -> last, temp;
     while (i < j)
    {
        while (L -> elem[i] % 2 != 0)
            i++;
        while (L -> elem[j] % 2 == 0)
            j--;
        if (i >= j)
            break;
        temp = L -> elem[i];
        L -> elem[i] = L -> elem[j];
        L -> elem[j] = temp;
        i++;
        j--;
    }
}

int main(void)
{
    SeqList a;
    a.last = MAXSIZE - 1;
    for (int i = 0; i < MAXSIZE; i++)
        scanf("%d", &a.elem[i]);
    for (int i = 0; i < MAXSIZE; i++)
        printf("%d ", a.elem[i]);
        printf("\n");
    odd_even(&a);
    for (int i = 0; i < MAXSIZE; i++)
        printf("%d ", a.elem[i]);


    return 0;
}