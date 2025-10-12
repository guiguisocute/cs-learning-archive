/*
已知长度为n的线性表L采用顺序存储结构，编写一个复杂度为O(n)、
空间复杂度为O(1)的算法，该算法删除线性表中所有值为x的数据元素。
*/
/**********************************/
/*文件名称：lab1_06.c                 */
/**********************************/
#include "sequlist.h"
/*请将本函数补充完整，并进行测试*/
/*解法一：用k记录顺序表L中不等于x的元素个数（即需要保存的元素个数），
  边扫描L边统计k，并将不等于x的元素向前放在k位置上，最后修改L的长度。
  */
void delNode1(sequence_list *L,datatype x)
{
  int i,k = 0;
  for(i = 0;i < L->size;i++){
    if(L->a[i] != x){
      L->a[k] = L->a[i]; 
      k++;
    }
  }
  L->size = k;
}
/*
    解法二：用k记录顺序表L中等于x的元素个数，边扫描L边统计K，并将不等
    于x的元素前移k个位置，最后修改L的长度。
*/
void delNode2(sequence_list *L,datatype x)
{
    int i,k = 0;
    for(i = 0; i < L->size;i++){
      if(L->a[i] == x){
      k++;
      }else{
        L->a[i - k] = L->a[i];
      }
    }
    L->size = L->size - k;
}
int main()
{
  sequence_list L;
  int x;
  // input(&L);
  inputfromfile(&L,"3.txt");
  print(&L);  	/*输出表L*/
  printf("请输入要删除的数：");
  scanf("%d",&x);
  // delNode1(&L,x);			/*分别测试*/
  delNode2(&L,x);
  printf("删除%d后的顺序表为：\n",x);
  print(&L);  						/*输出新表*/
  return 0;
}
