/*
请设计简单选择排序算法函数void selectSort(int a[],int n)，对a[1]..a[n]进行升序排序。
并测试在不同数据规模下的排序效率。
*/
#include "Arrayio.h"
#include <time.h>
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/
//不稳定而且无论最好最坏都是On2的排序，虽然最好写但也是最飞舞的算法，可以说除了教学没人会用这个算法了
void selectSort(int a[],int n)
{
  for(int i = 1; i <= n; i++){
    //不会写选择排序的CS学生真可以请哈吉高了
    int j,min_idx = i,min = a[i];
    for(j = i + 1; j <= n; j++){
      if(a[j] < min){
        min_idx = j;
        min = a[j];
      }
    }
    a[0] = a[i];
    a[i] = a[min_idx];
    a[min_idx] = a[0];    //简简单单swap一下
    
  }
}

int  main()
{
  int a[N+1],n;                     /*数据存储在a[1]...a[N]中*/
  printf("数据初始化...\n");
  n=readData(a,N,"data1.txt");      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("%d个数据排序中...\n",n);
  clock_t beg = clock();
  selectSort(a,n);
  clock_t end = clock();
  saveData(a,n,"out.txt");          /*排序结果存放在out.txt文件中*/
  printf("排序结束，排序结果保存在out.txt文件中。\n");
  printf("n=%d,  time = %.3f ms\n",
         n, 1000.0 * (end - beg) / CLOCKS_PER_SEC);
  return 0;
}
