#include<stdio.h>
int jiecheng(int n){
    if(n == 0) return 1;
    return (n * jiecheng(n - 1));
}

int main(){
    printf("%d",jiecheng(5));
}