#include<stdio.h>
#include<stdlib.h>

int main(){
    int sum;
    int a[1000];
    for(int i = 0;i < 100; i++){
        scanf("%d",&a[i]);
        if(a[i] == 0){
        sum = i;
        break;
        }
    }

    for(int i = sum - 1; i >= 0; i--){
        printf("%d ",a[i]);
    }

    system("pause");
    return 0;
}