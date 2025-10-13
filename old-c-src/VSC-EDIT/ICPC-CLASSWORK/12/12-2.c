#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int is_prime(int n){
    if (n == 1) return 0;
    for(int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    for(int i = 0; i < n; i++){
        if(is_prime(a[i])){
            printf("%d",a[i]);
            if(i != n - 1){
                printf(" ");
            }
        }
    }
    
    return 0;
}

