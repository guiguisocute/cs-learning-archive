/*
已知带头结点的单链表结构定义同实验3，设计一个递归算法，删除链表head中所有值为x的结点。
*/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
void delAll(linklist head,datatype x)
{ 
    //根据提示慢慢一步一步往后写就行了，这个揭老师实在给的太多了哈哈哈
    linklist p;
    if (head->next == NULL)           //链表为空表
        return ;
    if (head->next->info==x)    //链表的第1个结点值为x
    {
        p = head->next;
        head->next = p->next;
        free(p);
        delAll(head,x);     //进入了这个分支也要递归，要不然没法删重复的了
    }
    else{
        delAll(head->next,x);     //指针一直往前移,直到遇到第1个节点为x的情况
    }
                  
}
int main()
{   linklist head;
    datatype x;
    head=creatbyqueue();
    print(head);
    printf("请输入要删除的数：");
    scanf("%d",&x);
    delAll(head,x);
    print(head);
    return 0;
}
