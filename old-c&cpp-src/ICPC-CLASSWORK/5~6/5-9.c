#include<stdio.h>
#include<stdlib.h>

int main(){
    int n; int d = 10;
    scanf("%d",&n);

    int sigh = (n < 0)? -1 : 1;
    n = abs(n);

    int re = 0;
    while(n > 0){
        re = re * 10 + n % 10;
        n /= 10;
    }
    re *= sigh;
    printf("%d",re);

    system("pause");
    return 0;
    
    

}