#include<stdio.h>

unsigned long long jiecheng (int n){
    if(n == 1 || n == 0){
        return 1;
    }
    return n * jiecheng(n-1);
}

int main(){
    int n;
    scanf("%d",&n);

    printf("%llu",jiecheng(n));
}