#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100 
typedef int datatype;
typedef struct node
{
        datatype data;
        struct node *next;
}linknode;

typedef linknode * linkstack;
/**********************************/
/*函数名称：init()		 		*/
/*函数功能：初始化空栈             */
/**********************************/
linkstack init()
{
     return NULL;
}
/**********************************/
/*函数名称：empty()		 	       */
/*函数功能：判断栈是否为空        */
/**********************************/
int empty(linkstack  top)
{
     return top?0:1;
}
/**********************************/
/*函数名称：read()	 			     */
/*函数功能：读栈顶元                    */
/**********************************/
datatype read(linkstack top)
{
    if (empty(top))
        {
            printf("\n栈的空的！＼n");exit(1);
        }
    else
        return top->data;
}
/**********************************/
/*函数名称：push()	 			     */
/*函数功能：进栈                        */
/**********************************/
linkstack push(linkstack top,datatype x)
{
    linkstack p;
    p=(linkstack)malloc(sizeof(linknode));
    p->data=x;

    p->next=top;
    top=p;
    return top;
}
/**********************************/
/*函数名称：pop()	 			     */
/*函数功能：出栈                        */
/**********************************/
linkstack  pop(linkstack top)
{
     linkstack p;
    if (empty(top))
        {
            printf("\n顺序栈是空的!\n");
            exit(1);
        }
    p=top;
    top=top->next;
    free(p);
    return top;
}
