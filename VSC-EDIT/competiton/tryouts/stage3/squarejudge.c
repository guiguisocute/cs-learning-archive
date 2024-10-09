#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define lli long long int
#define EPS 1e-9

int main(){
    lli x;
    scanf("%lld",&x);
    lli a =(lli)(sqrt((4.0 * x) / sqrt(3.0)) + 0.5);


    if(fabs(sqrt(x) - (lli)sqrt(x)) < EPS && fabs((sqrt(3.0) / 4 * (a * a)) - x) < EPS){
        printf("2");
    }else if(fabs(sqrt(x) - (lli)sqrt(x)) < EPS){
        printf("0");
    }else if(fabs((sqrt(3.0) / 4 * (a * a)) - x) < EPS){
        printf("1");
    }else{
        printf("3");
    }

    system("pause");
    return 0;
}