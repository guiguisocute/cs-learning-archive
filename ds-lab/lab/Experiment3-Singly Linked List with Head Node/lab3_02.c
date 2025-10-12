/**********************************/
/*文件名称：lab3_02.c                 */
/**********************************/
/* 
假设线性表（a1,a2,a3,…an）采用带头结点的单链表存储，请设计算法函数void reverse(linklist  head)，
将带头结点的单链表head就地倒置，使表变成（an,an-1,…a3.a2,a1）。并构造测试用例进行测试。
*/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
void reverse(linklist head)     //head一直都是“按兵不动的”
{
    linklist s = head->next;
    linklist pre = head;
    while(s->next){
        s = s->next;
        s->next = pre->next;
        head->next = s;
        pre = s->next;
    }
    return;
}

void reverse2(linklist head){
    linklist p;
    linklist s;

    p = head->next;
    head->next = NULL;
    while(p){
        s = p;
        p = p->next;
        s->next = head->next;
        head->next = s;
    }
}
int main()
{   datatype x;
    linklist head;
    head=creatbystack();			/*头插入法建立带头结点的单链表*/
    print(head);					/*输出原链表*/
    reverse(head);			/*倒置单链表*/
    print(head);					/*输出倒置后的链表*/
    delList(head);
    return 0;
}
