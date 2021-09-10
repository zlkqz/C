# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define STACK_SIZE 30
# define QUEUE_SIZE 30

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
}BiTNode, *BiTree;

typedef struct
{
    BiTree elem[STACK_SIZE];
    int top;
}Stack;

typedef struct
{
    BiTree elem[QUEUE_SIZE];
    int front;
    int rear;
}Queue;

Stack s;
Queue q;

void init_queue(Queue *q)
{
    q -> rear = q -> front = 0;
}

bool is_empty_queue(Queue *q)
{
    if (q -> front == q -> rear)
        return true;
    else
        return false;
}

int EnterQueue(Queue *Q, BiTree x)
{
    if ((Q -> rear + 1) % QUEUE_SIZE == Q -> front)
        return 0;
    Q -> elem[Q -> rear] = x;
    Q -> rear = (Q -> rear + 1) % QUEUE_SIZE;
    return 1;
}

int DeleteQueue(Queue *Q, BiTree *x)
{
    if (Q -> front == Q -> rear)
        return 0;
    *x = Q -> elem[Q -> front];
    Q -> front = (Q -> front + 1) % QUEUE_SIZE;
    return 1;
}

int is_empty(Stack *s)
{
    if (s -> top == -1)
        return 1;
    else
        return 0;
}

void init_stack(Stack *s)
{
    s -> top = -1;
}

bool top(Stack *s, BiTree *p)
{
    if (is_empty(s))
        return false;

    *p = s -> elem[s -> top];
    return true;
}

int push(Stack *s, BiTNode *c)
{
    if (s -> top == STACK_SIZE - 1)
        return 0;

    s -> top++;
    s -> elem[s -> top] = c;
    return 1;
}

int pop(Stack *s, BiTree *x)
{
    if (s -> top == -1)
        return 0;

    *x = s -> elem[s -> top];
    s -> top--;
    return 1;
}

void create_bitree(BiTree *root)          //使用之后记得把缓冲区中的\n给弹出
{
    char ch;
    ch = getchar();
    if (ch == '.')
        *root = NULL;
    else
    {
        *root = (BiTNode*)malloc(sizeof(BiTNode));
        (*root) -> data = ch;
        create_bitree(&((*root) -> left));
        create_bitree(&((*root) -> right));
    }
}

void pre_order(BiTree root)              //先序遍历非递归算法
{
    init_stack(&s);
    BiTNode *p = root;
    while (p != NULL || !is_empty(&s))
    {
        while (p != NULL)
        {
            putchar(p -> data);
            push(&s, p);
            p = p -> left;
        }

        pop(&s, &p);
        p = p -> right;
    }
}

void in_order(BiTree root)           //中序遍历非递归算法
{
    init_stack(&s);
    BiTNode *p = root;

    while (p != NULL || !is_empty(&s))
    {
        while (p != NULL)
        {
            push(&s, p);
            p = p -> left;
        }

        pop(&s, &p);
        putchar(p -> data);
        p = p -> right;
    }
}

void post_order(BiTree root)                //后序遍历非递归算法
{
    init_stack(&s);
    BiTNode *p = root, *pre = NULL;

    while (p != NULL || !is_empty(&s))
    {
        while (p != NULL)
        {
            push(&s, p);
            p = p -> left;
        }

        top(&s, &p);
        p = p -> right;

        while (p == NULL || pre == p)
        {
            pop(&s, &p);
            putchar(p -> data);
            if (p == root)
                return;
            pre = p;
            top(&s, &p);
            p = p -> right;
        }
    }
}

bool layer_order(BiTree root)             //层次遍历
{
    if (root == NULL)
        return false;

    init_queue(&q);
    BiTNode *p = root;
    EnterQueue(&q, root);

    while (!is_empty_queue(&q))
    {
        DeleteQueue(&q, &p);
        if (p -> left != NULL)
            EnterQueue(&q, p -> left);
        if (p -> right != NULL)
            EnterQueue(&q, p -> right);

        putchar(p -> data);
    }

}

bool like(BiTree t1, BiTree t2)
{
    if (t1 == NULL && t2 == NULL)
        return true;

    if ((t1 == NULL && t2 != NULL) || (t1 != NULL && t2 == NULL))
        return false;

    if (like(t1 -> left, t2 -> left) && like(t1 -> right, t2 -> right))
        return true;
    else
        return false;
}

void del_children(BiTree root)
{
    if (root != NULL)
    {
        del_children(root -> left);
        del_children(root -> right);
        free(root);
    }
}

void cut(BiTree root, char x)         //调用时要先注意最上方的根节点是否data为x
{
    if (root != NULL)
    {
        if (root -> left != NULL && root -> left -> data == x)
        {
            del_children(root -> left);
            root -> left = NULL;
        }
        if (root -> right != NULL && root -> right -> data == x)
        {
            del_children(root -> right);
            root -> right = NULL;
        }

        cut(root -> left, x);
        cut(root -> right, x);
    }
}

int main()
{
    BiTree a;
    char x = 'b';
    create_bitree(&a);
    getchar();
    if (a -> data == x)
        del_children(a);
    else
        cut(a, x);
    
    return 0;
}