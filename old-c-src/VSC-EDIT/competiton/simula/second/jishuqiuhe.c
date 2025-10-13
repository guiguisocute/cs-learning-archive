#include <stdio.h>
#include <stdlib.h>

int main(){
    int m,n,sum = 0;
    scanf("%d %d",&m,&n);

    for(int i = m; i <= n; i++){
        if(i % 2 != 0){
            sum += i;
        };
        
    }
    printf("%d",sum);

    system("pause");
    return 0;
}