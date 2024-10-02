#include<stdio.h>
#include<stdlib.h>

int fibo(int n){
    if(n == 1 || n == 2){
        return 1;
    }else{
        return fibo(n - 1) + fibo(n -2);
    }
    
}
int main(){
    int n;
    scanf("%d",&n);

    int fn = fibo(n);
    int x = fn %= 4294967296;
    printf("%d",x);

    system("pause");
    return 0;   
}