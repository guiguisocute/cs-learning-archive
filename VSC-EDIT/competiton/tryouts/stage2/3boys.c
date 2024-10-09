#include<stdio.h>
#include<stdlib.h>

int main(){
    int a,b;
    scanf("%d %d",&a,&b);

    if((a == 1 && b ==2) || (a == 2 && b ==1)){
        printf("3");
    }else if((a == 3 && b ==1) || (a == 1 && b ==3)){
        printf("2");
    }else{
        printf("1");
    }

    system("pause");
    return 0;
}