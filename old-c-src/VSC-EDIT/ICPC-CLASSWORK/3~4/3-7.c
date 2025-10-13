#include<stdio.h>
#include<stdlib.h>

int main(){
    int kwh;
    scanf("%d",&kwh);

    if(kwh >= 150){
    printf("%.1f",kwh >= 400 ? 150 * 0.4463 + 250 * 0.4663 + (kwh - 400) * 0.5663 : 150 * 0.4463 + (kwh - 150) * 0.4663);
    }else{
        printf("%.1f",kwh * 0.4463);
    }
    system("pause");
    return 0;
}