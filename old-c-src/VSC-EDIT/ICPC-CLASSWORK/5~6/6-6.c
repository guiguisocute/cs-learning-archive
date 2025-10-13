#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);

    int num = 1;
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%02d",num);
            num++;
        }
        printf("\n");
    }
    printf("\n");
    num = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (n - i - 1) * 2; j++){
            printf(" ");
        }
        for(int j = 0; j <= i; j++){
            printf("%02d",num);
            num++;
        }
        printf("\n");
    }

    system("pause");
    return 0;
}