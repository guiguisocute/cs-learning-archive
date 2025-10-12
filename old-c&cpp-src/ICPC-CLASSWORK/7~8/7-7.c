#include<stdio.h>
#include<stdlib.h>
#define lli long long int

int main(){
    lli m,n;
    scanf("%lld %lld",&n,&m);

    lli base = n / m;
    lli remain = n % m;

    for(int i = 0; i < m - remain; i++){
        printf("%lld ",base);
    }
    for(int i = m - remain; i < m; i++){
        printf("%lld ",base + 1);
    }

    system("pause");
    return 0;
}