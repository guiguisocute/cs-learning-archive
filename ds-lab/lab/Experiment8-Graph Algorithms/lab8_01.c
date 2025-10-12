/*
编写程序输出以邻接表为存储结构的无向图的各顶点的度。
*/
/**********************************/
/*文件名称：lab8_01.c                 */
/**********************************/
#include "ljb.h"
/* 输出以邻接表为存储结构的无向图g的各顶点的度 */
/*只需要知道邻接表是怎么被构建出来的，这个实验基本就是送的
1:  最外层循环遍历顶点数组
2： 内层循环内置个计数器每找到一个边表结点就++直到最后空
*/
void degree(LinkedGraph g)
{
  printf("The degree is:\n");
  for(int i = 0; i < g.n; i++){
    EdgeNode* p = g.adjlist[i].FirstEdge;   //初始化为“头结点”指向的第一个边表结点
    int d = 0;
    printf("%c: ",g.adjlist[i].vertex);
    while(p){
      d++;
      p = p->next;
    }
    printf("%d\n",d);
  }
}
int main()
{ LinkedGraph g;
  creat(&g,"G11.txt",0);  	/*已知G11.txt中存储了图的信息*/
  printf("顶点数：%d, 边数：%d\n", g.n, g.e);
  printf("\n The graph is:\n");
  print(g);
  degree(g);
  return 0;
}
