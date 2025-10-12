#include <stdlib.h>
#include <stdio.h>
 /*思路：每一个节点互相比如果不等于零插入，如果等于0则free，有点像归并那题这样合成*/
typedef struct node {
    int coef;        /*系数*/
    int expn;        /*指数*/
    struct node *next;
} listnode;        //多项式存储结构

typedef listnode *linklist;
void delList(linklist head);

 /*
 函数名称： creat()
 函数功能：建立多项式存储结构，并且多项式在表中按所在项的指数递增存放
 */
linklist creat()            //建立多项式存储结构，
{
    linklist head,s,p,pre;   
    int coef;
    int expn;
    head = (linklist)malloc(sizeof(listnode));    /*生成头结点*/
    head->next=NULL;
    printf("请输入多项式，每一项只需输入系数，指数(当输入的系数为0时结束输入,但还需要再输入指数)：\n");
    scanf("%d",&coef);         //输入系数
    scanf("%d",&expn);        //输入指数

    while (coef!=0)       //请在此处填上适当的代码
    {
      s = (linklist)malloc(sizeof(listnode)); //每次重新申请一个空间
      s->coef = coef;
      s->expn = expn;
      s->next = NULL;   //把值赋进去先

      //再看一下未排序的列中expn的大小，选择合适的位置链入
      pre = head;
      p = head->next;
      //查找插入位置
      while(p && p->expn < s->expn){
        pre = p;
        p = p->next;
      }
      pre->next = s;
      s->next = p;
      scanf("%d",&coef);         //输入系数
      scanf("%d",&expn);        //输入指数
    }
    return head;
}

void print(linklist head) //输出多项式
{
    linklist p;
    p=head->next;
    while (p) {
        printf("%d(X)",p->coef);
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
    linklist pa,pb,c,r,s;
    c = (linklist)malloc(sizeof(listnode));
    c->next = NULL;   //啥也不说先创造头结点
    r = c;

    pa = a->next;
    pb = b->next;
    //以下while为类似归并操作
    while(pa && pb){
      if(pa->expn > pb->expn){
        s = pb;
        pb = pb->next;
        s->next = NULL;
        r->next = s;
        r = s;
      }else if(pa->expn < pb->expn){
        s = pa;
        pa = pa->next;
        s->next = NULL;
        r->next = s;
        r = s;
      }else if(pa->expn == pb->expn){
        s = pa;
        s->coef = pa->coef + pb->coef;
        s->expn = pa->expn;
        pa = pa->next;
        pb = pb->next;
        s->next = NULL;
        r->next = s;
        r = s;
      }
    }
    while(pa){
        s = pa;
        pa = pa->next;
        r->next = s;
        s->next = NULL;
        r = s;
      }
    while(pb){
        s = pb;
        pb = pb->next;
        r->next = s;
        s->next = NULL;
        r = s;
      }
      return c;
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
{
    linklist p=head;
    while (p) {
        head=p->next;
        free(p);
        p=head;
    }
}
