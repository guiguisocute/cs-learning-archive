#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);

    for(int i = 1; i <= n; i++){
        for(int space = 1; space <= n - i; space++){
            printf("            ");
        }

        for(int j = i; j >= 1; j--){
            printf("%3d*%3d=%3d",i,j,i * j);
            if(j > 1){
                printf(" ");
            }
        }
        printf("\n");
    }

    system("pause");
    return 0;
}