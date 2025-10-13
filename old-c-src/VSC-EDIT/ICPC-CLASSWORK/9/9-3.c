#include<stdio.h>
#include<stdlib.h>

int a[30][30];
int main(){
    int n;
    scanf("%d",&n);

    for(int i = 1; i <= n; i++){
        a[i][1] == 1;
        for(int j = 1; j <= n; j++){
            if(j == i){
                a[i][j] = 1;
            }else{
                a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(a[i][j] == 0){
                printf(" ");
            }else{
                printf("%d ",a[i][j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}