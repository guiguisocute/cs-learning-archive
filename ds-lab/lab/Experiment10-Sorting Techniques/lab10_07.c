/*
请设计快速排序算法函数void quickSort(int a[],int low,int right)，对a[low]..a[right]进行升序排序。
并测试在不同数据规模下的排序效率。
*/
#include "Arrayio.h"
#include <stdlib.h>
#include <time.h>
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/
//任取一个元素作为“枢轴”，建立left和right两个指针，划分成左边全小于枢轴，右边全大于枢轴
//然后递归处理左半区间和右半区间就行，直到空或者只剩一个
/*具体第一遍实现的方法就是：
取随机的元素作为枢轴（为了最大程度去避免最坏情况），和第一个元素作为交换，然后存进a[0]里，然后此时最左边就空出一个元素，从右边去一直往前找一个数比枢轴小的填上左边的坑然后填完了发现右边会有坑，此时再从左边开始找比枢轴大的填右边的坑直到l == r后把枢轴给填上去，第一遍就算划分好了，这个划分的操作复杂度是on
随后就是递归地去处理左右两个区间，这个最好情况是左右划分的一直很平均是log2n，最坏情况则是本身有序会一直做一颗很极端的树（很像二叉排序树的构建那种），退化成on，空间复杂度也同时会退化成on，这里空间复杂度主要是递归所产生的栈，和枢轴交换没有关系。
*/
int partition(int a[],int l, int r){      //划分的函数，返回值为枢轴划分好后所在的下标，可以使得快排代码更简洁些
  a[0] = a[l];
  while (l < r) // 只要左指针小于右指针，不断填坑挖坑直到l == r
  { 
    while(l < r && a[r] >= a[0]) r--;    //右指针移动的正常情况，右边大于枢轴，后者的条件判断保证了lr两指针永远不会交叉
    a[l] = a[r];  //只要跳出循环了，证明找到右边比枢轴小的元素，使得右边变到左边去, 因为此时a[0]已经存放好那个坑中原有的数了，所以不必担心被覆盖的问题
    while(l < r && a[l] <= a[0]) l++;   //同上
    a[r] = a[l];  
  }
  a[l] = a[0];
  return l;     //虽然这确实是一个int返回值的函数，但是他依然可以操纵指针啊，原数组中其实也把左边的树归位了
}

void quickSort(int a[],int low,int right )
{
  if(low >= right)
  { // 只有在区间长度大于1的时候才需要划分
    return;
  }
  int ran = low + rand() % (right - low + 1);
  a[0] = a[ran];
  a[ran] = a[low];
  a[low] = a[0];                        //生成随机位置的枢轴并交换到第一个
  
  int i = partition(a,low,right);
  quickSort(a,low,i - 1);
  quickSort(a,i + 1, right);

}

int  main()
{
  srand(time(NULL));
  int a[N+1],n;                     /*数据存储在a[1]...a[N]中*/
  printf("数据初始化...\n");
  n=readData(a,N,"data1.txt");      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("%d个数据排序中...\n",n);
  clock_t beg = clock();
  quickSort(a, 1, n);
  clock_t end = clock();
  saveData(a, n, "out.txt"); /*排序结果存放在out.txt文件中*/
  printf("排序结束，排序结果保存在out.txt文件中。\n");
  printf("n=%d,  time = %.3f ms\n",
         n, 1000.0 * (end - beg) / CLOCKS_PER_SEC);
  return 0;
}
