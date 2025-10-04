#include "linklist.h"
// 学生结构定义见linklist.h头文件，完成下面的函数。
// 一个多数据域，带头结点的单链表而已，就正常写就可以了

//统计每位学生的总分
void sum( linklist head)        //20分
//都有数据域了直接拿个指针遍历然后加起来就行了
{
    if(head == NULL || head->next == NULL)
    {
        return;
    }
    linklist p = head->next;        //
    while(p){
        p->total = p->chinese + p->english + p->math;
        p = p->next;
    }

}

//删除表中总分大于low，小于high的学生信息
//删掉原表总分，而且还要把删掉的链表给弄回来，我现在才懂了这个意思，好险没交得太早
//并将删除后的结点生成一个新链表返回
linklist del(linklist head, int low,int high)       //40分
//和上面函数一样都是一个遍历搞定，多加一个指针的事
//好像搞错了，这个得弄一个新链表，差点不符合题目要求了，好吓人还好看了一下main
{
    // 创建一个带头结点的新链表用于存储删除的节点
    linklist new = (linklist)malloc(sizeof(Node));
    new->next = NULL;
    
    if(head == NULL || head->next == NULL)
    {
        return new;
    }

    linklist p = head->next;
    linklist pre = head;
    linklist rear = new;  //新链表就用尾插法

    while(p){
        if(p->total > low && p->total < high){
            //从原链表删除并加入新链表
            pre->next = p->next;
            p->next = NULL;
            rear->next = p;
            rear = p;
            p = pre->next;
        } else {
            pre = p;
            p = p->next;
        }
    }

    return new;
}
//按总分由高到低排序
void sort(linklist head)        //40分
//就是很标准的链表重新断开后的头插排序，按照标准流程写就行了
{
    if(head == NULL || head->next == NULL){
        return;
    }
        

    linklist sorted = NULL;  //一个无头结点的新链表
    linklist p = head->next; 
    head->next = NULL;

    // 遍历原链表的所有节点
    while(p != NULL)
    {
        linklist next = p->next; //防止next走丢

        if(sorted == NULL || sorted->total < p->total)//首位处理
        {
            p->next = sorted;
            sorted = p;
        }
        else
        {
            // 在新链表中找到合适的位置头插
            linklist q = sorted;
            while(q->next != NULL && q->next->total >= p->total)
            {
                q = q->next;
            }
            p->next = q->next;
            q->next = p;
        }

        p = next;
    }

    head->next = sorted;
}

int main()
{
    linklist  head,h;
    head=inputData("data.txt");
    printList(head);
    sum(head);
    printList(head);
    sort(head);
    printf("按总分排序：\n");
    printList(head);
    h=del(head,240,260);
    printf("删除总分大于240分，小于260的学生信息：\n");
    printList(head);
    printList(h);               
    return 0;
}
