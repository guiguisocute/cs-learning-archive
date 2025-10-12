#include<stdio.h>
#include<stdlib.h>

int main(){
    int t; int apple[10];
    for(int i = 0; i < 10; i++){
        scanf("%d",&apple[i]);
    }
    scanf("%d",&t); t += 30;

    int count = 0;
    for(int i = 0; i < 10; i++){
        if(apple[i] <= t){
            count++;
        }
      
    }
        printf("%d\n",count);  

        system("pause");
        return 0;



}