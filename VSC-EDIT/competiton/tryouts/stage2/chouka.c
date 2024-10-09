#include<stdio.h>
#include<stdlib.h>

int main(){
    int t;
    scanf("%d",&t);

    int n[t],k[t];
    for(int i = 0; i < t; i++){
        scanf("%d %d",&n[i],&k[i]);
    }

    for(int i = 0; i < t; i++){
        if(k[i] == 0 || n[i] == 0){
            printf("NO !!!\n");
            continue;
        }
    int total_draws = (n[i] * 10) / k[i];
        if(total_draws >= 560){
            printf("LETS GGG!!!\n");
        } else {
            printf("NO !!!\n");
        }
    }

    system("pause");
    return 0;
}