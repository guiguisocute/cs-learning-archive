/*
试编写一个递归函数bintree buildBintree(char *pre, char *mid, int length)，
根据二叉树的前序序列pre、中序序列mid和前序序列长度length，构造二叉树的二叉链表存储结构，
函数返回二叉树的树根地址。
*/ 

#include "bintree.h"
#include <string.h>
char *a="";
/*请将本函数补充完整，并进行测试*/
/*虽然说做试卷题这种类型的题目画一个矩阵列一个表就能秒了，但显然不适用于程序的编写我们一步一步分析
前序序列，能得到第一个是根节点，但不知道左右子树到底有多大，得到的序列是这样的：根（未知长度的左子树）|（未知长度的右子树）
|就是这个分界点，你没办法知道，所以只凭一个前序序列是画不出一颗二叉树的
中序序列，信息量正好反过来，可以很清楚知道某个根节点的左右子树多大，但是不知道根具体在哪个位置
（能得到数量的左子树）根（能得到具体数量的右子树）
知道这个就能至少有眉目：
左右子树可以递归，主要是知道左右子树有多长就能随便解决问题了
*/
bintree buildBintree(char *pre, char *mid,int length)
{
    if(length <= 0)
        return NULL;
    bintree new = (bintree)malloc(sizeof(binnode));
    new->data = pre[0];
    new->lchild = NULL; new->rchild = NULL;     //别的不说先初始化一个根节点

    int i = 0;
    while(mid[i] != pre[0] && i < length){
        i++;
    }   //找mid里根的位置

    if(i == length){
        return NULL;        //低成本提升一点鲁棒性
    }

    new->lchild = buildBintree(pre + 1, mid, i);    //第一个根已经处理好了，现在去处理下一个根，长度就是中序左半边
    new->rchild = buildBintree(pre + 1 + i, mid +1 + i, length - 1 - i);    //最后那个长度传参一定要注意啊卧槽，画了个左右树结点相同的二叉树结果试了半天没注意到，具体长度就是中序右半边，但是要从前序断点处开始

    return new;


}
int main()
{   bintree root;
    char pre[100],mid[100];
    puts("请输入前序序列：");
    gets(pre);
    puts("请输入中序序列：");
    gets(mid);
    root=buildBintree(pre,mid,strlen(pre));
    puts("后序序列是：");
    postorder(root);
}

