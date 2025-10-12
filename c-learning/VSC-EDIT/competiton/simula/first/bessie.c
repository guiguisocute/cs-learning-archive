#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,result = 0;
    scanf("%d",&n);
    while(n != 1){
        if(n % 2 == 0){
            n = n / 2;
        }else{
            n = n * 3 +1;
        }
        result++;
    }
    printf("%d",result);

    system("pause");
    return 0;
}