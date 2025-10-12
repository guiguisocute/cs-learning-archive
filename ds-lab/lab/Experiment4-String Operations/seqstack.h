#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100 
typedef int datatype;
typedef struct
{       datatype  a[MAXSIZE];
        int top;
}seqstack;
/**********************************/
/*函数名称：init()		 		*/
/*函数功能：初始化空栈             */
/**********************************/
void init(seqstack *st)
{
    st->top=0;
}
/**********************************/
/*函数名称：empty()		 	       */
/*函数功能：判断栈是否为空        */
/**********************************/
int empty(seqstack *st)
{
    return st->top?0:1;
}
/**********************************/
/*函数名称：read()	 			     */
/*函数功能：读栈顶元                    */
/**********************************/
datatype read(seqstack *st)
{   if (empty(st))
        {  printf("\n栈的空的！＼n");exit(1);
        }
    else
        return st->a[st->top-1];
}
/**********************************/
/*函数名称：push()	 			     */
/*函数功能：进栈                        */
/**********************************/
void push(seqstack *st,datatype x)
{   if (st->top==MAXSIZE)
    {
        printf("栈满，无法进栈！\n");
        exit(1);
    }
    st->a[st->top]=x;
    st->top++;
}
/**********************************/
/*函数名称：pop()	 			     */
/*函数功能：出栈                        */
/**********************************/
datatype  pop(seqstack *st)
{   if (st->top==0)
        {   printf("\n顺序栈是空的!\n");
            exit(1);
        }
    return st->a[--st->top];
}
