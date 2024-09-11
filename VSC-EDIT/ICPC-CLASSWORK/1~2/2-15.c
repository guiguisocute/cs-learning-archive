#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    double a,b,c;
    scanf("%lf %lf %lf",&a,&b,&c);
    double p = (a + b + c) / 2.0;
    printf("%.1lf",sqrt(p * (p - a) * (p - b) * (p - c)));

    system("pause");
    return 0;
}