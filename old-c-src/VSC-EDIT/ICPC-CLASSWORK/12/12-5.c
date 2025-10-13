#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int max(int n){
    int max = -1;
    while(n % 2 == 0){
        max = 2;
        n /= 2;
    }
    for(int factor = 3; factor * factor <= n; factor+=2){
        while(n % factor == 0){
            max = factor;
            n /= factor;
        }
    }
    if(n > 2){
        max = n;
    }

    return max;
}

int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    
    for(int i = a; i <= b; i++){
        printf("%d",max(i));
        if(i != b){
            printf(",");
        }
    }
    return 0;
}