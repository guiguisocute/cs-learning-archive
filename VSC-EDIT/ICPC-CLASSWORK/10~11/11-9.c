#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    char s[301];
    char s1[11];
    char s2[11];
    scanf("%[^,],%[^,],%s", s, s1, s2);
    int slen = strlen(s),s1len = strlen(s1),s2len = strlen(s2);
    int pos_s1[301],pos_s2[301];
    int s1_count = 0, s2_count = 0;

    int result = -1;
    for(int i = 0; i <= slen - s1len; i++){
        if(strncmp(&s[i],s1,s1len) == 0){
            pos_s1[s1_count++] = i;
        }
    }

    for(int i = 0; i <= slen - s2len; i++){
        if(strncmp(&s[i],s2,s2len) == 0){
            pos_s2[s2_count++] = i;
        }
    }

    for(int i = 0; i < s1_count; i++){
        for(int j = 0; j < s2_count; j++){
            int s1end = pos_s1[i] + s1len;
            int s2start = pos_s2[j];
            if(s1end <= s2start){
                int current = s2start - s1end;
                if(current > result){
                    result = current;
                }
            }
        }
    }

    printf("%d",result);
    return 0;
}