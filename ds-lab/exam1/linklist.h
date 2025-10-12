#include <stdlib.h>
#include <stdio.h>
typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}linknode;
typedef linknode *linklist;

/*输出不带头结点的单链表*/
void print(linklist head)
{
    linklist p;
    p=head;
    while(p)
    {
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}

/*释放单链表的内容*/
void delList(linklist head)
{
  linklist p=head;
  while (p)
  {
    head=p->next;
    free(p);
    p=head;
  }
}
