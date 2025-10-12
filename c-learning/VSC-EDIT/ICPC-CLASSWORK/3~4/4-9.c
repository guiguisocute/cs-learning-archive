#include<stdio.h>
#include<stdlib.h>

int main(){
    int a,b; char in;
    scanf("%d %d %c",&a,&b,&in);

    if(in == '+'){
        printf("%d",a + b);

        system("pause");
        return 0;
    }else if(in == '-'){
        printf("%d",a - b);

        system("pause");
        return 0;
    }else if(in == '*'){
        printf("%d",a * b);

        system("pause");
        return 0;
    }else if(in == '/'){
        if(b == 0){
            printf("Divided by zero!");

            system("pause");
            return 0;
        }else{
            printf("%d",a / b);

            system("pause");
            return 0;
        }
        
    }
    printf("Invalid operator!");

    system("pause");
    return 0;

}