#include<stdio.h>
#include<stdlib.h>

int main(){
    int self[7]; int add[7]; int sum[7];int max = 0; int max_hours = 0;
    for(int i = 0; i < 7; i++){
        scanf("%d %d",&self[i],&add[i]);
    }
    for(int i = 0; i < 7; i++){
        sum[i] = self[i] + add[i];
    }
    for(int i = 0; i < 7; i++){
        if(sum[i] > 8 && sum[i] > max_hours){
            max_hours = sum[i];
            max = i + 1;
        }
        
    }
    
    printf("%d",max);

    system("pause");
    return 0;   
}