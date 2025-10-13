#include<stdio.h>
#include<stdlib.h>

int main(){
    long long int x,n,p;
    scanf("%lld %lld %lld", &x, &n, &p);

    long long two_result = (1LL << n) % (p - 1);
    long long int result = 1;
    
    for(long long int i = 0; i < two_result; i++){
        result =(result * x) % p;
    }

    printf("%lld\n", result);
    
    system("pause");
    return 0;
}