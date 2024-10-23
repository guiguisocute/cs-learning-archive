#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        char c[201];
        scanf("%s",c);
        int max = 1;
        char max_c = c[0];
        int current = 1;
        int len = strlen(c);

        for(int i = 1; i < len; i++){
            if(c[i] == c[i - 1]){
                current++;
            }else{
                if(current > max){
                max = current;
                max_c = c[i - 1];
            }
            current = 1;
                }
            
        }
        if(current > max){
            max = current;
            max_c = c[len - 1];
        }
        printf("%c %d\n",max_c,max);
    }
    return 0;
}