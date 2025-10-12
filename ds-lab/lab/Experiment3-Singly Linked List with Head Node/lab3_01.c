/*编写函数void delx(linklist head, datatype x)，删除带头结点单链表head中第一个值为x 的结点。
并构造测试用例进行测试。
*/ 
/**********************************/
/*文件名称：lab3_01.c                 */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
void delx(linklist head,datatype x)
{
    linklist p = head->next;            //维护一个头结点始终使它存储首元节点的的地址，
    linklist pre = head;
    while(p){
        if(p->info == x){
            pre->next = p->next;
            free(p);
            return;
        }
        pre = p;
        p = p->next;
    }
    return;
}

int main()
{   datatype x;
    linklist head;
    head=creatbyqueue();		/*尾插入法建立带头结点的单链表*/
    print(head);
    printf("请输入要删除的值：");
    scanf("%d",&x);
    delx(head,x);			            /*删除单链表的第一个值为x的结点*/
    print(head);
    delList(head);				/*释放单链表空间*/
    return 0;
}
