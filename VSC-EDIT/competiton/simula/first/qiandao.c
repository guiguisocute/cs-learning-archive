#include<stdio.h>
#include<stdlib.h>

int main(){
    char a[9]; int count_num = 0, count_a = 0, count_A = 0;
    for(int i = 0; i < 9; i++){
        scanf("%c",&a[i]);
    }
    for(int i = 0; i < 8; i++){
        if(a[i] >= '0' && a[i] <= '9'){
            count_num++;
        }else if(a[i] >='a' && a[i] <= 'z'){
            count_a++;
        }else if(a[i] >= 'A' && a[i] <= 'Z'){
            count_A++;
        }
        
        
    }
    printf("%d %d %d",count_num,count_a,count_A);

    system("pause");
    return 0;
}