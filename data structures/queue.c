# include <stdio.h>
# include <conio.h>
# define MAXSIZE 50

typedef struct node
{
    char data;
    struct node *next;
}LinkQueueNode;

typedef struct
{
    LinkQueueNode *front;
    LinkQueueNode *rear;
}LinkQueue;

typedef struct
{
    char elem[MAXSIZE];
    int front;
    int rear;
}SeqQueue;

int EnterQueue(SeqQueue *Q, char x)
{
    if ((Q -> rear + 1) % MAXSIZE == Q -> front)
        return 0;
    Q -> elem[Q -> rear] = x;
    Q -> rear = (Q -> rear + 1) % MAXSIZE;
    return 1;
}

int DeleteQueue(SeqQueue *Q, char *x)
{
    if (Q -> front == Q -> rear)
        return 0;
    *x = Q -> elem[Q -> front];
    Q -> front = (Q -> front + 1) % MAXSIZE;
    return 1;
}

/*void YangHuiTriangle(int n)
{
    SeqQueue Q;
    Q.front = Q.rear = 0;
    int i = 1, j = 1, x, x1, x2 = 0;
    while (i <= n)
    {
        while (j <= i)
        {
            if(j == 1 || j == i)
                x = 1;
            else
            {
                if (j == 2)
                {
                    DeleteQueue(&Q, &x1);
                    printf("%d ", x1);
                    DeleteQueue(&Q, &x2);
                    printf("%d ", x2);
                    x = x1 + x2;
                }
                else
                {
                    x1 = x2;
                    DeleteQueue(&Q, &x2);
                    printf("%d ", x2);
                    x = x1 + x2;
                }
            }//上一排的队列相加得到
            
            EnterQueue(&Q, x);
            j++;
        }

        if (i != 1)
            printf("\n");
        else
        {
            DeleteQueue(&Q, &x);
            printf("%d ", x);
        }

        j = 1;
        i++;
    }

    while (Q.front != Q.rear)
    {
        DeleteQueue(&Q, &x);
        printf("%d ", x);
    }
}*/                    //队列的元素为int

void print_queue(SeqQueue *Q)
{
    char x;
    while (Q -> rear != Q -> front)
    {
        DeleteQueue(Q, &x);
        printf("%c", x);
    }       
}

void buffer()
{
    char ch;
    int flag = 0, f;
    SeqQueue Q;
    while (1)
        if (kbhit())
        {
            ch = getch();
            if (ch == ';' || ch == ',')
            {
                print_queue(&Q);
                if (flag)
                    break;
                flag++;                
            }
            else
            {
                f = EnterQueue(&Q, ch);
                if (f == 0)         //判断队列满
                    break;
            }
        }
        else
            printf("A");
}



int main()
{
    buffer();
}



