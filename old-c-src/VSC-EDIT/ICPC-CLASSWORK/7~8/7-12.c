#include<stdio.h>
#include<stdlib.h>

int main(){
    int sumsave = 0;
    int hand = 0;
    int budget;

    for(int i = 1; i <= 12; i++){
        scanf("%d",&budget);

        hand += 300;
        if(hand < budget){
            printf("-%d",i);

            system("pause");
            return 0;
        }

        hand -= budget;

        if(hand >= 100){
            int save = (hand / 100) * 100; 
            sumsave += save;
            hand -= save;
        }
    }

    int total = sumsave * 1.2 + hand;
    printf("%d",total);

    system("pause");
    return 0;
}