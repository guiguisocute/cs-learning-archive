#include<stdio.h>

void swap(int* a,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int a[3];
    scanf("%d %d %d",&a[0],&a[1],&a[2]);

    for(int i = 0; i < 2; i++){
        for(int j =0; j < 2 - i; j++){
            if(a[j] > a[j + 1]){
                swap(&a[j],&a[j + 1]);
            }
        }
    }

    for(int i = 0; i < 3;i++){
        printf("%d ",a[i]);
    }

    return 0;

    
}