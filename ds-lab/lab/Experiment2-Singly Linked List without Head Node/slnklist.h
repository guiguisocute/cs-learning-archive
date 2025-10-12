#include <stdio.h>
#include <stdlib.h> 
/**************************************/
/* 链表实现的头文件，文件名slnklist.h */
/**************************************/
 typedef int datatype;
 typedef struct link_node{
   datatype info;
   struct link_node *next;
 }node;
typedef node *linklist;

/**********************************/
/*函数名称：creatbystack() 			 */
/*函数功能：头插法建立单链表            */
/**********************************/
linklist creatbystack()
{  linklist  head,s;
    datatype x;
    head=NULL;
    printf("请输入若干整数序列:\n");
    scanf("%d",&x);
    while (x!=0)		/*以0结束输入*/
    {   s=(linklist)malloc(sizeof(node));  /*生成待插入结点*/
        s->info=x;
        s->next=head;			/*将新结点插入到链表最前面*/
        head=s;
        scanf("%d",&x);
    }
    return head;				/*返回建立的单链表*/
}
/**********************************/
/*函数名称：creatbyqueue() 			 */
/*函数功能：尾插法建立单链表            */
/**********************************/
linklist creatbyqueue()
{
    linklist head,r,s;
    datatype x;
    head=r=NULL;
    printf("请输入若干整数序列:\n");
    scanf("%d",&x);
    while (x!=0) /*以0结束输入*/
    {    s=(linklist)malloc(sizeof(node));
         s->info=x;
         if (head==NULL)		/*将新结点插入到链表最后面*/
            head=s;
         else
            r->next=s;
        r=s;
        scanf("%d",&x);
   }
    if (r)  r->next=NULL;
    return head;					/*返回建立的单链表*/
}
/**********************************/
/*函数名称：print()		 			 */
/*函数功能：输出不带头结点的单链表      */
/**********************************/
void print(linklist head)
{   linklist p;
    int i=0;
    p=head;
    printf("List is:\n");
    while(p)
    {
        printf("%5d",p->info);
        p=p->next;
         i++;
		 if (i%10==0) printf("\n");
    }
    printf("\n");
}
/**********************************/
/*函数名称：delList()		 		 */
/*函数功能：释放不带头结点的单链表      */
/**********************************/
void delList(linklist head)
{ linklist p=head;
  while (p)
  { head=p->next;
    free(p);
    p=head;
  }
}

