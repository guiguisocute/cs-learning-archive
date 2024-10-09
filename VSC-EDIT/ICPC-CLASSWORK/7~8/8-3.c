#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,i = 1;
    scanf("%d",&n);

    int a[1000];
    a[0] = n;
    while(n != 1){
        if(n %2 == 0){
            n /= 2;
            a[i] = n;
            i++;
        }else{
            n = n * 3 + 1;
            a[i] = n;
            i++;
        }
    }

    for(int j = i - 1; j >= 0; j--){
        printf("%d ",a[j]);
    }

    system("pause");
    return 0;
}