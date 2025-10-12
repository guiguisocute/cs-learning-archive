/*
假设二叉树采用链式方式存储，t为其根结点，编写一个函数int Depth(bintree t, char x)，求值为x的结点在二叉树中的层次。
*/ 
#include "bintree.h"
char *a="ABC##D##EF#G###";  		/*扩充二叉树序树t的前序序列*/

/*
 	函数Depth，功能：求结点x所在的层次
*/
int Depth(bintree t,char x)
{
   //递归，爽！左边找到了那就左边的深度+1（别管这深度怎么来的），右边找到了就右边深度+1，根本身那就是1
   if(!t)
         return 0;
   if(t->data == x)
      return 1;
   
   int left = Depth(t->lchild,x);
   int right = Depth(t->rchild, x);
   
   if(left > 0)
      return left + 1;
   if(right > 0)
      return right + 1;
   return 0;
}

int main()
{  bintree root;
   char x;
   int k=0;
   root=creatbintree();
   printf("请输入树中的1个结点值：\n");
   scanf("%c",&x);
   k=Depth(root,x);
   printf("%c结点的层次为%d\n",x,k);
}
