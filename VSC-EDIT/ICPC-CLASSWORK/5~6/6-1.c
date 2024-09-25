#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,i = 1,k = 1;      //i行号，k数字
    scanf("%d",&n);

    while(n > 0){
        int count = 0;
        while(count < n){
            printf("%02d",k);
            k++;
            count++;
        }
        printf("\n");
        n--;

    }

    system("pause");
    return 0;

}