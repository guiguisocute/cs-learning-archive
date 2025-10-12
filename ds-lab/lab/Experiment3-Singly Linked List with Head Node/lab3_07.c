/*
请编写一个算法函数void partion(linklist head)，
将带头结点的单链表head中的所有值为奇数的结点调整
到链表的前面，所有值为偶数的结点调整到链表的后面。
*/

/**********************************/
/*文件名称：lab3_07.c             */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
void partion(linklist head)
{
    //奇数尾插偶数头插？不行！创建链表这两不能混用，否则一定会导致混乱，
    //只能像数组那样创造两个新链表再合并，把偶数单独扔出去（扔出去的操作有点像删结点，不过free变成了指向新结点）再重新接上就可以了（题目没有要求必须保留顺序，方便起见偶数我弄成头插吧）。

    /*实践发现这种方法还是太太太太复杂了，要新增好多新指针不好维护……还是用老师讲的那种
    跳过前面连续的前导奇数，使得pre留在最后一个奇数上，随后，后面只要遇到奇数就摘下头插到 原 链表，这样用两个指针就完成了任务*/
    linklist pre = head;
    linklist p = head->next;
    if(!p)return;      
    while(p->info % 2 == 1){
        pre = p;
        p = p->next;
    }
    while(p){
        if(p->info % 2 == 1){
            pre->next = p->next;
            p->next = head->next;
            head->next = p;
            p = pre->next;
        }else{
            pre = p;
            p = p->next;
        }
    }


}
int main()
{        linklist head;
         head=creatbyqueue();           /*尾插法建立带头结点的单链表*/
         print(head);                   /*输出单链表head*/
         partion(head);
         print(head);
         delList(head);
         return 0;
}
