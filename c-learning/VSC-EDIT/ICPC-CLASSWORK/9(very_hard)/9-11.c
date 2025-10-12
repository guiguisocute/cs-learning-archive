#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    int a[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }

    for(int i = 0; i < m; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for(int x = x1 - 1; x < x2; x++){
            for(int y = y1 -1; y < y2; y++){
                a[x][y]++;
            }
        } 
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}