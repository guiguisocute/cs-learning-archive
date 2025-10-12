/*
假设二叉排序树t中所有的关键字是由整数构成的，为了查找某关键字k，会得到一个查找序列。
设计一个算法，判断一个序列（存放在数组a中）是否是从t中搜索关键字k的序列。
*/
#include "bstree.h"
#define N 100
/*
	函数find(t,k,a,n)的作用是判断数组a中的序列是否是从t中搜索关键字k的序列。请将函数补充完整。
*/
// 我寻思这不就是射箭再画靶子吗，先把找k所产生的序列输出出来然后一一比对不就行了，还是说这两个能同步进行？确实这种方法实在有点低级，但是会平白无故多增添时间空间复杂度，所以我们还是好好想想边搜索边比对的方法吧：
// 一边沿 BST 往下走，一边检查当前结点值是否与 a[i] 一致；一旦不一致就返回 0
int find(bstree t, int k, int a[], int n)
{
    int i = 0; 

    while (t && i < n)
    {
        if (t->key != a[i]) //不一样直接返回0
            return 0;

        if (k == t->key)
            break;

        if (k < t->key)
            t = t->lchild;
        else
            t = t->rchild;

        i++;
    }
    return (i == n - 1);        //这里验证是否完全走完了整个数组
}

int  main()
  {
    int k,a[N],n,i;
    bstree t;
    t=creatBstree();         /*创建二叉排序树*/
    printf("请输入k的值：");
    scanf("%d",&k);
    printf("请输入数组a的元素个数：\n");
    scanf("%d",&n);
    printf("请输入%d个数组元素的值：\n",n);
    for (i=0;i<n;i++)
        scanf("%d",a+i);

    if (find(t,k,a,n)==1)
        printf("\n数组a为查找%d的搜索序列！\n",k);
    else
        printf("\n数组a不是查找%d的搜索序列！\n",k);
    return 0;
 }
