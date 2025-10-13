#include<stdio.h>
#include<stdlib.h>

int main(){
    int k,per = 1,sum = 0,day = 0;
    scanf("%d",&k);

    while(day < k){
        for(int i = 0; i < per && day < k; i++){
            sum += per;
            day++;
        }
        per++;
    }

    printf("%d",sum);

    system("pause");
    return 0;
}