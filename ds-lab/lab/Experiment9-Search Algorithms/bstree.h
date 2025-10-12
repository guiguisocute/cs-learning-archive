/**************************************/
/*         二叉排序树用的头文件         */
/*          文件名：bstree.h              */
/**************************************/
#include<stdio.h>
#include<stdlib.h>
typedef struct node1            /*二叉排序树结点定义*/
 {
  int key;                      /*结点值*/
  struct node1 *lchild,*rchild; /*左、右孩子指针*/
  }bsnode;
typedef bsnode *bstree;

/*
    函数creatBstree()根据输入的结点序列，建立一棵二叉排序树，并返回根结点的地址
*/
bstree  creatBstree()
  {
        bstree t=NULL,parent,p,q;
        int i,flag,n,x;

        printf("请输入拟创建的二叉树中的数据个数：");
        scanf("%d",&n);

        if (n>0)
        {
                printf("请依次输入插入二叉树的%d个整数：\n",n);
                for (i=0;i<n;i++)
                {       scanf("%d",&x);
                        parent=NULL;
                        p=t;
                        flag=0;
                        while (p)           //本循环用于查找插入位置
                        {
                           if (p->key>x)
                           {
                               parent=p;
                               p=p->lchild;
                           }
                           else if (p->key<x)
                           {
                               parent=p;
                               p=p->rchild;
                           }
                           else
                            {
                                flag=1;         //找到相同元素
                                break;
                           }
                        }
                        if (flag==0)            //未找到相同元素
                        {
                            q=(bstree)malloc(sizeof(bsnode));
                            q->key=x;
                            q->lchild=q->rchild=NULL;
                            if (!t)  t=q;
                            else
                                if (q->key <parent->key)
                                    parent->lchild=q;
                                else
                                    parent->rchild=q;
                        }
                }
        }
        return t;
  }

/*---中序遍历二叉排序树----*/
void inorder(bstree t)
  { if (t) {
                inorder(t->lchild);
                printf("%d\n",t->key);
                inorder(t->rchild);
             }

   }
