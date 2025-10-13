#include<stdio.h>
#include<stdlib.h>

int main(){
    double s; double v = 2; int step = 0;
    scanf("%lf",&s);

    if(s <= 2){
        printf("1");

        system("pause");
        return 0;
    }
    for(;;){
        s -= v;
        v *= 0.98;
        step++;
        if(s <= 0){
            break;
        }
    }
    printf("%d",step);

    system("pause");
    return 0;
}