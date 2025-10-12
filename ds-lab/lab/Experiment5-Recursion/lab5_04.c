/*
已知带头结点的单链表结构定义同实验3，假设链表中所有结点值均不相同，
请编写一个递归函数linklist max(linklist head)，返回表中最大数所在的结点地址，若链表为空，返回NULL。
*/
 

#include "slnklist.h"
/*请将本函数补充完整，并进行测试*/
linklist max(linklist head)
{
    //核心思路就是和lab1一样的调用同型函数的逆向思维，除了首节点以外其他的都已经，找好max了，然后return这两个之间最大的那个就可以了
    linklist p = head->next;
    if(!p){
        return NULL; // 空表判断
    }
    if(!p->next){
        // 这下应该稍微有点熟练度可以直接写终止条件了，就是当p下一个结点没了，直接返回p就行
        return p;
    }
        linklist temp_max = max(p);
        return (p->info > temp_max->info) ? p : temp_max;   

    //一开始有个bad code smell，我偷懒没设置tempmax,后来得知这个不太好，因为会导致栈的浪费……
}

int main()
{   linklist head,p;
    head=creatbyqueue();
    print(head);
    p=max(head);
    if (p)
        printf("max=%d\n",p->info);
    else
        printf("链表为空\n");
    return 0;
}
