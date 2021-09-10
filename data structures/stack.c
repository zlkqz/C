# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# define STACK_SIZE 30
# define MAX_SIZE 40

typedef struct
{
    char elem[STACK_SIZE];
    int top;
}SeqStack;

typedef struct
{
    int elem[STACK_SIZE];
    int top;
}SeqStack_int;

int push(SeqStack *s, char c)
{
    if (s -> top == STACK_SIZE - 1)
        return 0;

    s -> top++;
    s -> elem[s -> top] = c;
    return 1;
}

int push_int(SeqStack_int *s, int i)
{
    if (s -> top == STACK_SIZE - 1)
        return 0;

    s -> top++;
    s -> elem[s -> top] = i;
    return 1;
}

int pop(SeqStack *s, char *x)
{
    if (s -> top == -1)
        return 0;

    *x = s -> elem[s -> top];
    s -> top--;
    return 1;
}

int is_Empty(SeqStack *s)
{
    if (s -> top == -1)
        return 1;
    else
        return 0;
}

int BracketMatch(char *str)
{
    SeqStack s;
    char *a = str;
    s.top = -1;
    while (*a)
    {
        switch (*a)
        {
            case '(': case '[': case '{':
                push(&s, *a);
                break;
            
            case ')':
                if (s.elem[s.top] == '(')
                    pop(&s, a);
                else
                    return 0;
                break;
            
            case '}':
                if (s.elem[s.top] == '{')
                    pop(&s, a);
                else
                    return 0;
                break;
            
            case ']':
                if (s.elem[s.top] == '[')
                    pop(&s, a);
                else
                    return 0;
                break;        
        }
        a++;
    }

    if (is_Empty(&s))
        return 1;
    else
        return 0;

}

int operation(int num1, int num2, char op)
{
    int a = 1;
    switch (op)
    {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '^':
            for (int i = 1; i <= num2; i++)
                a *= num1;
            return a;
    }
}

int Transform(char **ch)
{
    char s[7];
    int i = 0;
    while (**ch >= '0' && **ch <= '9')
    {
        s[i++] = **ch;
        (*ch)++;
    }
    s[i] = 0;

    return atoi(s);
}

int ExpEvaluation()        //#结束符，^次方
{
    SeqStack_int OVS;         //运算数
    SeqStack OPTR;          //运算符
    OVS.top = OPTR.top = -1;
    char s[MAX_SIZE];
    gets(s);
    char *ch = s;
    int temp;
    while (*ch != '#')
    {
        if (*ch >= '0' && *ch <= '9')
        {
            temp = Transform(&ch);
            push_int(&OVS, temp);
        }
        else
        {
            switch (*ch)
            {
                case '+': case '-':
                    if (OPTR.top == -1)
                        push(&OPTR, *ch);
                    else
                    {
                        temp = operation(OVS.elem[OVS.top - 1], OVS.elem[OVS.top], OPTR.elem[OPTR.top]);
                        OVS.top -= 2;
                        OPTR.top--;
                        push_int(&OVS, temp);
                        push(&OPTR, *ch);
                    }
                    break;
                        
                case '*': case '/':
                    if (OPTR.elem[OPTR.top] == '^' || OPTR.elem[OPTR.top] == '*' || OPTR.elem[OPTR.top] == '/')
                    {
                        temp = operation(OVS.elem[OVS.top - 1], OVS.elem[OVS.top], OPTR.elem[OPTR.top]);
                        OVS.top -= 2;
                        OPTR.top--;
                        push_int(&OVS, temp);
                        push(&OPTR, *ch);
                    }
                    else
                        push(&OPTR, *ch);
                    break;
                
                case '^':
                    push(&OPTR, *ch);
                    break;
            }
            ch++;
        }
    }

    while (OPTR.top != -1)
    {
        temp = operation(OVS.elem[OVS.top - 1], OVS.elem[OVS.top], OPTR.elem[OPTR.top]);
        OVS.top -= 2;
        OPTR.top--;
        push_int(&OVS, temp);
    }

    return OVS.elem[OVS.top];
}

bool plalindrome(char *s)
{
    SeqStack S;
    S.top = -1;
    char x;
    while (*s != '&')
    {
        if (*s == '@')
            return false;
        push(&S, *s);
        s++;
    }

    s++;

    while (*s != '@')
    {
        pop(&S, &x);
        if (x != *s)
            return false;
        s++;
        if (is_Empty(&S))
            break;
    }

    if (!is_Empty(&S) || *s != '@')
        return false;

    return true;
}