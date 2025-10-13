#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, l, r;
    scanf("%d %d %d", &n, &l, &r);
    if(1 / n == r / n){
        printf("%d",r % n);
        }else{
            printf("%d",n-1);
        }

        system("pause");
        return 0;
}
