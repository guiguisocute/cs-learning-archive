#include<stdio.h>
#include<stdlib.h>

int main(){
    long long int x,y;
    scanf("%lld %lld",&x,&y);
    if(x == y){
        printf("=");

        system("pause");
        return 0;
    }else if(x > y){
        printf(">");

        system("pause");
        return 0;
    }else{
        printf("<");

        system("pause");
        return 0;
    }
}