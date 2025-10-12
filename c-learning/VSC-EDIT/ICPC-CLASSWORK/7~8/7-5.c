#include<stdio.h>
#include<stdlib.h>

int isstrange(int n){
    char str[20];
    sprintf(str,"%d",n);
    for(int i = 0; i < 20 && str[i] != '\0'; i++){
        if(str[i] == '2' || str[i] == '0' || str[i] == '3' || str[i] == '8'){
            return 1;
        }
    }
    return 0;
}

int main(){
    int n,sum = 0;
    scanf("%d",&n);

    for(int i = 0; i <= n; i++){
        if(isstrange(i)){
            sum += i;
        }
    }
    printf("%d",sum);

    system("pause");
    return 0;
}
