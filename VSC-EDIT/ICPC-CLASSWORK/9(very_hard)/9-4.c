#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    scanf("%d",&n);

    int a[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }

    int num = 1;
    int row = 0, col = n / 2;

    while(num <= n * n){
        a[row][col] = num;
        num++;

        int newrow = (row - 1 + n) % n;
        int newcol = (col + 1) % n;

        if (a[newrow][newcol] != 0){
            row = (row + 1) % n;
        }else{
            row = newrow;
            col = newcol;
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