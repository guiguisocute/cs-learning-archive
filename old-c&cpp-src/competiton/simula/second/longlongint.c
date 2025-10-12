#include <stdio.h>
#include <stdlib.h>

int main(){
    long long int x,y;
    scanf("%lld %lld",&x,&y);

    if(x * y > 2147483647 || x * y < -2147483647){
        printf("long long int");
    }else{
        printf("int");
    }

    system("pause");
    return 0;


}