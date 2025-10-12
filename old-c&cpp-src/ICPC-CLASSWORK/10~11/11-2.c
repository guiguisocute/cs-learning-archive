#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int calculate(int x, int y, char op) {
    switch (op) {
        case '+':  
            return x + y;
        case '-':  
            return x - y;
        case '*': 
            return x * y;
    }
    return 0;
}

char coperator(char op) {
    switch (op) {
        case 'a':  
            return '+';
        case 'b':  
            return '-';
        case 'c': 
            return '*';
    }
    return '?';
}

int main(){
    int i;
    scanf("%d",&i);
    char oper;
    int a,b;
    char buffer[50];
    int count = 2;
    getchar();

    while(i--) {
        char ch = getchar();

        if(isalpha(ch)) {
            oper = coperator(ch); 
            scanf("%d %d", &a, &b);
        } else {
            ungetc(ch, stdin);
            scanf("%d %d", &a, &b);
        }

        int result = calculate(a, b, oper);
        printf("%d%c%d=%d\n", a, oper, b, result);

        sprintf(buffer, "%d", a);
        count = strlen(buffer);
        sprintf(buffer, "%d", b);
        count += strlen(buffer);
        sprintf(buffer, "%d", result);
        count += strlen(buffer);
        count += 2;

        printf("%d\n", count);

        getchar();  
    }
    return 0;
}