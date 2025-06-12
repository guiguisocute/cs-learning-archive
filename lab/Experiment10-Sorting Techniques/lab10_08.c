/*
请设计归并排序算法函数void mergeSort(int a[],int n)，对a[1]..a[n]进行升序排序。
并测试在不同数据规模下的排序效率。
*/
#include "Arrayio.h"
#include <time.h>
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/

/*初始是n个子序列，然后两两归并，变成【n/2】（这里是向上取整了）个子序列，然后一直归并相同的子序列就完事了

排序轮数（指一整个数列达到一个子序列后需要多少轮）是Olog2n级别，单次归并又是ON

是一个稳定(最强稳定排序了)而且平均时间复杂度最低的排序方式，但也拥有最高的空间复杂度ON
*/

static int aux[N + 1];  //提前申请一个长度和待排序的数组一模一样的缓冲区，避免频繁地在函数内部里面申请与释放栈


/*将有序段a[u..m],a[m+1..v]归并到a[u..v]*/
void merge(int a[],int u,int m,int v)
{ 
  int i = u, j = m + 1, k = u;

  //把较小元素依次写进缓冲区
  while (i <= m && j <= v){
    if(a[i] <= a[j]){
      aux[k] = a[i];
      i++;
    }else{
      aux[k] = a[j];
      j++;
    }
    k++;
  }
    

  //把剩余元素直接追加
  while (i <= m){
    aux[k] = a[i];
    k++;
    i++;
  }
    
  while (j <= v){
    aux[k] = a[j];
    k++;
    j++;
  }
    

  //拷回原数组
  for (i = u; i <= v; ++i)
    a[i] = aux[i];
}

/*----一趟归并------*/
 void  mergepass(int a[],int n,int len)
  { /*对a[1..n]进行长度为len的一趟并归*/
    int i;
    for (i = 1; i + 2 * len - 1 <= n; i += 2 * len){    //如果下一段还是一套完整的len区间的话
      merge(a, i, i + len - 1, i + 2 * len - 1);
      }
      if (i + len - 1 < n)
      {
        merge(a, i, i + len - 1, n); // 处理一段半的尾巴,要么上面完美分完了，要么就像现在这样的一段半
      }
  }

/*----归并排序------*/
void mergeSort(int a[],int n)
{
  for (int len = 1; len < n; len *= 2) //长度变化是1,2,4,8……
    mergepass(a, n, len);
}

/*归并排序的递归实现*/
void mergeSortdc(int a[],int low,int high)
{
  if (low >= high)
    return;
  int mid = (low + high) / 2;
  mergeSortdc(a, low, mid);      //左半已经排好序
  mergeSortdc(a, mid + 1, high); //右半也已经排好序
  merge(a, low, mid, high);      //直接归并
}

int  main()
{
  int a[N+1],n;                     /*数据存储在a[1]...a[N]中*/
  printf("数据初始化...\n");
  n=readData(a,N,"data1.txt");      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("%d个数据排序中...\n",n);
  clock_t beg = clock();
  mergeSort(a,n);
  clock_t end = clock();            /* 或调用mergeSortdc(a,1,n); */
  saveData(a,n,"out.txt");          /*排序结果存放在out.txt文件中*/
  printf("排序结束，排序结果保存在out.txt文件中。\n");
  printf("n=%d,  time = %.3f ms\n",
         n, 1000.0 * (end - beg) / CLOCKS_PER_SEC);
  return 0;
}
