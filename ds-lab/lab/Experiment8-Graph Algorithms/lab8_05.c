/***************************************************/
/*          Dijkstra单源最短路径算法               */
/***************************************************/
#include "ljjz.h"   /*引入邻接矩阵创建程序*/
typedef enum{FALSE,TRUE} boolean;/*false为0,true为1*/
typedef int dist[M];  
/*
距离向量类型
  告诉你v0到图中所有点的最短路径的“值”是多少，但没法知道是怎么走出来的
*/
typedef int path[M];  
/*
路径类型
  储存了直接的前驱，可以通过一步一步反推（用栈）最后到源点，可输出一个完全正确的路径
也就是说，如果你没有这个输出路径的需求，那确实可以不创造path数组
*/

/*函数功能：Dijkstra算法求解单源最短路径
函数参数：图的邻接矩阵g;源点v0;路径向量p；距离向量d
*/
void dijkstra(Mgraph g,int v0,path p,dist d)
 { boolean final[M]; /*表示当前元素是否已求出最短路径，意思就是有没有把这个循环内的path与dist填完，真的闹麻了这个描述……*/
   int i,k,j,v,min,x;

   /*  第1步  初始化集合S与距离向量d，意思就是初始化，初始源点的dist数据和path数据，更新dist的时候同事更新dist */
  for(v = 0; v < g.n; v++){
    final[v] = FALSE;     //顺带把final数组也初始化了
    d[v] = g.edges[v0][v];
    if(d[v] != FINITY && d[v] != 0){
      p[v] = v0;      
    }else{
      p[v] = -1;
    }
  }

  final[v0] = TRUE;

  /* 第2步  依次找出n-1个结点加入S中   */
  for(i = 0; i < g.n - 1; i++){   
    //这个大循环，代表后面还有n-1个顶点要填,和i没什么关系了
    min = FINITY;
    
    for(k = 0; k < g.n; k++){
      //从dist里找最小的
      if(!final[k] && min > d[k]){
        v = k;
        min = d[k];
      }
    }
    final[v] = TRUE;
    //找到了这个保留下来的dist，也找到了对应的v
    /*第3步 修改新加点后的path与dist（同时）*/
    for(k = 0; k < g.n; k++){
      if(!final[k] && (min + g.edges[v][k]) < d[k]){      //如果没有被标记的情况下，并且之前最小路径加上最新
        d[k] = min + g.edges[v][k];
        p[k] = v;
      }
    }
  }
   }
/*函数功能：输出有向图的最短路径
函数参数：邻接矩阵g；路径向量p；距离向量d
*/
void print_gpd(Mgraph g,path p,dist d)
 {
   int st[M],i,pre,top=-1;
   for (i=0;i<g.n;i++)
    { printf("\nDistancd: %7d , path:" ,d[i]);
      st[++top]=i;
      pre=p[i];
      while (pre!=-1)   /*从第i个顶点开始向前搜索最短路径上的顶点*/
        { st[++top]=pre;
          pre=p[pre];
         }
      while (top>0)
     printf("%2d",st[top--]);
     //用一个小栈输出路径
    }
 }
/*---------- 主程序 ------------*/
int main()
 { Mgraph g;   /* 有向图 */
   path p;     /* 路径向量 */
   dist d;     /* 最短路径向量 */
   int v0;
   creat(&g,"G21.txt",1); /*假设图8.21所示的有向网G21的输入文件为g21.txt */
   print(g);        /*输出图的邻接矩阵*/
   printf("\n");
   printf("请输入源点编号：");
   scanf("%d",&v0);       /*输入源点*/
   dijkstra(g,v0,p,d);   /*求v0到其他各点的最短距离*/
   /*输出V0到其它各点的路径信息及距离*/
   print_gpd(g,p,d);

    return 0;
  }
