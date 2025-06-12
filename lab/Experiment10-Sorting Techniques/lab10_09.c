/*
请设计基于链表的基数排序函数void radixSort(linklist head)，对带头结点的整型非负单链表进行升序排序。
并测试在不同数据规模下的排序效率。(注：链表中的最大整数为500000)
*/
#include "slnklist.h"
#include <time.h>
struct  node2
{
    linklist front,rear;
};
#define N 500000     /*N为数据量大小，因data1.txt中只有50万个数，所以自行设定N值时需让N<=500000*/

/*请将本函数补充完整，并进行测试*/

//基数排序是一种全程都不需要比较的**非比较排序**
/*
1. 基数就是十进制基数就是10，二进制基数就是2
2. 不知道教材里是LSD还是MSD，这里我默认是LSD了
3. 先找待排元素的最高位是哪个，然后把不够最高位的通过前导0补成最高位（其实也可以不加，按照表达式算出来就是0了，这里说这么多只是为了好理解些）
4. 然后按照基数去造对应数量的桶，把数（整体，不能单放个位）都放进桶里，这个桶的数据结构就是一个有着队尾指针的链表队列
5. 把队列里面的指针全部取出来，构成了一个新链表
6. 这样一来所有元素的个位都能按照顺序排好
7. 接着重复进队出队，直到最高位也操作完

基数排序（桶排序）的效率是最特殊的那个，毕竟他无须比较，所以它也比较稳定
为O（最高位*（n+桶数）），空间复杂度就是O（桶数）
适用于固定位数，且整数的数据结构
*/

void radixSort(linklist head)
{
  if (!head || !head->next)     //不知道写什么的话先写个空表返回逻辑吧，跟高中数学最后一道导数题先求导性质差不多
    return;

  // 首先是考虑前导0应该怎么添加？,总之数值上最大值肯定也有最大的基数，先找个最大值再说
  int max = 0;
  for(linklist p = head->next; p; p = p->next){
    if(p->info > max){
      max = p->info;
    }
  }
  struct node2 q[10]; /*队列*/ // 也是桶数

  for(int e = 1; max / e > 0; e *= 10)
  {     
    //e是基数从低位到高位依次入桶
    for(int i = 0; i < 10; i++){
      q[i].front = q[i].rear = NULL;      //桶的初始化
    }

    linklist p = head->next;

    while(p){
      linklist nextn = p->next;
      p->next = NULL;
      int digit = (p->info / e) % 10;  //经典求某位数字的表达式
      if(q[digit].front == NULL){
        q[digit].front = q[digit].rear = p;
      }
      else{
        q[digit].rear->next = p;
        q[digit].rear = p;
      }
      p = nextn;
    }
    linklist tail = head; //尾插法
    for (int i = 0; i < 10; i++)
    { 
      if (q[i].front != NULL)
      {                          // 如果当前桶不为空
        tail->next = q[i].front;
        tail = q[i].rear;
      }
    }
    tail->next = NULL; 
// 经过一轮分配和收集，链表已按当前位(e)有序
  }
}
int  main()
{
  linklist head;
  printf("数据初始化...\n");
  head=creatLink("data1.txt",N);      /*从data1.txt中读入N个整数存入数组a，n为实际读入的数据个数*/
  printf("数据排序中...\n");
  clock_t beg = clock();
  radixSort(head);
  clock_t end = clock();
  writetofile(head, "out.txt"); /*排序结果保存在out.txt中*/
  printf("time = %.3f ms\n",
         1000.0 * (end - beg) / CLOCKS_PER_SEC);
  delList(head);
  return 0;
}
