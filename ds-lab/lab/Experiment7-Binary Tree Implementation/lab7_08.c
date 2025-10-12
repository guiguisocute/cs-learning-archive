/*
假设二叉树采用二叉链表存储结构，设计一个算法，求非空二叉树t的宽度（即具有结点数最多的那一层的结点个数）。
*/

#include "bintree.h"
char *a="ABD##EH##I##CF##G##";  			/*扩充二叉树序树t的前序序列*/

typedef struct{
    bintree qu[N];        //保存队列中的结点
    int level[N];           //保存queue中对应位置处结点的层次
    int f,r;                      //队列首尾指示
}seqQueue;

/*
    函数bintreeWidth(t)用于计算二叉树t的宽度，请将本函数补充完整
*/
//揭老师都帮我建立了队列结构体了，还有这种好事.jpg？思路简简单单，先进队根，层次标成是1，然后循环队非空的话，先放*队首*的儿子们，儿子们的level等于队首level+1，再出队（前提是得有）层数加一，然后同时维护一个count数组和一个max变量，边建立边更新(每次进循环最开始的时候检查一下)，return max就结束了
int bintreeWidth(bintree t)
{
    if (t == NULL)
        return 0;

    seqQueue a;
    a.f = 0;
    a.r = 0;
    a.qu[a.r] = t;
    a.level[a.r] = 1;
    a.r++;
    int count[N] = {0};     //记得数组初始化，要不然全是随机值
    count[0] = -1;
    int max = 0;
    //队列初始化


    while(a.f < a.r){
        bintree u = a.qu[a.f];
        int lvl = a.level[a.f];
        count[lvl]++;
        if(count[lvl] > max)
            max = count[lvl];   //更新max

        if (u->lchild && a.r < N)
        { // 队首有孩子就进队

            a.qu[a.r] = u->lchild;
            a.level[a.r] = lvl + 1;
            a.r++;
        }
        if (u->rchild && a.r < N)
        { // 队首有孩子就进队

            a.qu[a.r] = u->rchild;
            a.level[a.r] = lvl + 1;
            a.r++;
        }
        a.f++;
    }
    return max;

}
int main()
{
    bintree t;
    int width;
    t=creatbintree();   	/*建立二叉树t的存储结构*/

    width=bintreeWidth(t);
    printf("树的宽度为：%d\n",width);

    return 0;
}
