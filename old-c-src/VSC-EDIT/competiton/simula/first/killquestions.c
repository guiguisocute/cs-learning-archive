#include<stdio.h>
#include<stdlib.h>

int main(){
    long long int a,b,n,count = 0,workday = 1,total = 0;
    scanf("%lld %lld %lld",&a,&b,&n);

    while(total < n){
        if(workday == 6 || workday == 7){
            total += b;
            
        }else{
            total += a;
        }
        count++; workday++;
        if(workday > 7){
                workday = 1;
            }
    }
    printf("%lld",count);

    system("pause");
    return 0;
}