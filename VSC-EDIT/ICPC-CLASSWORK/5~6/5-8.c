#include<stdio.h>
#include<stdlib.h>

int main(){
    char a[9]; int count = 0;
    scanf("%s",a);

    for(int i = 0; a[i] != '\0'; i++){
        if(a[i] == '1'){
            count++;
        }
    }
    printf("%d",count);

    system("pause");
    return 0;
}