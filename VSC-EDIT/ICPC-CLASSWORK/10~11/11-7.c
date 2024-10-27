#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main() {
    char input[256];
    fgets(input, 256, stdin);  
    int vars[3] = {0, 0, 0};   
    int pos = 0;
    int len = strlen(input);

    while (pos < len) {
        if(input[pos] >= 'a' && input[pos] <= 'c') {
            int var_index = input[pos] - 'a';  
            pos++;

            if(input[pos] == ':' && input[pos + 1] == '=') {
                pos += 2;
            }else{
                break;
            }

            
            int value = 0;
            if(input[pos] >= 'a' && input[pos] <= 'c') {
                int val_index = input[pos] - 'a';
                value = vars[val_index];  
                pos++;
            }else if(input[pos] >= '0' && input[pos] <= '9') {
                value = input[pos] - '0';
                pos++;
            }else{
                break;
            }
           
            if(input[pos] == ';') {
                pos++;
            }else{    
                break;
            }

            vars[var_index] = value;
        }else{
            break;
        }
    }
    printf("%d %d %d\n", vars[0], vars[1], vars[2]);

    return 0;
}