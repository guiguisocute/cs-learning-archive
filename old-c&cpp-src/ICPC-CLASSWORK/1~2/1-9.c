#include <stdio.h>
#include <stdlib.h>
#define PI 3.141593

int main(){
    double r = 5;
    printf("%.4f \n", r * PI * 2);
    printf("%.4f \n", PI * r * r);
    printf("%.3f \n", (4.0 / 3.0) * PI * r * r * r);

    system("pause");
    return 0;
}