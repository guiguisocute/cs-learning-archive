#include<stdio.h>
#include<stdlib.h>

int main(){
    long long int l,r,sum = 0;
    scanf("%lld %lld",&l,&r);

    for(long long int i = l; i <= r; i++){
        sum = (sum + i * (i + 1) % 998244353 * (i + 2) % 998244353) % 998244353;
    }
    printf("%lld",sum);

    system("pause");
    return 0;
}