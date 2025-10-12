/*
请设计直接插入排序算法函数void insertSort(int a[],int n)，对a[1]..a[n]进行升序排序。
并测试在不同数据规模下的排序效率。
*/
#include "Arrayio.h"
#include <time.h>
//为了对比一下时间问了LM要了个测试函数，看一下数据量对ON2算法的影响
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/
void insertSort(int a[],int n)
/*
  直接插入排序
  依次将后面每个元素插入到前面有序的部分（有序区）
  而直接插入排序这个“直接”
  教案里的缓冲区好像是用下标0当作temp的（正确说法应该叫什么，哨兵？）
  只有当temp比有序区元素小的时候，数据元素才需要进行移动，temp也需要继续比较，大了直接插在后面就行了
*/
{   
  for(int i = 2; i <= n; i++){

    int j = i - 1; //有序区下标
    a[0] = a[i];

    while (a[0] < a[j]) //右移，直到找到插入点
    {
      a[j + 1] = a[j];
      j--; //这里会把j减到0，temp正好挡在a[0]
    }
    a[j + 1] = a[0];
  }
}

int  main()
{
  int a[N+1],n;                     /*数据存储在a[1]...a[N]中*/
  printf("数据初始化...\n");
  n = readData(a,N,"data1.txt");      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("%d个数据排序中...\n",n);
  clock_t beg = clock();
  insertSort(a,n);
  clock_t end = clock();
  saveData(a,n,"out.txt");          /*排序结果存放在out.txt文件中*/
  printf("排序结束，排序结果保存在out.txt文件中。\n");
  printf("n=%d,  time = %.3f ms\n",
         n, 1000.0 * (end - beg) / CLOCKS_PER_SEC);
  return 0;
}
