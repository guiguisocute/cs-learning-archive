/*
假设二叉树采用二叉链表存储结构，设计一个算法，
求非空二叉树中指定的某一层lev（lev>=1）的叶子结点个数。
*/

#include "bintree.h"
char *a="ABD##EH##I##CF##G##";  			/*扩充二叉树序树t的前序序列*/
typedef struct{
    bintree qu[N];      //保存队列中的结点
    int level[N];       //保存queue中对应位置处结点的层次
    int f,r;            //队列首尾指示
}seqQueue;

/*
    函数totalLeaf(t,lev)用于统计二叉树t中第lev层的叶子结点个数，请将本函数补充完整
*/

/*有没有发现特别眼熟？没错，这一题一样可以用上一题完全一致的思路去做，传参，队列都给你了不用干嘛？
而且其实更简单不用去维护max了，只用一直出队出到对应的层号，然后做个判断没有左右孩子，让计数器自增最后返回就行了，看我直接CV
*/
int totalLeaf(bintree t,int lev)
{
    {
        if (t == NULL)
            return 0;

        seqQueue a;
        a.f = 0;
        a.r = 0;
        a.qu[a.r] = t;
        a.level[a.r] = 1;
        a.r++;
        int count = 0; // 记得数组初始化，要不然全是随机值
        // 队列初始化

        while (a.f < a.r)
        {
            bintree u = a.qu[a.f];
            int lvl = a.level[a.f];
            if(lvl == lev && !u->lchild && !u->rchild)
                count++;
                
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
        return count;
    }
}
int main()
{
    bintree t;
    int lev,counter;
    t=creatbintree();   	/*建立二叉树t的存储结构*/
    printf("二叉树的前序序列为：\n");
    preorder(t);
    printf("\n请输入层号：");
    scanf("%d",&lev);
    counter=totalLeaf(t,lev);
    printf("%d层上共有%d个叶子结点。\n",lev,counter);
    return 0;
}
