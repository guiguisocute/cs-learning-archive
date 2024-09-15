#include<stdio.h>
#include<stdlib.h>

int main(){
    int a; int d = 1;
    scanf("%d",&a);

    if(a == 1){
        printf("%d",d);

        system("pause");
        return 0;
        }

    for(;;){
        a /= 2;
        d++;
        if (a == 1){
            break;
        }
        
    }
    printf("%d",d);

    system("pause");
    return 0;
}