#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,k;
    int sumA = 0,sumB = 0;
    int countA = 0,countB = 0;
    scanf("%d %d",&n,&k);

    for(int i = 1; i <= n; i++){
        if(i % k == 0){         //能被整除，A类数
            countA++;
            sumA+=i;
        }
    }
    printf("%.1f ",(float)sumA / countA);
    for(int i = 1; i <= n; i++){
        if(i % k != 0){         //不能被整除，B类数
            countB++;
            sumB+=i;
        }
    }
    printf("%.1f ",(float)sumB / countB);


    system("pause");
    return 0;

}