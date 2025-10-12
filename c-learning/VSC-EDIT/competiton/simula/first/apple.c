#include<stdio.h>
#include<stdlib.h>

int main(){
    int apples[10],tall,count = 0;
    for(int i = 0; i < 10; i++){
        scanf("%d",&apples[i]);
    }
    scanf("%d",&tall);
    tall += 30;

    for(int i = 0; i < 10; i++){
        if(apples[i] <= tall)
        count++;
    }

    printf("%d",count);
    
    system("pause");
    return 0;
}