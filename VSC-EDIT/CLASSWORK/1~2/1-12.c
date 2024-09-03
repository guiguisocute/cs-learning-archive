//感觉题干表述好奇怪,谁能想到有初始题量啊……
#include <stdio.h>
#include <stdlib.h>

int main(){
    double per_min = (8 * 30-10 * 6) / 24.0;
    printf("%.0f \n", (10.0 * per_min + (10 * 6 - 6 * per_min ))/10.0);

    system("pause");
    return 0;


}