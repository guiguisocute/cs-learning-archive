#include<stdio.h>
#include<stdlib.h>

int main(){
    char c[101];
    scanf("%s",c);

    for(int i = 0; i < 101 && c[i] != '\0'; i++){
        if(c[i] >= 97 && c[i] <= 122){
            c[i] -= 32;
        }
    }

    printf("%s",c);

    return 0;
}