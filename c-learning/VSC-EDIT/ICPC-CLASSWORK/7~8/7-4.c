#include<stdio.h>
#include<stdlib.h>

int isprime(int n){
    if (n == 1) return 0;
    for(int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(){
    int l,sum = 0,count = 0;
    scanf("%d",&l);

    for(int i = 2; i < l; i++){
        if(isprime(i)){
            sum += i;
        }
        if(isprime(i) && sum <= l){
            printf("%d\n",i);
            count++;
        }
        
    }
    printf("%d",count);

    system("pause");
    return 0;

}