/*
图采用邻接表存储结构，编程对图进行广度优先遍历（层次）。
*/
/**********************************/
/*文件名称：lab8_02.c                 */
/**********************************/
#include "ljb.h"
int visited[M] = {0};  				/*全局标志向量*/
/*请将本函数补充完整，并进行测试*/
void bfs(LinkedGraph g, int i)
/*广度有限，差不多理解为层次遍历，按照书本上嗯写就可以了
BFS类比成层次遍历就完事了，但因为图顶点之间不像树一样，具有那么强的上下级关系，所以得建立个上面那样的visit数组标记一下顶点的遍历情况
建队列
首个进队，队非空，把邻接表后面且visit = 0的放进去，把vsit改成1，然后再出队（打印，队首指针移动）*/
{ /*从顶点i出发广度优先变量图g的连通分量*/
  
  VertexNode quene[M];
  int r = 0, f = 0;
  quene[r] = g.adjlist[i];
  r++;
  visited[i] = 1;

  while(f < r){
    EdgeNode* p = quene[f].FirstEdge;
    while(p && visited[p->adjvex] == 0){
      quene[r++] = g.adjlist[p->adjvex];  //邻接点入队
      visited[p->adjvex] = 1;
      p = p->next;
    }
    printf("%c",quene[f++].vertex);
  }
  printf("\n");
  return;
}


/*函数功能：广度优先遍历图g
  函数参数：邻接表g
*/
int BfsTraverse(LinkedGraph g)
{  int i,count=0;
   for (i=0;i<g.n;i++)
       visited[i]=0;     /*初始化标志数组*/

   for (i=0;i<g.n;i++)
       if (!visited[i])  /*vi未访问过*/
       {printf("\n");
        count++;            /*连通分量个数加1*/
        bfs(g,i);
       }
   return count;
 }

int main()
{ 	  LinkedGraph g;
      int count;
      creat(&g,"g11.txt",0);  		/*创建图的邻接表*/
      printf("\n The graph is:\n");
      print(g);
      printf("广度优先遍历序列为：\n");
      count=BfsTraverse(g);     	/*从顶点0出发广度优先遍历图g，在这里打印的*/
      printf("\n该图共有%d个连通分量。\n",count);
      return 0;
}


