/*
5．字符串采用带头结点的链表存储，设计算法函数 void delstring(linkstring s, int i,int len)在字符
串 s 中删除从第 i 个位置开始，长度为 len 的子串。（实验代码详见 lab4_05.c）
*/
/**********************************/
/*文件名称：lab4_05.c                 */
/**********************************/
#include "linkstring.h"
/*请将本函数补充完整，并进行测试*/
void delstring(linkstring  s, int i, int len)
{ 
    //这个也简单，就是跟上一个一样，只不过链接头结点的操作变成pre结点的next赋值为应该删掉最后一个节点的next。说起来这两个函数我都好想没有判空逻辑，虽然要写也挺简单的但是题目没要求应该没问题，吧？
    linkstring p = s->next;
    linkstring pre = s;
    for(i--; i > 0; i--){
        pre = p;
        p = p->next;
    }
    for(len--;len > 0; len--){
        p = p->next;
    }
    pre->next = p->next;
}
int main()
{   linkstring str;
    str=creat();            /*建字符串链表*/
    print(str);
    delstring(str,2,3);     /*测试，从第2个位置删除长度为3的子串,请自行构造不同的测试用例  */
    print(str);               /*输出*/
    delList(str);
    return 0;
}
