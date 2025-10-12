/*
  请编写递归函数void bubbleSort(int a[],int n)，
  对长度为n的数组采用冒泡法进行升序排序。
  请编写递归函数int binSearch(int a[], int left, int right,int key)，
  采用二分查找法在数组a[left..right]中查找值为key的元素所在的位置，
  若查找失败函数返回-1。
  */ 

#include "ArrayIo.h"
#define N 10
/*请将本函数补充完整，并进行测试*/
void bubbleSort(int a[],int n)
{
    //首先要明白冒泡一轮的结果是什么————最大的已经跑去最右边去了，以此为初始递归契机，来想递归体写法，这个更像递归“正解”，体现出递归的如法炮制，不太需要逆向思考了
    if(n <= 1){
      return;
    }else{
      for(int i = 0; i < n - 1; i++){
        if(a[i] > a[i + 1])
          swap(i,i+1,a);
      } //一轮把最大值放右边
      bubbleSort(a,n - 1);
      //剩下的如法炮制
    }
    
}
int binSearch(int a[], int left,int right,int key)
{
  if(left > right){
    return - 1;     //终止条件
  }else{
    // 首先二分先找中点然后比较key与中点的大小这点用不用递归都不会变，先写上去
    int mid =left + (right - left) / 2;
    if (a[mid] == key){
      return mid;
    }

    if(key > a[mid]){
      // 右边找就行了
      return binSearch(a,mid + 1, right,key);
    }else{
      // 反之左边找就行
      return binSearch(a,left,mid - 1,key); 
    }
  }
}
int main()
{   int x,pos,a[N];
    init(a,N);
   	bubbleSort(a,N);
    print(a,N);
    printf("请输入要查找的数：\n");
    scanf("%d",&x);
    pos=binSearch(a,0,N-1,x);
    if (pos!=-1) printf("a[%d]=%d\n",pos,x);
    else printf("Not found!\n");
    return 0;
}
