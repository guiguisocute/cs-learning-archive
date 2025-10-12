#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,count = 1,max = 1;
    scanf("%d",&n);
    int a[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    for(int i = 0; i < n; i++){
        if(a[i + 1] - a[i] == 1){
            count++;
            if(count > max){
            max = count;
            }
        }else{
            count = 1;
        } 
    }

    if(count > max){
        max = count;
    }
    printf("%d",max);

    system("pause");
    return 0;
}