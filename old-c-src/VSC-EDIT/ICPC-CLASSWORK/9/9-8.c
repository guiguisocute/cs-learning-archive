#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);

    int a[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d",&a[i][j]);
        }
    }
    int b[m][k];
    for(int i = 0; i < m; i++){
        for(int j = 0; j < k; j++){
            scanf("%d",&b[i][j]);
        }
    }

    int c[n][k];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            c[i][j] = 0;
            for(int l = 0; l < m; l++){
                c[i][j] += a[i][l] * b[l][j];
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}