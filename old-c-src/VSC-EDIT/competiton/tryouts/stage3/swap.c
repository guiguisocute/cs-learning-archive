#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    int change[10],x,y;  
    for(int i = 0; i < 10; i++){
        scanf("%d %d",&x,&y);
        change[x] = y;
    }

    char baka[100];
    scanf("%s",baka);

    for (int i = 0; i < strlen(baka); i++) {
        if (isdigit(baka[i])) {
            baka[i] = '0' + change[baka[i] - '0'];
        }
    }

    long long int num1 = 0,num2 = 0; int i = 0;
    char suan;

    while (isdigit(baka[i])) {
        num1 = num1 * 10 + (baka[i] - '0');
        i++;
    }
    
    suan = baka[i];
    i++;
    
    while (isdigit(baka[i])) {
        num2 = num2 * 10 + (baka[i] - '0');
        i++;
    }
    
    long long int result = 0;
    if (suan == '+') {
        result = num1 + num2;
    } else if (suan == '-') {
        result = num1 - num2;
    } else if (suan == '*') {
        result = num1 * num2;
    } else if (suan == '/') {
        result = num1 / num2;
    }
    
    
    printf("%lld",result);
    system("pause");
    return 0;
}