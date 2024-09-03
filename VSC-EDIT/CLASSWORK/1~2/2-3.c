#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159

int main(){
    double r_s = 4; double r_l = 10;
    printf("%.0f \n",cbrt((4.0 / 3.0) * r_s * r_s * r_s * PI + (4.0 / 3.0) * r_l * r_l * r_l * PI));
    
    system("pause");
    return 0;
}