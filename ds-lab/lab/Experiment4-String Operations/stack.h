/*字符栈的结构定义及其操作实现*/
#define seqstacksize  100      /*栈的最大空间大小*/
typedef char datatype; 
typedef struct stack {
    datatype  data[seqstacksize] ;  /*向量data用于存储栈数据*/
    int  top;                       /*栈顶指示*/
}seqstack;

void initstack(seqstack *s)         /*栈初始化*/
{ s->top=-1;
}

int stackempty (seqstack *s)        /*判栈空*/
{ return s->top==-1;
}
int stackfull(seqstack *s)          /*判栈满*/
{return s->top==seqstacksize-1;
}
/*进栈*/
void push(seqstack *s, datatype x)
  { s->data[++s->top]=x;      //s->top是一个整体……弄完了top再++
  }
/*出栈*/
datatype pop(seqstack *s)
{ return s->data[s->top--];
}
/*取栈顶元*/
datatype stacktop(seqstack *s)
{ return s->data[s->top];
}
