/*
假设不带头结点的单链表head是升序排列的，设计算法函数linklist insert(linklist head,datatype x)，
将值为x的结点插入到链表head中，并保持链表有序性。
分别构造插入到表头、表中和表尾三种情况的测试用例进行测试。
*/ 
/**********************************/
/*文件名称：lab2_03.c                 */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
linklist insert(linklist head, datatype x) {

    linklist newNode = (linklist)malloc(sizeof(node));  //动态分配新节点
    newNode->info = x;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    linklist pre = NULL;    
    linklist p = head;

    while(p){
        if(x < p->info){
            if(pre == NULL){
                head = newNode;
                newNode->next = p;
            }else{
                pre->next = newNode;
                newNode->next = p;
            }
            return head;
        }else{
            pre = p;
            p = p->next;
        }
    }
    pre->next = newNode;
    newNode->next = p;
    return head;
}

int main()
{   datatype x;
    linklist head;
    printf("输入一组升序排列的整数：\n");
    head=creatbyqueue();				/*尾插入法建立单链表*/
    print(head);
    printf("请输入要插入的值：");
    scanf("%d",&x);
    head=insert(head,x);				/*将输入的值插入到单链表适当位置*/
    print(head);
    delList(head);
    return 0;
}
