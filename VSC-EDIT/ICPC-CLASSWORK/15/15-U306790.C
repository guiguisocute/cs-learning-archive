#include<stdio.h>
#include<string.h>

unsigned long long binary2decimal(char b[]) {
    unsigned long long d = 0;
    unsigned long long base = 1;
    int len = strlen(b);

    for(int i = len - 1; i >= 0; i--){
        if(b[i] == '1'){
            d += base;
        }
        base <<= 1;
    }

    return d;
}

int main(){
    char x[10000];
    scanf("%s",x);

    unsigned long long d = binary2decimal(x);
    printf("%llu",d);
    return 0;
}