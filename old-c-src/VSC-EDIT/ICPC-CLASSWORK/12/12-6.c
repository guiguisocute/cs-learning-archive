#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int isprimepluse(int n) {
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) return 0;
    }
    int reversed = 0;

    while(n != 0){
        int digit = n % 10;
        reversed = reversed * 10 + digit;
        n /= 10; 
    }

    for(int i = 2; i * i <= reversed; i++) {
        if(reversed % i == 0) return 0;
    }

    return 1;
}
int main(){
    int m,n;
    int ans[2500] = {0};
    int j = 0;
    scanf("%d %d",&m,&n);
    for(int i = m; i <= n; i++){
        if(isprimepluse(i)){
            ans[j] = i;
            j++;
        }
    }
    if(ans[0] == 0){
        printf("No");
    }else{
        for(int i = 0; i <= 2500 ; i++){
            if(ans[i] == 0){
                break;
            }
            printf("%d",ans[i]);
            if(ans[i+1] != 0){
                printf(",");
            }
        }
    }

    return 0;
}