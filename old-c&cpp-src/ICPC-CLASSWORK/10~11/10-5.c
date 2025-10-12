#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char a[101];
    scanf("%s",a);

    int count = 0; int k = 0;
    for(size_t i = 0; i < strlen(a) / 2; i++){

        if(a[i] == a[strlen(a) - 1 - k]){
            count++;
        }
        k++;
    }
    if(count == strlen(a) / 2){
        printf("yes");
    }else{
        printf("no");
    }

    return 0;
}