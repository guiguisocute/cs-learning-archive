#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define ll long long
//将 n 转换为以 k 为底的数

int main(){
    int t;
    scanf("%d",&t);
    ll n,k;

    while(t--){
        scanf("%lld %lld",&n,&k);

        if(k == 1){
            printf("%lld\n",n);
        }else{
            int count = 0;
            while (n > 0){
                count += n % k;
                n /= k;
            }
            printf("%d\n",count);
        }

    }

    return 0;
}