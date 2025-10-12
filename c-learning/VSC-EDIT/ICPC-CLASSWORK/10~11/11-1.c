#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    char p[10][5] = {
        " ",     
        "",      
        "abc",   
        "def",   
        "ghi",   
        "jkl",   
        "mno",   
        "pqrs",  
        "tuv",   
        "wxyz"   
    };

    char s[201];
    fgets(s, 201, stdin);
    int len = strlen(s);
    int count = 0;

    for(int i = 0; i < len; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 5; k++){
                if(s[i] == p[j][k]){
                    count += (k + 1); 
                    break;
                }
            }
        }
    }

    printf("%d",count);
    return 0;

}