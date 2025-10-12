#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char a[101];
    
    while(~scanf("%s", a)){
        int len = strlen(a);
        for(int i = len - 1; i >= 0; i--){
            putchar(a[i]);
        }
        putchar('\n');
    }
    return 0;
}