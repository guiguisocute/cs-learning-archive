/*
已知，二叉树存储结构定义见bstree.h，请编写一个算法函数bstree  creatBstreeByArray(int a[],int n)，
以数组a中的数据作为输入建立一棵二叉排序树，并将建立的二叉排序树进行中序遍历。
（提示，a中的原始数据可从data1.txt中读入，实验代码详见lab9_05.c）

*/

#include "Arrayio.h"
#include "bstree.h"
#define N 100
bstree  creatBstreeByArray(int a[],int n)
//really easy，就是二叉排序树不断查找的变体，失败时看比上一个节点是大了还是小了然后认贼作父（有原则地）
  { /*根据输入的结点序列，建立一棵二叉排序树，并返回根结点的地址*/
    bstree root = malloc(sizeof(bsnode));
    root->key = a[0];
    root->lchild = NULL;
    root->rchild = NULL;    //首元素入根

    for(int i = 1; i < n; i++){
      bstree p = root;
      bstree parent;
      bstree temp = malloc(sizeof(bsnode));
      temp->key = a[i];     //以下三行为插入的新节点的样子
      temp->lchild = NULL;
      temp->rchild = NULL;
      char flag;      //判断插到左孩子还是右孩子那里

      while(p){         //p不为空，作比较看看p怎么去“滑动”
        if(a[i] > p->key){
          parent = p;
          p = p->rchild;
          flag = 'r';   
        }else{
          parent = p;
          p = p->lchild;
          flag = 'l';
        }
      }
      if(flag == 'r'){
        parent->rchild = temp; 
      }else{
        parent->lchild = temp;
      }
    }
    return root;
  }
int  main()
  {
    int n,a[N];
    bstree t;
    n=readData(a,N,"data1.txt");
    output(a,n);
    t=creatBstreeByArray(a,n);         /*创建二叉排序树*/
    printf("中序遍历：\n");
    inorder(t);                 /*中序遍历二叉排序树*/
    return 0;
 }


