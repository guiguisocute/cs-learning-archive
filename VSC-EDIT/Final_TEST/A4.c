#include<stdio.h>
int isprime(int n){
    if(n == 1)return 0;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return 0;
    }
    return 1;
}


int main(){
    int count = 0;
    for(int i = 1000; i <= 2000; i++){
        if(isprime(i)){
            printf("%d ",i);
            count++;
            if(count % 10 == 0 && count != 0){
                printf("\n");
            }
        }
    }
    printf("\n");
    printf("%d",count);
    return 0;
}