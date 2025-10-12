#include<stdio.h>
#include<stdlib.h>
#define lli long long int

int main(){
    int a,b,sum = 1;
    scanf("%d %d",&a,&b);

    for(int i = 0; i < b; i++){
        sum *= a;
        sum %= 1000;
    }
    printf("%03d",sum);

    system("pause");
    return 0;
}