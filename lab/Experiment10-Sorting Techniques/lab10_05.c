/*
请设计筛选函数void sift(int a[],int k,int n)，对a[k] 进行筛选，
并利用其设计堆排序算法函数void heapSort(int a[],int n)，
对a[1]..a[n]进行升序排序。并测试在不同数据规模下的排序效率。（详见lab10_05.c）
*/
#include "Arrayio.h"
#include <time.h>
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/
//堆在现阶段可以简单理解成一个完全二叉树，除最后一层其他必须满，最后一层即使不满也必须要是连续的
//大根堆：任一节点都大于等于其左右孩子，小根堆就是反过来
//所以你明白了吧，既然完全二叉树，那么就可以用顺序结构从上到下从左到右存进数组里，不会造成空间的浪费：
//左孩子：2i，右孩子：2i+1，找父母就是除2向下取整 **这个是从下标1开始存的规律**
//本质利用堆顶是最大值or最小值去排序
//具体的实现是把一个数组看成一个逻辑上的完全二叉树，然后把这颗二叉树给大根堆化，最后输出的时候把根与最后的节点一一交换就可以了
//关键是要理解怎么堆化
void sift(int a[], int k, int n) // 参数：k = 需要调整的根下标；n = 当前堆最后一个元素下标。作用是在 确保 下面的节点已经堆化的情况，对于该处可能破坏堆结构的根节点，往下放，直到这颗完全二叉树能够大根堆化
{
      int i,j,finished;
      i=k;j=2*i;
      a[0]=a[k];
      finished=0;
      while((j<=n)&&(!finished))
      {
        if((j<n)&&(a[j+1]>a[j]))      //右孩子是否比左孩子大？
             j++;
        if(a[0]>=a[j])      //根是否都大于左右孩子？
             finished=1;    //结束了，因为确保了下面的二叉树已经堆化了
        else
        {
          a[i]=a[j];
          i=j;j=2*j;
        }
      }
      a[i]=a[0];
    }

void heapSort(int a[],int n)
{
    int i;
    for (i=n/2;i>=1;i--)    //从最下面开始建队，n/2是最后一个元素的父母
        sift(a,i,n);        //目的是把数组给堆化
    for (i=n;i>1;i--)
        {
            a[0]=a[i];    
            a[i]=a[1];
            a[1]=a[0];    //这个就是简单的交换，不要想太多
            sift(a,1,i-1);  //交换完成以后，把刚放下去的max从堆中去掉（i-1），然后再向下调整新上根的那个结点，把新的完全二叉树给堆化
        }
}

int  main()
{
  int a[N+1],n;                     /*数据存储在a[1]...a[N]中*/
  printf("数据初始化...\n");
  n=readData(a,N,"data1.txt");      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("%d个数据排序中...\n",n);
  clock_t beg = clock();
  heapSort(a, n);
  clock_t end = clock();
  saveData(a, n, "out.txt"); /*排序结果存放在out.txt文件中*/
  printf("排序结束，排序结果保存在out.txt文件中。\n");
  printf("n=%d,  time = %.3f ms\n",
         n, 1000.0 * (end - beg) / CLOCKS_PER_SEC);
  return 0;
}
