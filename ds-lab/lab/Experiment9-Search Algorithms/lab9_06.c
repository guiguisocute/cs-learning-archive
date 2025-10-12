/*设计一个递归算法，从大到小输出二叉排序树中所有关键字不小于k的结点值。
*/
#include "bstree.h"

/*
    函数outPut(t,k)的功能是从大到小输出二叉排序树中所有关键字不小于k的结点值，请将本函数补充完整。
*/

/*已知中序是从小到大，用的是递归，从大到小就是逆中序右根左，改一下完全没难度，不小于k那么就是在输出前做个判断就行，关键是怎么做这个k的判断分布区进行讨论下
分为节点比k大和比k小的情况，如果节点本身比k大，才要继续看比节点值更小的左树，如果节点值比k都要小了，比该节点更小的左树看都不要看一眼*/
void outPut(bstree t,int k)
{
  if(!t)
    return;
  if(t->key >= k){
    outPut(t->rchild,k);
    printf("%d\n",t->key);
    outPut(t->lchild,k);
  }else{
    outPut(t->rchild,k);
  }

}

int  main()
  {
    int k;
    bstree t;
    printf("本程序从大到小输出二叉排序树中所有关键字不小于k的结点值。\n");
    t=creatBstree();         /*创建二叉排序树*/
    printf("请输入k的值：");
    scanf("%d",&k);
    printf("输出结果：\n");
    outPut(t,k);
    return 0;
 }
