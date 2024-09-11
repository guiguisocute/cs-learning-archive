#include<stdio.h>
#include<stdlib.h>

int main(){
    int q;
    scanf("%d",&q);
    if(5 * q < 11 + (3 * q)){
        printf("Local");

        system("pause");
        return 0;
    }
    else{
        printf("Luogu");

        system("pause");
        return 0;        
    }
}