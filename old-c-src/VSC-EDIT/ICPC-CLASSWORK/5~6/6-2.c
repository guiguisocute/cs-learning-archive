#include<stdio.h>
#include<stdlib.h>

unsigned long long factorial(int n){
    unsigned long long result =1;
    for(int i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

int main(){
    unsigned long long num,s = 0;
    scanf("%llu",&num);

    for(int i = 1; i <= num; i++){
        s += factorial(i);
    }
    printf("%llu",s);

    system("pause");
    return 0;
}

