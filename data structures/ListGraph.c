# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_VERTEX_NUM  20

typedef int VertexType;
typedef int InfoPtr;

typedef enum
{
    DG, UDG
}GraphType;

typedef struct ArcNode
{
    int adjvex;
    InfoPtr* info;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
}VNode;

typedef struct
{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph* G, VertexType v)     //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
{
    for (int i = 0; i < G -> vexnum; i++)
        if ((G -> vertex[i]).data == v)
            return i;

    return -1;
}

bool insert_vertex(ListGraph *G, VertexType v)
{
    int location;
    if (G -> vexnum >= MAX_VERTEX_NUM || (location = locate_vertex(G, v)) != -1)
        return false;

    G -> vertex[G -> vexnum].data = v;
    G -> vertex[G -> vexnum].firstarc = NULL;
    G -> vexnum++;

    return true;
}

bool arc_exist(ListGraph *G, int i, int j)          //寻找G中有无i->j边， 有返回true, 无返回false
{
    ArcNode *p = (G -> vertex[i]).firstarc;

    while (p != NULL)
        if (p -> adjvex == j)
            return true;
        else
            p = p -> nextarc;

    return false;
}

bool insert_arc(ListGraph *G, VertexType v, VertexType w)
{
    int i = locate_vertex(G, v), j = locate_vertex(G, w);

    if (i == -1 || j == -1 || arc_exist(G, i, j))
        return false;

    ArcNode *p = (G -> vertex[i]).firstarc, *s = (ArcNode*)malloc(sizeof(ArcNode));
    s -> adjvex = j;
    s -> info = NULL;
    
    (G -> vertex[i]).firstarc = s;
    s -> nextarc = p;

    if (G -> type == UDG)
    {
        p = (G -> vertex[j]).firstarc;
        ArcNode *r = (ArcNode*)malloc(sizeof(ArcNode));
        r -> adjvex = i;
        r -> info = NULL;

        (G -> vertex[j]).firstarc = r;
        r -> nextarc = p;
    }

    G -> arcnum++;

    return true;
}

bool del_vertex(ListGraph *G, VertexType v)
{
    int location;
    if (G -> vexnum <= 0 || (location = locate_vertex(G, v)) == -1)
        return false;

    ArcNode *p = (G -> vertex[location]).firstarc, *q = NULL;

    while (p != NULL)             //删除以v为弧尾的边
    {
        q = p -> nextarc;
        free(p);
        p = q;
        G -> arcnum--;
    }

    for (int i = location; i < G -> vexnum - 1; i++)
        G -> vertex[i] = G -> vertex[i + 1];

    G -> vexnum--;

    for (int i = 0; i < G -> vexnum; i++)     //删除以v为弧头的边
    {
        p = (G -> vertex[i]).firstarc;

        while (p != NULL)             //q为p的前驱
        {
            if (p -> adjvex == location)            //删除
            {
                if (q == NULL)
                {
                    (G -> vertex[i]).firstarc = p -> nextarc;
                    free(p);
                    p = (G -> vertex[i]).firstarc;
                }
                else
                {
                    q -> nextarc = p -> nextarc;
                    free(p);
                    p = q -> nextarc;
                }

                if (G -> type == DG)
                    G -> arcnum--;
            }
            else                     //更改数组移动之后引起的下标改变
            {
                if (p -> adjvex > location)
                    p -> adjvex--;

                q = p;
                p = p -> nextarc;
            }
        }

        q = NULL;
    }

    return true;
}

int main()
{
    ListGraph G;
    G.arcnum = G.vexnum = 0;
    G.type = UDG;
    insert_vertex(&G, 1);
    insert_vertex(&G, 2);
    insert_vertex(&G, 3);
    insert_arc(&G, 1, 2);
    insert_arc(&G, 1, 3);
    insert_arc(&G, 3, 2);
    del_vertex(&G, 2);
}
