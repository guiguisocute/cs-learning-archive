#include<stdio.h>
#include<stdlib.h>

void bubblesort(int num_in[], int n) {
    int temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(num_in[j] > num_in[j + 1]) {
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
    int a[n + 1];
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&a[n]);

    bubblesort(a,n + 1);
    for(int i = 0; i < n + 1; i++){
        printf("%d ",a[i]);
    }

    return 0;
}