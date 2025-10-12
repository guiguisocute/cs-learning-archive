/*
设计一个递归算法，使得它对任一给定的带头结点的整数单链表head，删除重复结点（对于多个值相同的结点，保留最后一个结点）.
*/
#include "slnklist.h"


/*函数inList(linklist head,datatype x)的功能是判断带头结点的单链表head中是否含有值为x的结点，有则返回1，无则返回0
*/
int inList(linklist head,datatype x)
{   //这个没说要递归，正常遍历就行了
    linklist p = head;
    while(p){
        if(p->info == x){
            return 1;
        }
        p = p->next;
    }
    return 0;
}

/*函数delSameNode的功能是采用递归算法删除head中的重复结点（对于多个值相同的结点，保留最后一个结点。
输入输出例子大概是输入1 2 2 3 1 4 3，输出2 1 4 3*/

void delSameNode(linklist head)
{
    linklist p;
    if (head->next == NULL || head->next->next == NULL)
    { // 链表为空或只有一个结点
        return;
    }
    //这题的思想又回归到了lab01上，先假设后续的已经全删干净了（就是不包括当前首结点的情况下没有重复），然后再检查当前的首节点有没有和后续重复的情况（检查逻辑就是利用inlist遍历处理完的链表看有无1），如果有就正常删
    
    p = head->next;     //保存当前节点，！！！这一点折磨了我非常久，注意递归后返回的链表结构可能会发生改变，最好不要再前置递归频繁调用传参，会死锁绕结

    delSameNode(head->next);        //递归体
    //后面就是检查当前节点（head->next）是否在后续链表中存在（这个就是形式上不带头结点了哈）
    if(inList(p->next,p->info)){      //传参1是后续链表头，传参2则是当前节点数据
        head->next = p->next;
        free(p);
    }

}


int main()
{
    linklist head;
    head=creatbyqueue();
    print(head);
    delSameNode(head);
    print(head);
    delList(head);
    return 0;
}
