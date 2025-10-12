#include<stdio.h>
#include<stdlib.h>

int main(){
    int x;
    scanf("%d",&x);
    int a = x / 3,b = x / 3 ,c = x/3;
    a = a / 2;
    b = b / 2;
    c = a + b + c;
    a = a / 2;
    c = c / 2;
    b = b + a + c;
    b = b / 2;
	c = c / 2;
	a = a + b + c;
    printf("%d %d %d",a,b,c);
    
    system("pause");
    return 0;
}

