/*
6．字符串采用带头结点的链表存储，编写函数 linkstring index(linkstring s, linkstring t)，查找子
串 t 在主串 s 中第一次出现的位置，若匹配不成功，则返回 NULL。（实验代码详见 lab4_06.c）
*/

#include "linkstring.h"
/*请将本函数补充完整，并进行测试*/
linkstring index(linkstring s, linkstring t)
{
    // 很容易想到暴力，就是主链每一个节点我都不管三七二十一遍历所有子串，子串全匹配就返回主链指针不全匹配才下一个，等一会这个返回输出值是不是有问题啊，感觉再说废话只要找到了那肯定是子串第一个元素啊，真要偷懒的话直接print子串第一个元素不就行了x，我还是输出第几个节点吧嗨呀，要不然显得努力很蠢
    if(t->next == NULL)
    return NULL;

    linkstring p_s = s->next;
    char count = '1';

    while(p_s){
        linkstring current_s = p_s;
        linkstring p_t = t->next;
        while (current_s && p_t && current_s->data == p_t->data){
            current_s = current_s->next;
            p_t = p_t->next;
        }
        if(p_t == NULL){
            p_s->data = count;
            return p_s;
        }
        p_s = p_s->next;
        count++;
    }
    return NULL;
}

linkstring index_fail(linkstring s, linkstring t)
{
    // 这是我一开始想了很久On的函数，但是没考虑到子串为完全匹配主链指针还要走回去的情况，可以说白忙活了
    linkstring result = NULL;
    if (t->next == NULL)
        return result;

    linkstring p_s = s->next;
    linkstring p_t = t->next;
    char count = '1', flag;

    while (p_s)
    {
        if (!p_t)
        {
            result->data = flag;
            return result;
        }

        if (p_t->data == p_s->data)
        {
            if (p_t == t->next)
            { // 如果pt是首元结点
                flag = count;
                result = p_s; // 那就让result变成主链当前指针
            }
            p_t = p_t->next;
        }
        else
        {
            p_t = t->next;
            result = NULL;
        }
        p_s = p_s->next;
        count++;
    }
    return result;
}


int main()
{
    linkstring s, t, p = NULL;
    s = creat(); /*建立主串链表*/
    t = creat(); /*建立子串链表*/
    print(s);
    print(t);
    p = index(s, t);
    if (p)
    printf("匹配成功，首次匹配成功的位置结点位置在第%c个", p->data);
    else
    printf("匹配不成功！\n");
    delList(s);
    delList(t);
    return 0;
}