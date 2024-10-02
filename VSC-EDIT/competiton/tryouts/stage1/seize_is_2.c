#include<stdio.h>
#include<stdlib.h>

int prime(int n){
    if (n == 1) return 0;
    for(int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(){
    int t;
    scanf("%d",&t);

    int s[t];
    for(int i = 0; i < t; i++){
        scanf("%d",&s[i]);
    }

    for(int i = 0; i < t; i++){
        if(prime(s[i])){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }

    system("pause");
    return 0;

}