/*
请编写一个递归算法函数void partion(int a[], int left, int right)，
将数组a[left..right]中的所有奇数调整到表的左边，所有偶数调整到表的右边。
*/
#include "ArrayIo.h" 
#define N 10
/*请将本函数补充完整，并进行测试*/
void partion(int a[], int left,int right)
{
    if(left >= right)  
        return;     //单值不用排(顺便也加了一点非法潘丹)
    if(left == right - 1){
        if(a[left] % 2 == 0) 
            swap(left,right,a);       //写完递归体就可以去想终止条件了，快碰一起的时候仅需要考虑偶奇情况交换就行,swap函数我写进头文件里去了
        return;
    }else{
        //就想着右指针不断往左边收缩，然后左边那群那堆因为递归早就排好了，这时候就只剩最右可能没分类好，右边是偶不动，右边是奇把元素放最前然后整体右移就可以了
        if(a[right] % 2 != 0){      
            int temp = a[right];    //全体右移,最后把原最右赋值给a[left]
            for(int i = right; i > left; i--){
                a[i] = a[i-1];
            }
            a[left] = temp;
            partion(a, left + 1, right); // 这里很关键！！虽然一开始是按照左边一坨排好来弄的，但是，两个数组块进行交换后，就变成右边那一坨排好了，代码也要随之改变
        }
        partion(a, left, right - 1);    //不变的话就按照原有的弄就行了
        }
}
int main()
{   int a[N];
    input(a,N);				/*随机产生N个数*/
    print(a,N);
    partion(a,0,N-1);
    print(a,N);
    return 0;
}
