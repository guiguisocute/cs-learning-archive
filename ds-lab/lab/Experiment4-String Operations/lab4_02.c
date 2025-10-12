/*
2．基于链式栈存储结构重新实现栈的基本操作，并基于链式栈改写十进制到十六进制的转换程序。
（实验代码详见 lab4_02.c）
*/
/*文件名称：lab4_02.c                 */
/**********************************/
#include "linkstack.h"
/*请将本函数补充完整，并进行测试*/
void Dto16(unsigned int m)
{
    linkstack s;    //一个链表的节点指针，非常平平无奇的链表结点
    s=init();   //初始指向空
    printf("十进制数%u对应的十六进制数是：",m);
    while (m)       //这个是存栈程序，每次除16就把余数放进链表里，很显然应该头插,push函数就是一种头插捏
    {
        s = push(s,m % 16);     //TMD之前忘记更新指针了，这个函数不是void啊……
        m /= 16;
    }
    while (!empty(s))
               {
                putchar((read(s) < 10 ? read(s) + '0' : read(s) + '7'));    //先读再弹出来
                s = pop(s);     //同第十六行
               }
    printf("\n");
}


int main()
{
        unsigned int m;
        printf("请输入待转换的十进制数：\n");
        scanf("%u",&m);
        Dto16(m);
        return 0;
}

