#include<stdio.h>
#include<stdlib.h>

int main(){
    int x; char type; int pre = 8;
    scanf("%d %c",&x,&type);

    if(x <= 1000){
    }else{
        pre = (((x - 1000)+ 500 - 1) / 500) * 4 + 8;
    }
    if(type == 'y'){
        printf("%d",pre + 5);
    }else{
        printf("%d",pre);
    }

    system("pause");
    return 0;
}