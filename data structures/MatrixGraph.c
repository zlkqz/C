# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_VERTEX_NUM  20

typedef int VertexType;

typedef enum
{
    DG, UDG
}GraphType;

typedef struct
{
    VertexType vertex[MAX_VERTEX_NUM]; //顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
    GraphType type;     //图的种类标志
}MatrixGraph;

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);

bool matrix_insert_vertex(MatrixGraph *G, VertexType v)
{
    int location;
    if (G -> vexnum == MAX_VERTEX_NUM || (location = matrix_locate_vertex(G, v)) != -1)
        return false;

    G -> vexnum++;
    G -> vertex[G -> vexnum - 1] = v;
    for (int i = 0; i < G -> vexnum; i++)
    {
        G -> arcs[i][G -> vexnum - 1] = 0;
        G -> arcs[G -> vexnum - 1][i] = 0;
    }

    return true;
}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w)
{
    int i = matrix_locate_vertex(G, v), j = matrix_locate_vertex(G, w);
    
    if (i == -1 || j == -1 || G -> arcs[i][j] == 1)
        return false;

    G -> arcs[i][j] = 1;
    if (G -> type == UDG)
        G -> arcs[j][i] = 1;
    G -> arcnum++;
    return true;
}