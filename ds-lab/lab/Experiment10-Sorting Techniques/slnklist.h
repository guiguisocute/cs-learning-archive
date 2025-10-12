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
/*函数名称：print()		 			 */
/*函数功能：输出带头结点的单链表      */
/**********************************/
void print(linklist head)
{
    linklist p;
    int i=0;
    p=head->next;
    printf("List is:\n");
    while(p)
    {
        printf("%7d",p->info);
        i++;
        if (i%10==0)    printf("\n");
        p=p->next;
    }
    printf("\n");

}

/******************************************/
/*函数名称：creatLink() 			      */
/*函数功能：从文件中读入n个数据构成单链表 */
/******************************************/
linklist creatLink(char *f, int n)
{
    FILE *fp;
    int i;
    linklist s,head,r;
    head=r=(linklist)malloc(sizeof(node));
    head->next=NULL;
    fp=fopen(f,"r");
    if (fp==NULL)
        return head;
    else
    {
         for (i=0;i<n;i++)
            {
                s=(linklist)malloc(sizeof(node));
                fscanf(fp,"%d",&(s->info));
                r->next=s;
                r=s;
            }
        r->next=NULL;
        fclose(fp);
        return head;
    }
}
/*
    函数功能：将链表内容存入文件f
*/
void writetofile(linklist head, char *f)
{
    FILE *fp;
    linklist p;
    int i=0;
    fp=fopen(f,"w");
    if (fp!=NULL)
    {
        p=head->next;
        fprintf(fp,"%s","List is:\n");
        while(p)
        {
            fprintf(fp,"%7d",p->info);
            i++;
            if (i%10==0)    fprintf(fp,"%c",'\n');
            p=p->next;
        }
        fprintf(fp,"%c",'\n');
        fclose(fp);
    }
    else    printf("创建文件失败!");

}

/**********************************/
/*函数名称：delList()		 		 */
/*函数功能：释放带头结点的单链表      */
/**********************************/
void delList(linklist head)
{ linklist p=head;
  while (p)
  { head=p->next;
    free(p);
    p=head;
  }
}
