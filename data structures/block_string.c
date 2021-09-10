# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
#define BLOCK_SIZE 4
#define BLS_BLANK '#'   

typedef struct block
{
    char ch[BLOCK_SIZE];
    struct block *next;
}Block;

typedef struct
{
    Block *head;
    Block *tail;
    int len;
}BLString;

void blstr_init(BLString *T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}

bool blstr_substr(BLString src, int pos, int len, BLString *sub)
{
    if (pos < 0 || pos >= src.len || len == 0)
        return false;

    blstr_init(sub);
    int i = 0;
    Block *p = src.head, *q, *s;
    while (i < pos)
    {
        i++;
        if (i % BLOCK_SIZE == 0)
            p = p -> next;
    }
    
    s = (Block*)malloc(sizeof(Block));
    sub -> head = sub -> tail = s;
    q = sub -> tail;

    int j = 0, f;
    while (j < len)
    {
        q -> ch[j % BLOCK_SIZE] = p -> ch[i % BLOCK_SIZE];

        i++;
        j++;

        if (i % BLOCK_SIZE == 0)
            p = p -> next;
        
        if (i >= src.len)
            break;

        if (j % BLOCK_SIZE == 0 && j != len)
        {
            s = (Block*)malloc(sizeof(Block));
            sub -> tail -> next = s;
            sub -> tail = s;
            q = s;
        }
    }

    f = j;
 
    while (j % BLOCK_SIZE != 0)
    {
        q -> ch[j % BLOCK_SIZE] = '#';
        j++;
    }

    sub -> len = f;
    sub -> tail -> next = NULL;

    return true;
}

int main()
{
    int a;
    scanf("%d", &a);
    printf("%d", a);
}