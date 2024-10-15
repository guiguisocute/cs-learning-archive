#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);


    int a[n][n];
    int index = 0;          //index是一维的线性索引, 如果我们要表示第i行第 j列的元素，那么它的位置可以用 index =i x N +i来表示。
    int fill = 0;

    while(index < n * n){
        int count;
        scanf("%d",&count);
        for(int j = 0; j < count; j++){
            a[index / n][index % n] = fill;         //
            index++;
        }
        fill ^= 1;
    }
        
        
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d",a[i][j]);
        }
        printf("\n");
    }

    return 0;
}