/*
设有n(n>1)个整数存放到顺序表L中。试设计一个时间和空间两方面
尽可能高效的算法，将顺序表中整数序列循环左移p(0<p<n)个位置，
即将L中的数据序列（X0,X1,…,Xn-1）变换为（Xp,Xp+1,…,Xn-1,X0,X1,…,Xp-1）。
*/
#include "sequlist.h"
void reverse(sequence_list *L,int left,int right);//辅助函数reverse()，实现顺序表L->a[left..right]进行首尾倒置。
/*
    解法1：函数leftShift1()的功能是实现顺序表循环左移p位，请根据提示将该函数补充完整。
*/
void leftShift1(sequence_list *L,int p)
{
    if (p>0 && p<L->size)
    {
        reverse(L,0,L->size-1);                   //将顺序表L的全部数据倒置
        reverse(L,0,L->size-p-1);                  //将顺序表L的前n-p个元素倒置
        reverse(L,L->size-p,L->size-1);//将顺序表L的后p个元素倒置
    }
}
/*
    解法2:函数leftShift2()的功能是实现顺序表循环左移p位，请根据提示将该函数补充完整。
*/
void leftShift2(sequence_list *L,int p)
{
    if (p>0 && p<L->size)
    {
         reverse(L,0,p - 1);                       //将顺序表L的前p个元素倒置
         reverse(L,p,L->size - 1);                       //将顺序表L的后n-p个元素倒置
         reverse(L,0,L->size - 1);                       //将顺序表L全部元素倒置
    }
}
//辅助函数reverse()，实现顺序表L->a[left..right]进行首尾倒置。
void reverse(sequence_list *L,int left,int right)
{
    int i=left,j=right,temp;
    while(i<j)
    {
        temp=L->a[i];
        L->a[i]=L->a[j];
        L->a[j]=temp;
        i++;
        j--;
    }
}
int main()
{
  sequence_list L;
  int p;
//   input(&L);
  inputfromfile(&L,"3.txt");
  printf("线性表为：\n",p);
  print(&L);  	/*输出表L*/
  printf("请输入循环左移的位数：");
  scanf("%d",&p);
//   leftShift1(&L,p);             //测试方法1
  leftShift2(&L,p);       //测试方法2
  printf("循环左移%d位后的线性表为：\n",p);
  print(&L);  						/*输出新表*/
  return 0;
}
