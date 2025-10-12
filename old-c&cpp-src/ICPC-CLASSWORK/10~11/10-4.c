#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int prime(int n){
    if (n == 0) return 0;
    if (n == 1) return 0;
    for(int i = 2; i * i <= n; i++){
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(){
    char a[101];
    int count[26] = {0};
    scanf("%s",a);

    for(int i = 0; i < strlen(a); i++){
        count[a[i] - 'a']++;
    }

    int maxn = 0, minn = 100;
    for(int i = 0; i < 26; i++){
        if(count[i] > 0){
            if(count[i] > maxn) maxn = count[i];
            if(count[i] < minn) minn = count[i];
        }
        
    }

    int diff = maxn - minn;
    if(prime(diff)){
        printf("Lucky Word\n%d",diff);
    }else{
        printf("No Answer\n0");
    }

    return 0;
}