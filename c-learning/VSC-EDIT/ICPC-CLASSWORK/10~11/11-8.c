#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main() {
    int n, i, vk_count = 0;
    char s[105];

    scanf("%d", &n);
    scanf("%s", s);

    for(i = 0; i < n - 1; i++) {
        if(s[i] == 'V' && s[i + 1] == 'K') {
            vk_count++;
            s[i] = '0';
            s[i + 1] = '0';  
        }
    }

    for(i = 0; i < n - 1; i++) {
        if(s[i] == s[i + 1] && s[i] != '0' && s[i + 1] != '0') {
            vk_count++;
            break;
        }
    }
        

    printf("%d", vk_count);

    return 0;
}
