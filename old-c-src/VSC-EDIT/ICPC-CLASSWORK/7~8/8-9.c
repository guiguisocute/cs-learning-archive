#include<stdio.h>
#include<stdlib.h>

int main(){
    int m,n;
    int count[10] = {0};
    scanf("%d %d",&m,&n);

    for(int i = m; i <= n; i++){
        int num = i;
        while(num > 0){
                count[num % 10]++;
                num /= 10;
            }
    }
    for(int i = 0; i < 10; i++){
            printf("%d",count[i]);
            if(i < 9){
                printf(" ");
            }
        }
             
        return 0;
}