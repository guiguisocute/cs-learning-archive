/*  利用creatLink()函数从data1.txt中读入不同规模的数据存入不带头结点的单链表，
编写基于单链表的顺序查找算法，测试数据量为1万、5万、10万、20万、
30万、40万和50万时的数据查询时间。
*/

#include "slnklist.h"
#define N 500000          /*数据量*/
/*请将本函数补充完整，并进行测试*/
linklist  seqsearch(linklist  head, int key)
{
    linklist p = head->next;
    while(p){
        if(p->info == key)
            break;
        p = p->next;
    }
    return p;
}

int main()
{
    linklist head,pos;
    int x;
    head= creatLink("data1.txt",N); /*从data1.txt文件中读入前N个数存入带头结点的单链表head*/
    print(head);                    /*当链表结点数非常大时，可选择注释本行*/
    printf("请输入要查找的整数：");
    scanf("%d",&x);
    pos=seqsearch(head,x);
    if (pos==NULL)
        printf("查找失败！\n");
    else
        printf("查找成功！%d\n",pos->info);
    delList(head);
}
