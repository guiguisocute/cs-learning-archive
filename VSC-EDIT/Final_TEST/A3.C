#include<stdio.h>

int isshui(int a){
    if(((a % 10) * (a % 10) * (a % 10) + (a / 10 % 10) * (a / 10 % 10) * (a / 10 % 10) + (a / 100) * (a / 100) * (a / 100)) == a){
        return 1;
    }else
    return 0;
}

int main(){
    for(int i = 100; i <= 999; i++){
        if(isshui(i)){
            printf("%d\n",i);
        }
    }
    return 0;
}