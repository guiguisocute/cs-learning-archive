/*
已知线性表存储在带头结点的单链表head中，请设计算法函数void sort(linklist head)，将head中的结点按结点值升序排列。
*/
/**********************************/
/*文件名称：lab3_05.c                 */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
void  sort(linklist head)
{
    //核心思路是插入排序，一个最合适链表的O(n2)排序法（每次选出一个未排序的节点，然后找到它在已排序部分的正确位置并插入）

    linklist unsorted_head = head->next;    //原链表遍历的指针
    linklist t;     //取结点指针
    linklist sorted_p;      //排序好链表的遍历指针
    linklist sorted_pre;       //上一个指针的前驱
    head->next = NULL;
    while(unsorted_head){
        t = unsorted_head;
        unsorted_head = t->next;
        t->next = NULL;

        sorted_p = head->next;
        sorted_pre = head;

        //查找插入位置
        while(sorted_p && sorted_p->info <= t->info){
            sorted_pre = sorted_p;
            sorted_p = sorted_p->next;        
        }

        //一开始还犯蠢了while条件偷懒只写了指针p不为空，加了条件判断结果break来break去的，还忽略了边界条件……

        t->next = sorted_p;
        sorted_pre->next = t;
    }

    }

int main()
{        linklist head;
         head=creatbyqueue();   		/*尾插法建立带头结点的单链表*/
         print(head);    			    /*输出单链表head*/
         sort(head);     				/*排序*/
         print(head);
         delList(head);
         return 0;
}
