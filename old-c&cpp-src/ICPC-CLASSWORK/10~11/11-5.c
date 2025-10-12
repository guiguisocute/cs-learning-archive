#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    char s[21];
    scanf("%s",s);

    char temp1[21] = {0},temp2[20] = {0};
    int len = strlen(s);
    char ch = '\0';
    int i;

    for(i = 0; i < len; i++){
        if(!isdigit(s[i])){
            ch = s[i];
            break;
        }
    }

    if(s[0] == '0' && (ch == '\0' || ch == '%')){
        printf("0%c",ch);

        return 0;
    }

    strncpy(temp1,s,i);
    temp1[i] = '\0';

    if(ch != '0'){
        strcpy(temp2,s + i + 1);
    }

    int judge = 0;

    if(ch == '\0'){
        for(i = len - 1; i >= 0; i--){
            if(temp1[i] != '0'){
                judge = 1;
            }
            if(temp1[i] == '0' && temp1[len -1] == '0'){
                if(i == len - 1){
                    continue;
                }else if(temp1[i + 1] == '0' && !judge){
                    continue;
                }
            }
           printf("%c",temp1[i]);   
        }
        judge = 0;
    }else{
        if(ch == '%'){
            for(i = len - 2; i >= 0; i--){
                if(temp1[i] != '0'){
                    judge = 1;
            }
            if(temp1[i] == '0' && temp1[len - 2] == '0'){
                if(i == len - 2){
                    continue;
                }else if(temp1[i + 1] == '0' && !judge){
                    continue;
                }
            }
           printf("%c",temp1[i]);
            
        }
        judge = 0;
        printf("%%");


        }else if(ch == '/'){
            int len_1 = strlen(temp1);
            int len_2 = strlen(temp2);
            for(i = len_1 - 1; i >= 0; i--){
                if(temp1[0] == '0'){
                    printf("0");
                    break;
                }
                if(temp1[i] != '0'){
                    judge = 1;
            }
            if(temp1[i] == '0' && temp1[len_1 -1] == '0'){
                if(i == len_1 - 1){
                    continue;
                }else if(temp1[i + 1] == '0' && !judge){
                    continue;
                }
            }
           printf("%c",temp1[i]);   
        }
        judge = 0;
        printf("/");
        for(i = len_2 - 1; i >= 0; i--){
            if(temp2[i] != '0'){
                judge = 1;
            }
            if(temp2[i] == '0' && temp2[len_2 -1] == '0'){
                if(i == len_2 - 1){
                    continue;
                }else if(temp2[i + 1] == '0' && !judge){
                    continue;
                }
            }
           printf("%c",temp2[i]);   
        }
        judge = 0;

        }else{
            int len_1 = strlen(temp1);
            int len_2 = strlen(temp2);
            for(i = len_1 - 1; i >= 0; i--){
                if(temp1[0] == '0'){
                    printf("0");
                    break;
                }
                if(temp1[i] != '0'){
                judge = 1;
                }
                 if(temp1[i] == '0' && temp1[len_1 -1] == '0'){
                    if(i == len_1 - 1){
                    continue;
                    }else if(temp1[i + 1] == '0' && !judge){
                    continue;
                }
            }
           printf("%c",temp1[i]);   
        }
        judge = 0;
        printf(".");
        if(temp2[0] == '0' && temp2[1] == '\0'){
            printf("0");
            return 0;
        }
        int start = 0;
        for(i = 0; i < len_2; i++){
            if(temp2[start] == '0'){
                start++;
            }
        }
        for(i = len_2 - 1; i >= start; i--){
            printf("%c",temp2[i]);
            if(i == start){
                printf("\0");
            }
        }
        }
    }
    printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");printf("\0");
    
    return 0;
}