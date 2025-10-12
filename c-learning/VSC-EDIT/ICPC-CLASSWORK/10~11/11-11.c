#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    int count_al[26] = {0};
    char s[410];
    for (int i = 0; i < 4; i++) {
        char temp[110]; 
        fgets(temp, sizeof(temp), stdin);
        strcat(s, temp);
        }

    int max = 0;
    int len = strlen(s);

    for(int i = 0; i < len; i++){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            count_al[s[i] - 'A']++;
        }
    }
    for(int i = 0; i < 26;i++){
        if(count_al[i] > max){
            max = count_al[i];
        }
    }
    
    for(int i = max; i > 0; i--){
        for(int j = 0; j < 26; j++){
            if(count_al[j] >= i){
                printf("* ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    for(int j = 0; j < 26; j++){
    printf("%c ", 'A' + j);
    }

    return 0;
}