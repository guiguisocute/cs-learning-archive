#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main(){
    char word[11];
    char essay[1000001];

    scanf("%s",word);
    getchar();
    fgets(essay, sizeof(essay), stdin);

    to_lower(word);
    to_lower(essay);

    int count = 0;
    int pos = -1;

    int word_len = strlen(word);
    int essay_len = strlen(essay);

    int i = 0;
    while (i < essay_len) {
        
        while (i < essay_len && essay[i] == ' ') {
            i++;
        }

        int start = i;

        while(i < essay_len && essay[i] != ' '){
            i++;
        }

        int current_len = i - start;

        if(current_len == word_len && strncmp(&essay[start],word,word_len) == 0){
        count++;
        if(pos == -1){
            pos = start;
         }
        }
        i++;
    }
    if(pos != -1){
        printf("%d %d",count,pos);
    }else{
        printf("-1");
    }

    return 0;

}