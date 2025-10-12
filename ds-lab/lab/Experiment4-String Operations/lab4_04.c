/*
4．已知字符串采用带结点的链式存储结构（详见 linkstring.h 文件），请编写函数 linkstring
substring(linkstring s,int i,int len)函数，在字符串 s 中从第 i 个位置起取长度为 len 的子串，函数返回子串链表。（实验代码详见 lab4_04.c）
*/

#include "linkstring.h"
/*请将本函数补充完整，并进行测试*/
linkstring substring(linkstring  s, int i, int len)
{
    //都已经建好链表了，只需要一直遍历到对应位置然后尾插就行了
    linkstring p = s->next;
    for(i--;i > 0; i--){
        p = p->next;
    }
    s->next = p;
    for(len--;len > 0; len--){
        p = p->next;
    }
    p->next = NULL;
    return s;
}
int main()
{   linkstring str1,str2;
    str1=creat();                  /*建字符串链表*/
    print(str1);
    str2=substring(str1,3,5);    /*测试，从第3个位置开始取长度为5的子串,请自行构造不同测试用例*/
    print(str2);                   /*输出子串*/
    delList(str1);
    delList(str2);
    return 0;
}
