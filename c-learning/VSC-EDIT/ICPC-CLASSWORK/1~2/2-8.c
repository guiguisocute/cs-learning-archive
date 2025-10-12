#include <stdio.h>
#include <stdlib.h>

int main(){
    float a,b,c;
    scanf("%f %f %f",&a,&b,&c);
    printf("%.0f \n",a * 0.2 + b * 0.3 + c * 0.5);

    system("pause");
    return 0;
}