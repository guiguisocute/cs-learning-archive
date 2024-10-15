#include<stdio.h>
#include<stdlib.h>

int main(){
    int t,n;
    scanf("%d",&t);
    
    while(t--){
        scanf("%d",&n);
        int count[10] = {0};

        for(int i = 0; i <= n; i++){
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
        printf("\n");     
        }

        return 0;
}