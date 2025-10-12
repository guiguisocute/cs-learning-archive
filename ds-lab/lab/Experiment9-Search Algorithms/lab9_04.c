/*  利用readData()函数从data2.txt中读入不同规模的有序数据存入数组，
编写基于数组的二分查找递归算法。
*/
#include "ArrayIo.h"
#define N 10000          /*数据量*/
/*请将本函数补充完整，并进行测试*/
int binSearch(int a[],int low,int high,int key)
//可否理解折半查找判定树实质上是由这个演变的？，有点前序的感觉又有点中序的感觉
{
    if(low > high){
        return -1;
    }else{
        int mid = (high + low) / 2 ;       
        if (key == a[mid])
        {
            return mid;
        }
        if (key > a[mid])
        {
            return binSearch(a, mid + 1, high, key);
        }
        if (key < a[mid])
        {
            return binSearch(a, low, mid - 1, key);
        }
    }
    return -1;
}

int main()
{
    int a[N],n,x,pos;
    n=readData(a,N,"data2.txt"); /*从data2.txt文件中读入前N个数存入a中，函数返回成功读入的数据个数*/
    printf("请输入要查找的整数：");
    scanf("%d",&x);
    pos=binSearch(a,0,n-1,x);
    if (pos==-1)
        printf("查找失败");
    else
        printf("a[%d]=%d\n",pos,x);
}
