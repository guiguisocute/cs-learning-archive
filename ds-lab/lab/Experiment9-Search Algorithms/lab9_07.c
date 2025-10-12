/*设计一个算法，在一棵二叉排序树中求出指定结点的层次，若树为空，返回-1，若结点不在树中，返回0。
*/
#include "bstree.h"

/*
    函数level(t,k)的功能是在一棵二叉排序树中求出指定结点的层次，若树为空，返回-1，若结点不在树中，返回0，请将函数补充完整。
*/

//总体思路上和标准二叉树查找返回层次差不太多，但排序二叉树有个好处就是确定了他在另一边后就无需管另外一边了，少遍历了半边，还是爽到的。
int level(bstree t,int k)
{
  if(!t)
   return -1;
  
  if(t->key == k)
    return 1;
  int i;
  if(k > t->key){
    i = level(t->rchild, k);
  }else{
    i = level(t->lchild, k);
  }
  if(i > 0){
    return i + 1;
  }

  return 0;

  
}

int  main()
  {
    int k,lev;
    bstree t;
    t=creatBstree();         /*创建二叉排序树*/
    printf("请输入拟查找的值：");
    scanf("%d",&k);
    lev=level(t,k);
    if (lev>0) printf("%d在树中的第%d层.\n",k,lev);
    else if (lev==0) printf("未找到该结点.\n");
    else printf("该二叉排序树为空树.\n");
    return 0;
 }
