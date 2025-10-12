/*
请设计二分插入排序算法函数void binInsertSort(int a[],int n)，对a[1]..a[n]进行升序排序。
并测试在不同数据规模下的排序效率。
*/
#include "Arrayio.h"
#include <time.h>
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/
//二分插入排序本质上是利用了简单插入排序中，有序区“有序”的性质，把有序区做一个二分查找，之前简单查找用的是一个一个比，不过这次的二分不能提前结束，而是要一直比到l > r时，才能严格保证稳定，而此时的l指向的位置就是应该插入的位置
void binInsertSort(int a[],int n)
{
  for(int i = 2; i <= n; i++){
    a[0] = a[i];
    int left = 1, right = i - 1;
    if(a[i] >= a[right])
      continue;         //不知道这个操作能不能降一点时间复杂度

    while(right >= left){       //还没找到的情况，里面做二分直到找到了, 别用递归写了，递归还得再整个函数栈多麻烦，别苦了编译器了
      int mid = (right + left) / 2;
      if(a[0] >= a[mid]){
        left = mid + 1;
      }else{
        right = mid - 1;
      }

    }
    for(int j = i - 1; j >= left; j--){
      a[j + 1] = a[j];
    }
    a[left] = a[0];
  }
}
//二分插入找的效率是log2n级别，可惜还是给元素 移动 拖了后腿，导致整体的复杂度仍然是on2，属于非常经典的白忙活了

int  main()
{
  int a[N+1],n;                     /*数据存储在a[1]...a[N]中*/
  printf("数据初始化...\n");
  n=readData(a,N,"data1.txt");      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("%d个数据排序中...\n",n);
  clock_t beg = clock();
  binInsertSort(a, n);
  clock_t end = clock();
  saveData(a, n, "out.txt"); /*排序结果存放在out.txt文件中*/
  printf("排序结束，排序结果保存在out.txt文件中。\n");
  printf("n=%d,  time = %.3f ms\n",
         n, 1000.0 * (end - beg) / CLOCKS_PER_SEC);
  return 0;
}
