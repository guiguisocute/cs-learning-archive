#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 3; 
    for (int i = 0; i < n; i++){
        for (int j = n - 1; j > i; j--){
            printf(" ");
        }
          for (int k = 0; k < 2 * i + 1; k++){
        printf("*");
          }
     printf("\n");
    }
    //上半部分


    for (int i = n - 2; i >= 0; i--){
        for (int j = n - 1; j > i; j--){
            printf(" ");
        }
    for (int k = 0; k < 2 * i + 1; k++){
        printf("*");
    }
     printf("\n");
    }
    //下半部分
    system("pause");
    return 0;
}