#include<stdio.h>
#include<stdlib.h>

void bubblesort(int num_in[],int n){
    int temp;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(num_in[j] > num_in[j + 1]){
                temp = num_in[j];
                num_in[j] = num_in[j + 1];
                num_in[j + 1] = temp;
            }
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int num_in[n];
    for(int i = 0; i < n; i++){
        scanf("%d",&num_in[i]);
    }
    bubblesort(num_in,n);
    printf("%d",num_in[0]);

    system("pause");
    return 0;
}