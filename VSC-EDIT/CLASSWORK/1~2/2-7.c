#include <stdio.h>
#include <stdlib.h>

int main(){
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d); int total_min = (c * 60 + d) - (a * 60 + b);
    printf("%d %d", total_min / 60, total_min - total_min / 60 * 60);

    system("pause");
    return 0;
}