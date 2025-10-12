/***************************************/
/*             拓扑排序算法            */
/***************************************/
#include <stdlib.h>
#include <stdio.h>
#define M 20
typedef char vertextype;
typedef struct node
{ /*边结点类型定义*/
    int adjvex;
    struct node *next;
} edgenode;
typedef struct de /*带顶点入度的头结点定义*/
{
    edgenode *FirstEdge;
    vertextype vertex;
    int id; /*顶点的入度域*/
} vertexnode;

typedef struct
{ /*AOV网络的邻接表结构*/
    vertexnode adjlist[M];
    int n, e;
} AovGraph;

void creat(AovGraph *g, char *filename) /*建立AOV网络的存储结构*/
{
    int i, j, k;
    edgenode *s;
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp)
    {
        fscanf(fp, "%d%d", &g->n, &g->e); /*输入图中的顶点数与边数*/

        for (i = 0; i < g->n; i++) /*输入顶点值*/
        {
            fscanf(fp, "%1s", &g->adjlist[i].vertex);
            g->adjlist[i].FirstEdge = NULL;
            g->adjlist[i].id = 0; /*入度初始化为0*/
        }
        for (k = 0; k < g->e; k++)
        {
            fscanf(fp, "%d%d", &i, &j);
            s = (edgenode *)malloc(sizeof(edgenode));
            s->adjvex = j;
            g->adjlist[j].id++; /*顶点j的入度加1*/
            s->next = g->adjlist[i].FirstEdge;
            g->adjlist[i].FirstEdge = s;
        }
    }
}
void print(AovGraph g)
{
    edgenode *p;
    int i;
    for (i = 0; i < g.n; i++)
    {
        printf("%c %d   ", g.adjlist[i].vertex, g.adjlist[i].id);
        p = g.adjlist[i].FirstEdge;
        while (p)
        {
            printf("%d-->", p->adjvex);
            p = p->next;
        }
        printf("\n");
    }
}
/*函数功能：拓扑排序
函数参数：AOV网邻接表存储结构变量g
函数返回值：拓扑排序输出的顶点个数
*/
int TopSort(AovGraph g)
{
    int k = 0, i, j, v, flag[M];
    int queue[M]; /*队列*/
    int h = 0, t = 0;
    edgenode *p;
    for (i = 0; i < g.n; i++)
        flag[i] = 0; /*访问标记初始化*/
                     /*先将所有入度为0的结点进队*/
                     /*将程序补充完整*/
    for (i = 0; i < g.n; i++)
    {
        if (g.adjlist[i].id == 0)
        {
            queue[t++] = i; // 进队
            flag[i] = 1;    // 标记为已访问
        }
    }
    while (h < t)
    {                   // 队列不为空
        v = queue[h++]; // 出队
        printf("%c ", g.adjlist[v].vertex);
        k++;
        p = g.adjlist[v].FirstEdge;
        while (p)
        {
            j = p->adjvex;
            g.adjlist[j].id--; // 相邻顶点的入度减1
            if (g.adjlist[j].id == 0 && !flag[j])
            {
                queue[t++] = j; // 如果入度变为0，则进队
                flag[j] = 1;    // 标记为已访问
            }
            p = p->next;
        }
    }
    return k; // 返回输出的顶点个数
}
int main()
{
    int k = 0;
    AovGraph g;
    creat(&g, "aov.txt"); /*假设图8.25所示的AOV网输入文件为aov.txt*/
    printf("\n图8.27所示AOV网的邻接表是：\n");
    print(g);
    k = TopSort(g);
    if (k < g.n)
        printf("\n该图存在环！\n");
    return 0;
}