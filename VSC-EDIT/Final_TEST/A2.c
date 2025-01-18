#include<stdio.h>

int main(){
    double sum = 0;
    for(int i = 0; i <= 100; i++){
        sum += (1.0/(1.0 + 5.0 * i));
    }
    printf("%lf",sum);
    return 0;
}