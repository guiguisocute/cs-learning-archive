#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,count = 0;
    scanf("%d",&n);
    int a[n];
    for(int i =0; i < n; i++){
        scanf("%d",&a[i]);
    }

    printf("0 ");
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(a[i]- a[j] > 0){
                count++;
            }
        }
        printf("%d ",count);
        count = 0;
    }

    system("pause");
    return 0;

}