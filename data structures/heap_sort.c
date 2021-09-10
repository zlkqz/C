# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct _otherInfo
{
    int i;
    int j;
}OtherInfo;

typedef struct _minHeapNode
{
    int value;
    OtherInfo otherInfo;
}MinHeapNode, *PMinHeapNode;

typedef struct _minPQ {
    PMinHeapNode heap_array; // 指向堆元素数组
    int heap_size; // 当前堆中的元素个数
    int capacity;  //堆数组的大小
}MinHeap, *PMinHeap;

int parent(int i){
    return (i+1) / 2 - 1;
}

int left(int i){
    return (i+1) * 2 - 1;
}

int right(int i){
    return (i+1) * 2;
}

void swap_node(MinHeapNode *x, MinHeapNode *y){
    int a = y -> value;
    y -> value = x -> value;
    x -> value = a;
    OtherInfo t = x -> otherInfo;
    x -> otherInfo = y -> otherInfo;
    y -> otherInfo = t;
}

void init_min_heap(PMinHeap pq, int capacity)
{
    pq -> capacity = capacity;
    pq -> heap_size = 0;
    pq -> heap_array = (PMinHeapNode)malloc(capacity * sizeof(MinHeapNode));
}

bool heap_insert_value(PMinHeap pq, int value)
{
    if (pq -> heap_size == pq -> capacity)
        return false;
    
    MinHeapNode a;
    a.value = value;
    pq -> heap_array[pq -> heap_size] = a;

    int k = pq -> heap_size;
    while (pq -> heap_array[k].value < pq -> heap_array[parent(k)].value)
    {
        swap_node(pq -> heap_array + k, pq -> heap_array + parent(k));
        k = parent(k);
    }

    pq -> heap_size++;
    return true;
}

void min_heapify(PMinHeap pq, int i)
{
    int j = left(i);
    while (j < pq -> heap_size)
    {
        if (j + 1 < pq -> heap_size && pq -> heap_array[j + 1].value < pq -> heap_array[j].value)
            j++;

        if (pq -> heap_array[j].value < pq -> heap_array[i].value)
        {
            swap_node(pq -> heap_array + j, pq -> heap_array + i);
            i = j;
            j = left(i);
        }
        else
            break;
    }
}
