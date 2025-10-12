#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int n,x;
    scanf("%d %d",&n,&x);

    char num_str[10];
    int count = 0;
    char y = x + '0';

    for(int i = 1; i <= n; i++){
        sprintf(num_str,"%d",i);
        for(int j = 0; j <= strlen(num_str); j++){
            if(y == num_str[j]){
                count++;
            }
        }
    }
    printf("%d",count);

    system("pause");
    return 0;

}