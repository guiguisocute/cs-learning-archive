#include<stdio.h>
#include<stdlib.h>

int main(){
    double l,a,b,c;
    scanf("%lf %lf %lf %lf",&l,&a,&b,&c);

    double t = l / (a + b);
    printf("%.4lf",t * c);

    system("pause");
    return 0;
}