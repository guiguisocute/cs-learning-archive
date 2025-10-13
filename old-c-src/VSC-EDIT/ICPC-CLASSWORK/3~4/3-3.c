#include<stdio.h>
#include<stdlib.h>

int main(){
    int x;
    scanf("%d",&x);
    if(x % 2 == 0 && x > 4 && x <= 12 ){
        printf("1 ");
    }
    else{
        printf("0 ");
    }
    if (x % 2 == 0 || (x > 4 && x <= 12)) {
        printf("1 ");
    } 
    else {
        printf("0 ");
    }
    if ((x % 2 == 0) ^ (x > 4 && x <= 12)) {
        printf("1 ");
    }
    else {
        printf("0 ");
    }
    if(!(x % 2 == 0 || (x > 4 && x <= 12))){
        printf("1 ");
    }
    else{
        printf("0 ");
    }

    system("pause");
    return 0;
}