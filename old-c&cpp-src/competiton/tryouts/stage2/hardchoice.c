#include<stdio.h>
#include<stdlib.h>

int main(){
    int t;
    scanf("%d",&t);
    int x[t],y[t];
    for(int i = 0; i < t; i++){
        scanf("%d %d",&x[i],&y[i]);
    }

    int sum_l = 0,sum_f = 0;
    for(int i = 0; i < t; i++){
        if(x[i]){
            sum_l += y[i];
        }else{
            sum_f += y[i];
        }
    }
    if(sum_f >= sum_l){
        printf("0 %d",sum_f);
    }else{
        printf("1 %d",sum_l);
    }

    system("pause");
    return 0;
}