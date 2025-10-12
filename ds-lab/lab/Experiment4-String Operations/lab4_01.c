/*
1．已知顺序栈存储结构及基本操作已定义（详见 seqstack.h 文件），利用顺序栈结构，编写算法
函数 void Dto16(unsigned int m)实现十进制无符号整数 m 到十六进制数的转换。（实验代码详见
lab4_01.c）
*/
/**********************************/
#include "seqstack.h"
/*请将本函数补充完整，并进行测试*/
void Dto16(unsigned int m)
{   seqstack s;			/*定义顺序栈*/  //这是一个结构体哈，和链表结点有点类似的首先定义了一组容量为100的数组然后里面再记录了top值()
    init(&s);   //使top值为0
    printf("十进制数%u对应的十六进制数是：",m);        //数电讲过，十进制转其他进制核心算法就是除16然后取余数倒着来
    while (m)
    {
        push(&s,m % 16);
        m /= 16;
    }

    while (!empty(&s)){
        int t = pop(&s);
            //A到F的ASCII码 65~70, 0~9 ASCII码：48~57 （但好像不用计直接+‘0’ + '7'就完事了……）
        putchar((t < 10 ? t + '0' : t + '7'));     //就是用来输出单个字符的
        }
        printf("\n");
    }

int main()
{    int m;
     printf("请输入待转换的十进制数：\n");
     scanf("%u",&m);
     Dto16(m);
     return 0;
}
