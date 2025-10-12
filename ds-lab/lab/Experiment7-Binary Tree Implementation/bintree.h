#include <stdio.h>
#include <stdlib.h>
#define N 100 
extern char *a;     /*存放扩充二叉树的前序序列*/
// ·extern· ：用于声明外部变量，避免重复定义并说明变量已在别处分配存储。相当于告诉编译器“变量 a 在别的地方已被定义，这里只是引用它，不要再分配存储

typedef struct node /*二叉树结构定义*/
{
    char data;
    struct node *lchild,*rchild;
}binnode;
typedef binnode *bintree;

/*函数creatbintree (根据扩充二叉树的前序序列(字符串a)建立二叉树t的存储结构*/
bintree  creatbintree()
{
    char ch=*a++;
    bintree t;
    if  (ch=='#')  t=NULL;  //这点也是比较重要的
    else
    { t=(bintree)malloc(sizeof(binnode));
      t->data=ch;
      t->lchild=creatbintree();
      t->rchild=creatbintree();
    }
    return t;
}

void preorder(bintree t)  /*前序递归遍历二叉树*/
{
    if (t)
    {
        printf("%c",t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}
void postorder(bintree t)  /*后序递归遍历二叉树*/
{
    if (t)
    {

        postorder(t->lchild);
        postorder(t->rchild);
        printf("%c",t->data);
    }
}

/*顺序栈定义*/
typedef struct
{
    bintree data[N];    //这里存着一堆树结点
    int top;
    int tag[N]; // 具体来说，tag[i] 对应着栈中 data[i] 所指向的那棵子树的遍历状态,用于需要多次检查同一节点状态的算法
}seqstack;

void init(seqstack *s)   /*初始化空栈*/
{
    s->top=-1;
}
int empty(seqstack *s)   /*判断栈是否为空*/
{
    if (s->top>-1) return 0;
    else return 1;
}
int full(seqstack *s)   /*判断栈是否为满*/
{
    if (s->top==N-1) return 1;
    else return 0;
}
void push(seqstack *s ,bintree x)   /*进栈*/
{
    if (!full(s))
        s->data[++s->top]=x;
}
bintree pop(seqstack *s)			/*出栈*/
{
    if (!empty(s))
        return s->data[s->top--];
    return NULL;
}
