#include<stdio.h>
#include<stdlib.h>

long long int fibo(int n){
    if(n == 1 || n == 2){
        return 1;
    }else{
        return fibo(n - 1) % 4294967296 + fibo(n -2) % 4294967296;
    }
    
}
int main(){
    int n;
    scanf("%d",&n);

    long long int fn = fibo(n);
    long long x = fn;
    printf("%lld",x);

    system("pause");
    return 0;   
}