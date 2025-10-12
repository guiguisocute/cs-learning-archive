/*
实验7.1 编写算法函数void preorder1(bintree t)实现二叉树t的非递归前序遍历。
*/ 



#include "bintree.h"
char *a="ABC##D#E##F##";  /*扩充二叉树序树t的前序序列*/
//这个就是正常的前序创造树，#代表空叶

/*函数preorder1()的功能是非递归前序遍历二叉树t，请将函数补充完整并调试运行*/
void preorder1(bintree t)
{
    // core: 模拟“先访问自己，再左，再右”
    // 逻辑：栈非空——→pop，然后push右，push左，直到栈空就停
    seqstack b;     
    init(&b);
    if(t)push(&b,t);

    while(!empty(&b)){
        bintree temp = pop(&b);
        printf("%c",temp->data);
        if(temp->rchild)push(&b,temp->rchild);
        if(temp->lchild)push(&b, temp->lchild);
    }
    
}
int main()
{   bintree t;
    t=creatbintree();   /*建立二叉树t的存储结构*/
    printf("二叉树的前序序列为：\n");
    preorder(t);       //验证一致性
    printf("\n");
    printf("二叉树的后序序列为：\n");
    postorder(t);      //验证一致性
    printf("\n");
    printf("二叉树的前序非递归遍历为：\n");
    preorder1(t);
    return 0;
}
