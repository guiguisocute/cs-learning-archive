/*
   试编写一个函数，将一棵给定二叉树中所有结点的左、右子女互换。
*/ 
#include "bintree.h"
char *a="ABC##D##EF#G###";  		/*扩充二叉树序树t的前序序列*/
/*请将本函数补充完整，并进行测试*/
void change(bintree t)
//这个也是递归做，先把当前节点的左子树右子树先给change了，然后再来做自己的镜像
{
   if(!t)
      return;

   change(t->lchild);
   change(t->rchild);

   bintree tmp;
   tmp = t->lchild;
   t->lchild = t->rchild;
   t->rchild = tmp;

}

int main()
{  bintree root;
   root=creatbintree();
   change(root);
   preorder(root);
}
