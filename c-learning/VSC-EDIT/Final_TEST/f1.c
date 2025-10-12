#include <stdio.h>


int gcd(int a,int b){
    if(a < b){
        int temp = a;
        a = b;
        b = temp;
    }
    if(b == 0) return a;
    return gcd(b,a % b);
}

void strcat(char s1[],char s2[])