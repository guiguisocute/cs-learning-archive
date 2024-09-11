#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    float n,a,b,c,a_p,b_p,c_p;
    scanf("%f",&n);
    scanf("%f %f",&a,&a_p);
    scanf("%f %f",&b,&b_p);
    scanf("%f %f",&c,&c_p);

    int sum[3];
    sum[0] = ceil(n / a) * a_p;
    sum[1] = ceil(n / b) * b_p;
    sum[2] = ceil(n / c) * c_p;
    int min = 2147483647;
    for(int i = 0; i < 3; i++){
        if(sum[i] < min){
            min = sum[i];
        }
    }
    printf("%d",min);
    system("pause");
    return 0;
}