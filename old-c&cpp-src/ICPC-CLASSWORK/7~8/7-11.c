#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,x,k;
    scanf("%d",&n);

    for(int i = 1; i <= 100; i++){
        for(int j = 100; j >=1; j--){
            if((i * 7 + j * 21) * 52 == n){
                x = i;
                k = j;
            }
        }
    }

    printf("%d\n%d",x,k);
    
    system("pause");
    return 0;
}