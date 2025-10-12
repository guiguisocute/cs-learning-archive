/*
假设树采用指针方式的孩子表示法表示，试编写一个非递归函数void PreOrder1(tree root)，实现树的前序遍历算法。
*/ 
#include "tree.h"


void  PreOrder1(tree root)
{
        // 非递归那就是自己操作栈了
        //具体思路就是创建一个树栈先把根节点给入进去，然后只要栈非空就取栈访问数据并访问节点打印出来这个节点的数据，再看孩子的指针域，把孩子们**从右往左**（这样才能保证出栈的时候从左往右）放进栈，最后循环这个操作就行了
        if(!root){
                return;
        }

        tree stack[MAXLEN];
        int top = -1;

        stack[++top] = root;    //最开始的根节点入栈
        
        while(top >= 0){
                tree temp = stack[top--];
                printf("%c",temp->data);
                for(int i = m - 1; i>=0; i--){
                        if(temp->child[i]){
                                stack[++top] = temp->child[i];
                        }
                }
        }

}
void PreOrder2(tree root){      //现在改成链式栈进行前序遍历
        // 这个链式栈的实现方式和上面那个差不多，只不过是用链表来实现
        if(!root){
                return;
        }

        linklist stack = NULL;    //链式栈初始化为空

        linklist new = (linklist)malloc(sizeof(linknode));
        new->info = root;     //把根节点放入新结点中
        new->next = stack;    
        stack = new;          

        while(stack != NULL){
                linklist temp = stack;   //保存当前栈顶结点
                stack = stack->next;       
                printf("%c",temp->info->data);  
                for(int i = m - 1; i>=0; i--){
                        if(temp->info->child[i]){
                                linklist newNode = (linklist)malloc(sizeof(linknode));   
                                newNode->info = temp->info->child[i];     
                                newNode->next = stack;
                                stack = newNode;
                        }
                }
                free(temp);
        }
}

    int main()
{
        tree root;
        printf("please input the preorder sequence of the tree:\n");
        root =createtree();
        printf("前序序列是：\n");
        PreOrder2(root);
        return 0;
}
