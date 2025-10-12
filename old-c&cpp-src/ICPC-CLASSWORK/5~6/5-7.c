#include<stdio.h>
#include<stdlib.h>

int main(){
    long long int a1,a2,n;
    scanf("%lld %lld %lld",&a1,&a2,&n);

    printf("%lld",a1 * n + (n*(n - 1)) / 2 * (a2 - a1) );

    system("pause");
    return 0;
}