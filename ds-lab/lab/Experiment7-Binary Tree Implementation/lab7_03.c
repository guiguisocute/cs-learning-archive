/*
编写函数bintree prelist(bintree t)，bintree postfirst(bintree t)，
分别返回二叉树t在前序遍历下的最后一个结点地址和后序遍历下的第一个结点地址。
*/ 

#include "bintree.h"
char *a="ABC##D##EF#G###";  /*扩充二叉树序树t的前序序列*/

//函数1返回最右节点，函数2返回最左边的结点
bintree prelast(bintree t)
//递归写最爽，应该不超过五行把，最右节点，右子树非空有的话就在右子树里，右子树空的话就去左子树找，都空证明找到咯（不用担心会找到更左边的叶子因为前面的条件总是会优先拐到右边的）
{
    if (!t)
        return NULL;
    if(t->rchild)
        return prelast(t->rchild);
    else if(t->lchild)
        return prelast(t->lchild);
    else{
        return t;
    }
}
bintree postfirst(bintree t)
//和前面一样只不过换了个方向左右根，找最左边，左子树非空去左边找，右子树非空去右边找，都空了就是根
{
    if (!t)
        return NULL;
    if (t->lchild)
        return postfirst(t->lchild);
    else if(t->rchild)
        return postfirst(t->rchild);
    else{
        return t;
    }
}

int main()
{   bintree t,p,q;
    t=creatbintree();   	/*建立二叉树t的存储结构*/
    p=prelast(t);
	q=postfirst(t);
	if (t!=NULL)
            {   printf("前序遍历最后一个结点为：%c\n",p->data);
			    printf("后序遍历第一个结点为：%c\n",q->data);
            }
	 else	printf("二叉树为空！");
    return 0;
}


