/*
编写算法函数linklist delallx(linklist head, int x)，删除不带头结点单链表head中所有值为x的结点。
*/
/**********************************/
/*文件名称：lab2_04.c                 */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
linklist delallx(linklist head,int x)
{ 
    linklist p = head;
    linklist pre = NULL;  // 前驱指针

    while (p != NULL) {   
        if (p->info == x) {   
            if (pre == NULL) {  // 情况1：删除头结点
                head = p->next; 
                free(p);        
                p = head;       
            } else {            // 情况2：删除中间或末尾结点
                pre->next = p->next; 
                free(p);         
                p = pre->next;  // p指向下一个待检查的结点
            }
        } else {               // 未找到x，继续后移
            pre = p;           // pre跟上p
            p = p->next;       // p后移
        }
    }
    return head; 

}
linklist delallx_fun2(linklist head,int x){
    linklist newnode_head = NULL;
    linklist newnode_rear = NULL;
    linklist p = head;

    while(p){ 
        linklist next = p->next;    //每次临时保存p的next避免被指针操控后数据销毁  
        if(p->info != x){
            if(newnode_head == NULL){
                newnode_head = p;
                newnode_rear = p;
            }else{
                newnode_rear->next = p;
                newnode_rear = p;
            }
            p->next = NULL;    //只要满足条件当时的p就是在哪一个操作中的实际逻辑的尾结点，其next当然为空
        }
        p = next;
    }
    return newnode_head;
}
int main()
{   datatype x;
    linklist head;
    head=creatbyqueue();				/*尾插入法建立单链表*/
    print(head);
    printf("请输入要删除的值：");
    scanf("%d",&x);
    // head=delallx(head,x);
    head = delallx_fun2(head,x);
    print(head);
    delList(head);
    return 0;
}
