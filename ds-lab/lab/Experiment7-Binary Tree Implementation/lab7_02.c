/*
编写算法函数void levelbintree(bintree t)，实现二叉树的层次遍历。
*/
 
#include "bintree.h"
char *a="ABC##D#E##F##";  			/*扩充二叉树序树t的前序序列*/
void levelbintree(bintree t)
{
    //建个队列出队入队就完事了甚至还比一般树要好写一点上个实验就写过了
    //只要队列不为空就出队然后再把孩子从左到右生进队列里
    bintree quene[N];
    int front = 0, rear = 0;

    if(t){
        quene[rear] = t;
        rear++;
    }else{
        return;
    }
    while(front < rear){
        bintree temp = quene[front];
        printf("%c",temp->data);
        front++;
        if(temp->lchild)
            quene[rear++] = temp->lchild;
        if (temp->rchild)
            quene[rear++] = temp->rchild;
    }

}
int main()
{   bintree t;
    t=creatbintree();   	/*建立二叉树t的存储结构*/
    printf("二叉树的层次序列为：\n");
    levelbintree(t);       /*层次遍历二叉树*/
    return 0;
}
