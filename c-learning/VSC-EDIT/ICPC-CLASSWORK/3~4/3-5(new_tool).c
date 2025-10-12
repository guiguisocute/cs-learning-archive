#include<stdio.h>
#include<stdlib.h>

int main(){
    int x;
    scanf("%d",&x);

    int by3 = (x % 3 == 0);
    int by5 = (x % 5 == 0);
    int by7 = (x % 7 == 0);
    int count = by3 + by5 + by7;

    if(count == 0){
        printf("n");
    }else{
        if(by3)printf("3 ");
        if(by5)printf("5 ");
        if(by7)printf("7 ");
    }
    printf("\n");

    system("pause");
    return 0;
}