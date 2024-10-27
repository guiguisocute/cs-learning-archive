#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    while(1){
        int n;
        scanf("%d",&n);
        if(n == 0){
            break;
        }
        
        char s[200][201];
        int len[200];
        int min_len = 201;

        for(int i = 0; i < n; i++){
            scanf("%s",s[i]);
            len[i] = strlen(s[i]);
            if(len[i] < min_len){
                min_len = len[i];
            }
        }

        char ans[201];
        int pos = 0;

        for(int i = 1; i <= min_len; i++){
            char c = s[0][len[0] - i];
            int j;
            for(j = 1 ; j < n; j++){
                if(s[j][len[j] - i] != c){
                    break;
                }
            }
            if (j == n){
                ans[pos++] = c;
            }else {
                break;
            }
        }
        if (pos == 0){
            printf("\n");
        }else{
            for(int i = pos - 1; i >= 0; i--){
                printf("%c",ans[i]);
            }
            printf("\n");
        }
    }
    return 0;
}