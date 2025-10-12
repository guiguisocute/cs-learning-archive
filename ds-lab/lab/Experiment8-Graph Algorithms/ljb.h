/*********************************************/
/*    邻接表存储结构   文件名：ljb.h     	 */
/*********************************************/

#include <stdio.h>
#include <stdlib.h>
#define M 20					/*预定义图的最大顶点数*/
typedef char DataType;  /*顶点信息数据类型，在此处，这里规定了每个顶点存储一个字符信息*/

//邻接表最重要的一点：顶点表后面的边表顺序其实无所谓的，取决于输入人，如果是无向图，那更没法预测了，邻接表的链表就真只能表示这个顶点所有的边，没法规定说顺序怎么样怎么样

typedef struct node{    /*边表结点*/
      int adjvex;                  /*邻接点*/
      // int weight;                 /*边的权值（假设有）*/ 
      struct node *next;
   }EdgeNode;
   // 每个 EdgeNode 表示一条「从某顶点出发」的边，adjvex 存储*被*指向顶点的序号，next 串起该顶点的所有邻接边。

   typedef struct vnode
   {                       /*头结点类型*/
      DataType vertex;     /*顶点信息*/
      EdgeNode *FirstEdge; /*邻接链表头指针*/
   } VertexNode;

typedef struct{           /*邻接表类型*/
 VertexNode adjlist[M];  /*存放头结点的顺序表*/
 int n,e;                 /*图的顶点数与边数*/
}LinkedGraph;


/*函数功能：建立图的邻接表
  函数参数：邻接表指针变量g；存放图信息的文件名filename;图的类型参数c，c=0表示建立无向图，否则表示建立有向图 
  函数返回值：无
*/ 
void creat(LinkedGraph *g,char *filename,int c)
    { int i,j,k;
      EdgeNode *s;
      FILE *fp;
      fp=fopen(filename,"r");
      if (fp)
      {
      fscanf(fp,"%d%d",&g->n,&g->e);              /*读入顶点数与边数*/
    
      for(i=0;i<g->n;i++)
       {
          fscanf(fp, " %c", &g->adjlist[i].vertex); /*读入顶点信息*/
          g->adjlist[i].FirstEdge = NULL;           /*边表置为空表*/
       }
  
      for(k=0;k<g->e;k++)                     /*循环e次建立边表*/
        {
            fscanf(fp,"%d%d",&i,&j);                 /*输入无序对（i,j）*/
            s=(EdgeNode *)malloc(sizeof(EdgeNode));
            s->adjvex=j;                         /*邻接点序号为j*/
            s->next=g->adjlist[i].FirstEdge;
            g->adjlist[i].FirstEdge=s;           /*将新结点*s插入顶点vi的边表头部*/
            /*这好像是头插，实际生成出来的边表链应该是倒置的*/

            if (c==0)                            /*无向图，这就真的只是一个简单粗暴地标识符啊*/ 
            {
            s=(EdgeNode *)malloc(sizeof(EdgeNode));
            s->adjvex=i;                         /*邻接点序号为i*/
            s->next=g->adjlist[j].FirstEdge;
            g->adjlist[j].FirstEdge=s;           /*将新结点*s插入顶点vj的边表头部*/
			}
        }
    fclose(fp);
    }
    else
    g->n=0;
   }
/*---函数print():输出邻接表存储结构---*/
void print(LinkedGraph  g)
{  EdgeNode *p;
   int i;
   for (i=0;i<g.n;i++)
    {   printf("%c",g.adjlist[i].vertex);
        p=g.adjlist[i].FirstEdge;
        while (p)
        {   printf("-->%d",p->adjvex);
            p=p->next;
        }
     printf("\n");
   }
}
