/*
已知两个带头结点的单链表L1和L2中的结点值均已按升序排序，设计算法函数
linklist mergeAscend (linklist L1,linklist L2)将L1和L2合并成一个升序的
带头结单链表作为函数的返回结果；
设计算法函数linklist mergeDescend (linklist L1,linklist L2)
将L1和L2合并成一个降序的带头结单链表作为函数的返回结果；
并设计main()函数进行测试。
*/
/**********************************/
/*文件名称：lab3_06.c                 */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
linklist mergeAscend(linklist L1,linklist L2)
{
    linklist L3 = (linklist)malloc(sizeof(node));
    L3->next = NULL;
    linklist r3 = L3;
    linklist p1,p2;
    p1 = L1->next;
    p2 = L2->next;
    linklist t;
    //归并第一步，不断比较大小然后按顺序放进新链表(怎么放？尾插法)
    while(p1 && p2){
        if(p1->info < p2->info){
            t = p1;
            p1 = p1->next;
            t->next = NULL;
            r3->next = t;
            r3 = t;
        }else{
            t = p2;
            p2 = p2->next;
            t->next = NULL;
            r3->next = t;
            r3 = t;
        }
    }
    //归并第二步，一个表走到头了，剩下只用无脑放另一个表就行了
    while(p1){
            t = p1;
            p1 = p1->next;
            t->next = NULL;
            r3->next = t;
            r3 = t;
    }
    while(p2){
            t = p2;
            p2 = p2->next;
            t->next = NULL;
            r3->next = t;
            r3 = t;
    }
    free(L2);
    free(L1);
    return L3;
}

linklist mergeDescend(linklist L1,linklist L2)
{
    linklist L3 = (linklist)malloc(sizeof(node));
    L3->next = NULL;
    linklist p1,p2;
    p1 = L1->next;
    p2 = L2->next;
    linklist t;
    //归并第一步，不断比较大小然后按顺序放进新链表(怎么放？头插法，毕竟题要求降序)
    while(p1 && p2){
        if(p1->info < p2->info){
            t = p1;
            p1 = p1->next;
            t->next = L3->next;
            L3->next = t;
        }else{
            t = p2;
            p2 = p2->next;
            t->next = L3->next;
            L3->next = t;
        }
    }
    //归并第二步，一个表走到头了，剩下只用无脑放另一个表就行了
    while(p1){
            t = p1;
            p1 = p1->next;
            t->next = L3->next;
            L3->next = t;
    }
    while(p2){
            t = p2;
            p2 = p2->next;
            t->next = L3->next;
            L3->next = t;
    }
    free(L1);
    free(L2);
    return L3;
}


int main()
{       linklist h1,h2,h3;
         h1=creatbyqueue();     /*尾插法建立单链表,请输入升序序列*/
         h2=creatbyqueue();
         print(h1);
         print(h2);
         h3=mergeAscend(h1,h2);/*升序合并到h3*/
        //  h3=mergeDescend(h1,h2);
            /*降序合并请调用h3=mergeDescend(h1,h2); */
         print(h3);
         delList(h3);
         return 0;
}
