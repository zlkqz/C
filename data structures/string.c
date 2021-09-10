# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <ctype.h>
# define MAXLEN 50

typedef struct
{
    char elem[MAXLEN];
    int len;
}SString;

bool str_insert(SString *s, int pos, SString *t)
{
    if (pos < 0 || pos > s -> len)
        return false;         //插入位置不合法
    
    int i;

    if (s -> len + t -> len <= MAXLEN)        //插入后没有溢出
    {
        for (i = s -> len - 1; i >= pos; i--)
            s -> elem[i + t -> len] = s -> elem[i];
        for (i = 0; i < t -> len; i++)
            s -> elem[i + pos] = t -> elem[i];
        s -> len = s -> len + t -> len;
        return true; 
    }
    else if (pos + t -> len <= MAXLEN)        //插入之后原s的pos后面丢失一部分
    {
        for (i = MAXLEN - t -> len - 1; i >= pos; i--)
            s -> elem[i + t -> len] = s -> elem[i];
        for (i = 0; i < t -> len; i++)
            s -> elem[i + pos] = t -> elem[i];
        s -> len = MAXLEN;
        return true;
    }
    else                                    //插入之后原s的pos后面部分全部丢失
    {
        for (i = pos; i < MAXLEN; i++)
            s -> elem[i] = t -> elem[i - pos];
        s -> len = MAXLEN;
        return true;
    }
}

void get_next(SString t, int next[])
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < t.len - 1)
        if (j == -1 || t.elem[i] == t.elem[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
}

int KMP(SString s, SString t, int pos, int next[])
{
    int i = pos, j = 0;
    while (i < s.len && j < t.len)
        if (j == -1 || s.elem[i] == t.elem[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];

    if (j == t.len)
        return i -j;
    else
        return -1;
}

void print_str(SString *s)
{
    for (int i = 0; i < s -> len; i++)
        printf("%c", s -> elem[i]);
}

int str_compare(const char* ptr1, const char* ptr2)
{
    const char *p1 = ptr1, *p2 = ptr2;
    
    while (*p1 && *p2)
        if (toupper(*p1) != toupper(*p2))
            return *p1 - *p2;
        else
        {
            p1++;
            p2++;
        }

    if (*p1)
        return 1;
    else if (*p2)
        return -1;
    else
        return 0; 
}

void get_substr(int start, int final, char *s, char *t)
{
    for (int i = start; i < final; i++)
        t[i - start] = s[i];
}

void longest_substr(SString l, SString s, SString *longest)           //l为长串，s为短串
{
    int i, next[MAXLEN];
    char temp[MAXLEN];

    for (i = s.len; i > 0; i--)
        for (int j = 0; j + i <= s.len; j++)
        {
            get_substr(j, j + i, s.elem, longest -> elem);
            longest -> len = i;
            get_next(*longest, next);

            if (KMP(l, *longest, 0, next) != -1)
                return;
        }

    if (i == 0)
        printf("No substr!");
}

int main()
{
    SString s1, s2, s3;
    gets(s1.elem);
    s1.len = strlen(s1.elem);
    gets(s2.elem);
    s2.len = strlen(s2.elem);
    longest_substr(s1, s2, &s3);
    puts(s3.elem);
}