# include <stdio.h>
# include <stdlib.h>

typedef enum{
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,
    HASH_REPLACED_VALUE,
    HASH_ALREADY_ADDED,
    HASH_DELETED,
    HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;

struct __HashEntry{
    union{
        char  *str_value;
        double dbl_value;
        int       int_value;
    } key;
    union{
        char  *str_value;
        double dbl_value;
        int       int_value;
        long   long_value;
        void  *ptr_value;
    } value;
    HashEntry *next;
};

struct __HashTable{
    HashEntry **bucket;        
    int size;
    HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;
// 创建大小为hash_size的哈希表，创建成功后返回HashTable类型的指针，否则返回NULL。

HashTable* create_hash(int size)
{
    HashTable *table;

    table = (HashTable*)malloc(sizeof(HashTable));
    table -> size = size;

    if ((table -> bucket = (HashEntry**)malloc(size * sizeof(HashEntry*))) == NULL)
        return NULL;
    
    int i = 0;
    HashEntry **p;
    for (p = table -> bucket; i < size; i++, p++)
        *p = NULL;

    return table;
}

long hash_string(const char *str)
{
    long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if(hash < 0)
        hash *= -1;
    return hash;
}

HASH_RESULT hash_add_int(HashTable *table, const char *key, int value )
{
    HASH_RESULT result;
    long hash = hash_string(key);

    HashEntry **p = table -> bucket + hash % table -> size;

    if (*p == NULL)
    {
        HashEntry *s = (HashEntry*)malloc(sizeof(HashEntry));
        (s -> key).str_value = (char *)key;
        (s -> value).int_value = value;
        s -> next = NULL;
        *p = s;
        result = HASH_ADDED;
    }
    else
    {
        while ((*p) -> next != NULL)
            if (((*p) -> value).int_value == value)
            {
                result = HASH_ALREADY_ADDED;
                return result;
            }

        if (((*p) -> value).int_value == value)
        {
            result = HASH_ALREADY_ADDED;
            return result;
        }

        HashEntry *s = (HashEntry*)malloc(sizeof(HashEntry));
        (s -> key).str_value = (char *)key;
        (s -> value).int_value = value;
        s -> next = NULL;
        (*p) -> next = s;
        result = HASH_REPLACED_VALUE;
    }

    return result;
}

int main()
{
    HashTable* a = create_hash(5);
    const char *key = "abc";
    int value = 123;
    hash_add_int(a, key, value);    

    return 0;
}