#include <stdlib.h>
#include <stdio.h>
typedef char datatype; 
typedef struct node
{   datatype data;
    struct node *next;
}linknode;
typedef linknode *linkstring;
/**********************************/
/*函数名称：creat() 			      */
/*函数功能：尾插法建立字符单链表         */
/**********************************/
linkstring creat()
{   linkstring head,r,s;
    datatype x;
    head=r=(linkstring)malloc(sizeof(linknode));
    head->next=NULL;
    printf("请输入一个字符串（以回车结束）:\n");
    scanf("%c",&x);
    while (x!='\n')
    {    s=(linkstring)malloc(sizeof(linknode));
         s->data=x;
         r->next=s;
         r=s;
         scanf("%c",&x);
   }
     r->next=NULL;
    return head;
}
/**********************************/
/*函数名称：print() 			      */
/*函数功能：输出字符串                   */
/**********************************/
void print(linkstring head)
{   linkstring p;
    p=head->next;
    printf("List is:\n");
    while(p)
    {   printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}

/*释放单链表的内容*/
void delList(linkstring head)
{
  linkstring p=head;
  while (p)
  {
    head=p->next;
    free(p);
    p=head;
  }
}
