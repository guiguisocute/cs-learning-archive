#include<stdio.h>
#include<stdlib.h>

int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    if(a + b == c && a - b ==c){
        printf("all right");

        system("pause");
        return 0;
    }

    if(a + b == c){
        printf("plus");
    }else if(a - b == c){
        printf("minus");
    }else{
        printf("all wrong");
    }

    system("pause");
    return 0;
}