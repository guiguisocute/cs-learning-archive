/*  利用readData()函数从data1.txt中读入不同规模的数据存入数组，
编写基于数组的顺序查找算法，测试数据量为1万、5万、10万、20万、
30万、40万和50万时的数据查询时间。
*/

#include "ArrayIo.h"
#include <time.h>   
#define N 2000000          /*数据量*/
int a[N];
/*请将本函数补充完整，并进行测试*/
int seqsearch(int a[],int n,int key)
//返回的是这整个数组的下标，data1文件里好像是有5w行*10列，所以只读前1000列？
{
    //顺序表就是一个一个找，纯遍历就完事了,但题目要求的查询时间，用手掐表好像也太不CS了，必须要整个
    int i = 0;
    int result = -1;
    while(i < n){
        if(a[i] == key){
            result = i;
            break;
        }
        i++;
    }
    return result;
}

int main()
{
    srand(time(NULL));
    int n,x,pos;
    n=readData(a,N,"data1.txt"); /*从data1.txt文件中读入前N个数存入a中，函数返回成功读入的数据个数*/
    printf("请输入要查找的整数：（若需随机生成请输入-1）(保证找到)\n");
    scanf("%d",&x);
    if(x == -1){
        x = a[rand() % N];
    }
    clock_t start, end;
    start = clock();
    pos = seqsearch(a, n, x);
    end = clock();
    double timeused = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    if (pos==-1)
        printf("查找失败");
    else{
        printf("a[%d]=%d\n", pos, x);
        printf("数据量为%d时，查询时间为: %lf", N, timeused);
    }

}
