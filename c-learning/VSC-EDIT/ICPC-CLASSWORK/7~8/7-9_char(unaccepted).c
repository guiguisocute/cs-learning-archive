#include<stdio.h>
#include<stdlib.h>

int main(){
    double a,b; int n;
    scanf("%lf %lf %d",&a,&b,&n);

    char str[10000];
    sprintf(str,"%.100000f",a / b);

    printf("%c",str[n + 1]);
    system("pause");
    return 0;
}