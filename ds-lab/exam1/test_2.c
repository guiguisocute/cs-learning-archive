#include "linklist.h"

/*函数getword的功能是将字符串s中的单词分离出来(单词之间
可以有一个或多个空格分隔)，分离出的单词采用链表的方式存
储在w[]的每一行，函数返回单词的个数*/
int  getword(linklist w[],char  *s)
//一个字符串，然后链表和之前定义的一样，用字符串指针去跑一遍，遇到空格直接往下走新建链表就行，正好形参上本身就给了链表数组了(题目里默认大小是80)而且全部null化了，提示得还算比较明显了,注意还要返回单词个数，其实就是w链表非空数量
{
    int s_p = 0;     //字符串指针
    int w_p = 0;        //链表指针
    linklist temp,rear;     //rear指向整个链表数组的最后一个字符
    while(s[s_p] != '\0'){
        if(s[s_p] != ' '){
            if(w[w_p] == NULL){
                w[w_p] = (linklist)malloc(sizeof(linknode)); 
                w[w_p]->data = s[s_p];
                w[w_p]->next = NULL;
                rear = w[w_p];
            }else{  //往w_p位置的链表加字符（尾插）
                temp = (linklist)malloc(sizeof(linknode));
                temp->data = s[s_p];
                temp->next = NULL;
                rear->next = temp;
                rear = temp;
                
            }
        }
        else if(s[s_p] == ' ' && s[s_p + 1] != '\0'){
            if(w[w_p] != NULL){
                w_p++;
            }
        }
        s_p++;
    }
    if(w[w_p] == NULL){
        return w_p;     //防一下没东西的情况
    }else{
        return w_p + 1;
    }


}

int main()
//好像main函数里没有检查返回值的操作？
{       char  *s="College of Computer Information and Engineering";
        char  *t=" Hello!     My   is     name Tony.";
        int i,n;
        linklist ws[80]={NULL};
        linklist wt[80]={NULL};

        n=getword(ws,s); 	//分离出字符串s中的所有单词

        for (i=0;i<n;i++)   	//输出所有单词
            print(ws[i]);

        n=getword(wt,t);	//分离出字符串t中的所有单词
        for (i=0;i<n;i++)   	//输出所有单词
            print(wt[i]);

        for (i=0;i<n;i++)   	//释放所有单词链表
            delList(ws[i]);
        for (i=0;i<n;i++)   	//释放所有单词链表
            delList(wt[i]);
         return 0;
}
