#include<stdio.h>
#include<stdlib.h>
#define lli long long int

lli fibo(int n){
    if(n == 1 || n == 2){
        return 1;
    }else{
        return fibo(n - 1) % 4294967296 + fibo(n -2) % 4294967296;
    }
    
}

int main(){
    int n;
    scanf("%d",&n);
    lli a[n];
    for(int i = 0; i < n; i++){
        scanf("%lld",&a[i]);
    }

    for(int i = 0; i < n; i++){
        printf("%lld\n",fibo(a[i]));
    }

    system("pause");
    return 0;
}