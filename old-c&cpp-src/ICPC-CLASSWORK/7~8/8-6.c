#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;  int count[8] = {0}, reward[7], ticket[7];
    scanf("%d",&n);
    for(int i = 0; i < 7; i++){
        scanf("%d",&reward[i]);
    }

    while(n--){
        int correct_num = 0;
        for(int i = 0; i < 7; i++){
            scanf("%d",&ticket[i]);
            for(int j = 0; j < 7; j++){
                if(ticket[i] == reward[j]){
                    correct_num++;
                }
            }
        }
        count[7 - correct_num]++;
    }

    for(int i = 0; i < 7; i++){
        printf("%d",count[i]);
        if(i < 6){
            printf(" ");
        }
    }

    return 0;
}