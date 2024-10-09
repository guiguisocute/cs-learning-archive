#include<stdio.h>
#include<stdlib.h>

int main(){
    int k;
    scanf("%d",&k);
    int n = 1;
    double sum = 1;

    while(sum <= k){
        sum += 1.0 / (n + 1.0);
        n++;
    }

    printf("%d",n);

    system("pause");
    return 0;
    }