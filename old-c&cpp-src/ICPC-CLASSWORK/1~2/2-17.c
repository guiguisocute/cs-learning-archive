#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14

int main(){
    float r,h;
    scanf("%f %f",&h, &r);
    float vol = r * r * PI * h;
    printf("%.0f",ceil(20 * 1000 / vol));

    system("pause");
    return 0;
}