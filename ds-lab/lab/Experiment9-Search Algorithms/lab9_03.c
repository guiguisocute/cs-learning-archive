/*  利用readData()函数从data2.txt中读入不同规模的有序数据存入数组，
编写基于数组的二分查找算法，测试数据量为1万、5万、10万、20万、30万、
40万和50万时的数据查询时间。
*/
#include "ArrayIo.h"
#define N 10000          /*数据量*/
/*请将本函数补充完整，并进行测试*/
int binSearch(int a[],int n,int key)
{
    int left = 0, right = n -1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(a[mid] == key)
            return mid;
        else if(key > a[mid]){
            left = mid + 1;
        }
        else{
            right = mid - 1;
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
    pos=binSearch(a,n,x);
    if (pos==-1)
        printf("查找失败");
    else
        printf("a[%d]=%d\n",pos,x);
}
