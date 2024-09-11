#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    float p; float o;
    scanf("%f %f",&p,&o);
    printf("%.0f",round((p * o / 10) / 10) * 10);

    system("pause");
    return 0;
}