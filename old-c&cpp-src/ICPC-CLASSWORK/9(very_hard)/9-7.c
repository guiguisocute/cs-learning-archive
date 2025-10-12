#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);

    int num[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            num[i][j] = 1;
        }
    }

    for(int layer = 1; layer <= n / 2; layer++) {
        for(int i = layer; i < n - layer; i++) {
            num[layer][i] = layer + 1;          
            num[n - layer - 1][i] = layer + 1;  
            num[i][layer] = layer + 1;          
            num[i][n - layer - 1] = layer + 1;  
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", num[i][j]);
        }
        printf("\n");
    }

    return 0;
}