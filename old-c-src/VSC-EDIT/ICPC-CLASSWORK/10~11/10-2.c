#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int n;
    scanf("%d",&n);

    char c[51];
    scanf("%s",c);

    for(int i = 0; i < 51 && c[i] != '\0'; i++){
        int temp = n;
        while(temp){
            c[i]++;
            if( c[i]  > 'z' ){
                c[i]  =  'a';
            }
            temp--;
        }
    }

    printf("%s",c);

    return 0;
}