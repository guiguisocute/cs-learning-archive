#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define m 3
#define MAXLEN 100

typedef char datatype;
typedef struct node {
     datatype data;
     struct node *child[m];     //每个树节点最多三个孩子
} node;     //树指针名
//这个好像是孩子表示法？

typedef  node *tree;

typedef struct linknode
{
    tree info;
    struct linknode *next;
} linknode;
typedef linknode *linklist; // 链式栈存储结构

/********************************************************/
/*  函数功能:根据树的前序遍历结果建立一棵3度树	  	   */
/*  函数返回值:树根地址								   */
/*  文件名:tree.h,函数名:createtree ()		            */
/********************************************************/

tree  createtree()
{ /*按前序遍历顺序建立一棵3度树的递归算法
    也可以叫做是先根遍历
    "根-左-右"的访问顺序*/

    int i;
    char ch;
    tree t;
    if ((ch = getchar()) == '#')
        t = NULL;
    else
    {
        t = (tree)malloc(sizeof(node));
        t->data = ch;
        for (i = 0; i < m; ++i)
            t->child[i] = createtree();
    }
    return t;
}

void preorder(tree t)
    //用递归前序遍历的方法打印树
{
    int i;
    if (t)
        {
            printf("%c",t->data);
            for (i=0;i<m;i++)
                preorder(t->child[i]);
        }
}

void postorder(tree t)
//用递归后序遍历的方法打印树（先访问所有子树最后访问根节点）
//左子树→右子树→根
{
    int i;
    if (t)
        {
            for (i=0;i<m;i++)
                postorder(t->child[i]);
            printf("%c",t->data);
        }
}
