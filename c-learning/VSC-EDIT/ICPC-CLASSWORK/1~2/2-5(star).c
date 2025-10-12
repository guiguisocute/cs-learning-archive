#include<stdio.h>
#include<stdlib.h>

int main(){
    char a,b,c,d;
    scanf("%c%c%c.%c",&a,&b,&c,&d);    //很惭愧，这一题看了别人的题解，感到很精妙
    printf("%c.%c%c%c",d,c,b,a);

    system("pause");
    return 0;
}