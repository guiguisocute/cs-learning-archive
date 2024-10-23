#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    char current_word[101] = {0};  
    char longest_word[101] = {0};  
    char shortest_word[101] = {0}; 
    int current_len = 0;           
    int max_len = 0;               
    int min_len = 101;             
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF){
        if(isalpha(ch)){
            current_word[current_len++] = ch;
        }else{      //当遇到分隔符（非字母字符）时，检查当前单词的长度，如果当前单词有效（长度大于0），则根据它的长度更新最长和最短单词，并将当前单词清空以继续处理下一个单词。
            if(current_len > 0){
                current_word[current_len] = '\0';

                if(current_len > max_len){
                    max_len = current_len;
                    strcpy(longest_word,current_word);
                }
                if(current_len < min_len){
                    min_len = current_len;
                    strcpy(shortest_word,current_word);
                }

                current_len = 0;

            }
        }
    }
            if(current_len > 0){
                current_word[current_len] = '\0';

                if(current_len > max_len){
                    max_len = current_len;
                    strcpy(longest_word,current_word);
                }
                if(current_len < min_len){
                    min_len = current_len;
                    strcpy(shortest_word,current_word);
                }
            }
    printf("%s\n", longest_word);
    printf("%s", shortest_word);

    return 0;
}