#include <stdio.h>
#include <stdlib.h>

int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    
    int temp;
    if(a > b){
        temp = a;
        a = b;
        b = temp;        
    }
    if(a > c){
        temp = a;
        a = c;
        c = temp;
    }
    if(b > c){
        temp = c;
        c = b;
        b = temp;
    }
    printf("%d %d %d",a,b,c);

    system("pause");
    return 0;
}