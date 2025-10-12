#include<stdio.h>

int main(){
    int a[7];
    int max = -1;
    int min = 101;
    int sum = 0;
    for(int i = 0; i < 7; i++){
        scanf("%d",&a[i]);
        if(a[i] > max){
            max = a[i];
        }
        if(a[i] < min){
            min = a[i];
        }
        sum += a[i];
    }
    sum = sum - max - min;

    float aver = sum / 5.0;
    printf("%.3f",aver);
    return 0;
}