#include<stdio.h>
#include<stdlib.h>
#define lli long long int

int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    int square = 0;
    for (int i = 1; i <= n && i <= m; i++){
        square += (n - i + 1) * (m - i + 1);
    }

    lli rec = ( (lli)m * ( m + 1) / 2) * ( (lli)n * (n + 1) / 2 ) - square;
    
    printf("%d %lld",square,rec);

    system("pause");
    return 0;
}