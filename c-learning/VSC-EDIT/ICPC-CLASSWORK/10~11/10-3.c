#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char a[20];
     fgets(a, 20, stdin);

    int count = 0;
    for(int i = 0; i < strlen(a); i++){
        if(a[i] != ' ' && a[i] != '\n' && a[i] != '\0'){
            count++;
        }
    }
    printf("%d",count);

    return 0;
}