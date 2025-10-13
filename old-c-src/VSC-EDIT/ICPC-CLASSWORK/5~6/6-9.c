#include<stdio.h>
#include<stdlib.h>

int main(){
    int n; double max,min,sum = 0;
    scanf("%d",&n);
    double a[n];
    for(int i = 0; i < n; i++){
        scanf("%lf",&a[i]);
    }
    max = a[0]; min = a[0];

    for(int i = 1; i < n; i++){
        if(a[i] > max){
            max = a[i];
        }
        if(a[i] < min){
            min = a[i];
        }
    }

    if(max == min){
        printf("%.2lf",a[0]);
    }else{
        for(int i = 0; i < n; i++){
            sum += a[i];
        }
        sum = sum - max - min;
        double ave = sum / (n - 2);
        printf("%.2lf",ave);
    }

            
    system("pause");
    return 0;
}