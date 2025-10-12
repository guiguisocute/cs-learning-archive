/*
编写一个程序，用尽可能快的方法返回带头结点单链表
中倒数第k个结点的地址，如果不存在，则返回NULL。
*/
/**********************************/
/*文件名称：lab3_08.c             */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
linklist   search(linklist head,int k)
{
    /*首先分析，我们肯定用On的算法，再快没可能了怎么都要至少遍历一遍，假设我们这边是可以直接知道链表长度那么直接单个指针步进（n-k）步就行了，
    只不过呢，我们没法做到提前知道链表长度，但我们至少知道k，以及获取n的一个“间接条件”，指针为空，这样，首先构建一个指针步进k步，然后再让它步进到为空，这样，他第二次走的距离肯定是n-k步了，此时我们在他第二次走之前让另外一个指针一起和它动，这样第二个指针刚好就站在n-k步那里，当然我们还要处理边界判断这样，这个都是比较容易的*/

    linklist fast = head;
    linklist slow = head;
    for(int i = 0; i < k; i++){
        if(fast == NULL){
            return NULL;
        }
        fast = fast->next;
    }
    while(fast){
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}


int main()
{
     int k;
     linklist head,p;
     head=creatbyqueue();        /*尾插法建立带头结点的单链表*/
     print(head);                  /*输出单链表head*/
     printf("k=");
     scanf("%d",&k);
     p=search(head,k);
     if (p) printf("%d\n",p->info);
     else
         printf("Not Found!\n");
     delList(head);
     return 0;
}
