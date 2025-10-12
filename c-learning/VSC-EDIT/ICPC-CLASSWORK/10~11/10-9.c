#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char a[1001];
    scanf("%s",a);
    int len = strlen(a);

    int count = 1;
    for(int i = 0; i < len; i++){
        if(a[i] == a[i+1]){
            count ++;
        }else{
            printf("%d%c",count,a[i]);
            count = 1;
        }
    }
    return 0;
}
