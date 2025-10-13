#include<stdio.h>
#include<stdlib.h>

int main(){
    int a,b,n;
    scanf("%d %d %d",&a,&b,&n);

    a = a % b;

    for(int i = 0; i < n; i++){
        a *= 10;
        int ans = a / b;
        a = a % b;
        if(i == n - 1){
            printf("%d",ans);
        }

    }

    system("pause");
    return 0;
}