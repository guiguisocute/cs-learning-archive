#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
/*对长度为n的整型数组作输入*/
void input( int a[],int n)
{   int i;
   printf("请输入 %d 个整数：\n",n);
   for (i=0;i<n;i++)
      scanf("%d",&a[i]);
}
/*输出长度为n的整型数组*/
void print(int a[ ],int n)
{  int i;
   printf("\n数组的内容是：\n");
   for (i=0;i<n;i++)
     { if (i%10==0) printf("\n");
	   printf("%6d",a[i]);
     }
  printf("\n");
}
void init(int a[],int n)
{	int i;
   srand(time(NULL)); // time函数返回从 1970年1月1日起至今的秒数，srand起到一个种子设定器的作用，如果不使用 time() 设置随机数种子，而是直接使用 rand()，那么每次运行程序时都会生成相同的随机数序列
   for (i=0;i<n;i++)
      a[i] = rand() % 1000; // 通过取模运算将范围限制在 0-999
}

void swap(int l,int r,int a[]){    //数组交换函数
   int temp;
   temp = a[l];
   a[l] = a[r];
   a[r] = temp;
}
