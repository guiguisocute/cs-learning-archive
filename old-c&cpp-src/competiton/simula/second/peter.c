#include <stdio.h>
#include <stdlib.h>

int main(){
    long long int n,k,new = 0;
    scanf("%lld %lld",&n,&k);
    long long int sum = n;
    long long int butt = n;

    while(butt >= k){
        long long int new = butt / k;
        sum += new;
        butt = butt % k + new;
    }
    printf("%lld",sum);

    system("pause");
    return 0;
}