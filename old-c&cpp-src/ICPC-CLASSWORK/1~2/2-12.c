#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double a = 1, b = -100, c = 2400;
    double delat = b * b - 4 * a * c;
    double t = round(((-b + sqrt(delat))/(2 * a)));
    printf("%.0f",110 - t);

    system("pause");
    return 0;
}