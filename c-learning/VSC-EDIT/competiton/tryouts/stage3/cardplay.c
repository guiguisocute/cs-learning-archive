#include<stdio.h>
#include<stdlib.h>

int main(){
    int t,n;
    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        int card[n + 1];
        for(int i = 1; i <= n; i++){
            scanf("%d",&card[i]);
        }
        if(n > 3){
            printf("2");
        }else{
            printf("0");
        }


    }

    system("pause");
    return 0;
}