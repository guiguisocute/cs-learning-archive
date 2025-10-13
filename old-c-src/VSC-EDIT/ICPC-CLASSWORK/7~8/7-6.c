#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,temp;
    scanf("%d",&n);
    
    while(n !=1){
        if(n % 2 == 0){
            temp = n;
            n /= 2;
            printf("%d/2=%d\n",temp,n);
        }else{
            temp = n;
            n = n * 3 + 1;
            printf("%d*3+1=%d\n",temp,n);
        }
    }
    printf("Done");

    system("pause");
    return 0;
}