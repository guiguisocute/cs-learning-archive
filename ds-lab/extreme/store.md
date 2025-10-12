3-4
```c
/*
编写算法函数void  delallx(linklist head, int x)，删除带头结点单链表head中所有值为x的结点。
*/
/**********************************/
/*文件名称：lab3_04.c                 */
/**********************************/
#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
void  delallx(linklist head,int x)
{
        linklist  pre,p;
        pre=head;
        p=head->next;
        while (p)
        {
            if (p->info==x)             //删除
            {
                pre->next=p->next;
                free(p);
                p=pre->next ;
            }
            else            //留在链表中
            {
                pre=p;
                p=p->next;
            }
        }

}
/*删除所有的重复元素节点*/
void del2(linklist head){
    linklist p;     //保留表头
    linklist r;
    linklist q;
    linklist s;
    p = head->next;
    head->next = NULL;
    r = head;
    while(p){
        //查找p指向节点在已经创造的新链表中是否存在（有就说明重复没有就说明没重复）？
        q = head->next;
        while(q && q->info != p->info)  //用q去在心链表种去找
            q = q->next;
        if(q){
            //free p指向的节点
            
        }
        else{
            //插p到head末尾
        }
    }
}
int main()
{   datatype x;
    linklist head;
    head=creatbyqueue();				/*尾插入法建立带头结点的单链表*/
    print(head);
    printf("请输入要删除的值：");
    scanf("%d",&x);
    delallx(head,x);
    print(head);
    delList(head);
    return 0;
}

```

3-5
```c
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
        linklist p,s,pre,q;
        p=head->next;
        head->next=NULL;
        while (p)
        {
            s=p;
            p=p->next;
            s->next=NULL;
            //查找插入位置
            pre=head;
            q=head->next;
            while (q &&q->info > s->info)
            {
                pre=q;
                q=q->next;
            }
            s->next=q;          //插入pre指示的节点后
            pre->next=s;
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

```
3-6
```c
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
    linklist p,q;     //用于L1L2指针移动
    linklist r,head;    //用于新链表的构建和头指针
    head=(linklist)malloc(sizeof(node));
    head->next=NULL;
    r=head;
    p=L1->next;
    q=L2->next;
    while (p && q)
    {
            if (p->info< q->info)
            {
                L1->next=p->next;
                p->next=NULL;
                r->next=p;
                r=p;
                p=L1->next;
            }
            else
            {
                L2->next=q->next;
                q->next=NULL;
                r->next=q;
                r=q;
                q=L2->next;
            }
    }
    if (p) r->next=p;
    if (q) r->next=q;
    free(L1);
    free(L2);
    return head;
}

linklist mergeDescend(linklist L1,linklist L2)
{
    linklist p,q;     //用于L1L2指针移动
    linklist r,head;    //用于新链表的构建和头指针
    head=(linklist)malloc(sizeof(node));
    head->next=NULL;
    p=L1->next;
    q=L2->next;
    while (p && q)
    {
            if (p->info< q->info)
            {
                L1->next=p->next;
                p->next=head->next;   //头插入
                head->next=p;
                p=L1->next;
            }
            else
            {
                L2->next=q->next;
                q->next=head->next;
                head->next=q;
                q=L2->next;
            }
    }
    while  (p)
    {
                L1->next=p->next;
                p->next=head->next;   //头插入
                head->next=p;
                p=L1->next;
    }
    while (q)
    {
                L2->next=q->next;
                q->next=head->next;
                head->next=q;
                q=L2->next;
    }
    free(L1);
    free(L2);
    return head;
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

```

3-7
```c
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
        linklist  pre,p;
        pre=head;
        p=head->next;
        while (p && p->info %2==1)
        {
            pre=p;
            p=p->next;
        }
        while (p)
        {
            if (p->info%2==1)
            {
                pre->next=p->next;
                p->next=head->next;
                head->next=p;
                p=pre->next;
            }
            else
            {
                pre=p;
                p=p->next;
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

```
3-8
```c
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

```
3-9
```c
#include <stdlib.h>
#include <stdio.h>
 /*思路：每一个节点互相比如果不等于零插入，如果等于0则free，有点像归并那题这样合成*/
typedef struct node
{       int coef;        /*系数*/
        int expn;       /*指数*/
        struct node *next;
}listnode;        //多项式存储结构

typedef listnode *linklist;
void delList(linklist head);

 /*
 函数名称： creat()
 函数功能：建立多项式存储结构，并且多项式在表中按所在项的指数递增存放
 */
linklist creat()            //建立多项式存储结构，
{
          linklist head,s,p,pre,r;
          int coef;
          int expn;
          head=(linklist)malloc(sizeof(listnode));    /*生成头结点*/
          head->next=NULL;
          printf("请输入多项式，每一项只需输入系数，指数(当输入的系数为0时结束输入)：\n");
          scanf("%d",&coef);         //输入系数
          scanf("%d",&expn);        //输入指数

          while (coef!=0)       //请在此处填上适当的代码
           {

           }
         return head;
}

void print(linklist head) //输出多项式
  {
        linklist p;
        p=head->next;
        while (p)
        {   printf("%d(X)",p->coef);
            printf("%d    ",p->expn);
            p=p->next;
        }
        printf("\n");
 }

 /*
 函数名称： add()
 函数功能：多项式相加
 入口参数：a与b是存储多项式的带头结点单链表，并且多项式在表中按所在项的指数递增存放
 */
linklist add(linklist a,linklist b)  //请将本函数补充完整
{
            linklist pa,pb,c,pc,r;


}

int main()
 {
           linklist a,b,c;
           a=creat();
           printf("多项式a为：");
           print(a);

           b=creat();
           printf("多项式b为：");
           print(b);

           c=add(a,b);
           printf("两个多项式的和为：\n");
           print(c);
           delList(c);
           return 0;
 }
 /***************************************/
/*函数名称：delList()		 	                	 */
/*函数功能：释放带头结点的单链表      */
/***************************************/
void delList(linklist head)
{ linklist p=head;
  while (p)
  { head=p->next;
    free(p);
    p=head;
  }
}

```

