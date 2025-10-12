#include<stdio.h>
#include<stdlib.h>

int main(){
    double pifen4 = 0;
    int count = 0;
    int i = 1;
    int flag = 1;
    while(((double)(1.0 / i)) >= 0.000001){
        if(flag == 1){
            pifen4 += (double)(1.0 / i);
        }else{
            pifen4 -= (double)(1.0 / i);
        }
        count++;
        flag = flag ^ 1;
        i = i + 2;
    }

    printf("%lf %d",pifen4 * 4,count);
    return 0;
}