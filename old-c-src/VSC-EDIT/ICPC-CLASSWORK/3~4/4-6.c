#include<stdio.h>
#include<stdlib.h>

int main(){
    double m;
    scanf("%lf",&m);

    const double epsilon = 1e-6;
    double sum[2];
    sum[0] = 27 + 23 + m / 3;
    sum[1] = m / 1.2;
    if(sum[0] < sum[1]){
        printf("Bike");

        system("pause");
        return 0;
    }
    else if(sum[0] > sum[1]){
        printf("Walk");

        system("pause");
        return 0;
    }
    else{
        printf("All");

        system("pause");
        return 0;
    }

    }




