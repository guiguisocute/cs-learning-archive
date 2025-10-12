#include <stdio.h>
#include <stdlib.h>

int main(){
    float total_cola; int n;
    scanf("%f %d",&total_cola,&n);
    printf("%.3f \n", total_cola / n);
    printf("%d \n",n * 2);

    system("pause");
    return 0;
}