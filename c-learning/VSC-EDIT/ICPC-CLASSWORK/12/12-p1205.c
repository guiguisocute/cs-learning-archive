#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

char original[10][10];  
char target[10][10];    
char temp[10][10];     
int n;

void copyArray(char dest[10][10], char src[10][10]) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dest[i][j] = src[i][j];
}

int isSame(char arr1[10][10], char arr2[10][10]) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(arr1[i][j] != arr2[i][j])
                return 0;
    return 1;
}

void rotate90(char src[10][10], char dest[10][10]) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dest[i][j] = src[n-1-j][i];
}

void reflect(char src[10][10], char dest[10][10]) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dest[i][j] = src[i][n-1-j];
}

int solve() {
    char work[10][10];
    
    rotate90(original, temp);
    if(isSame(temp, target)) return 1;
    
    rotate90(temp, work);
    if(isSame(work, target)) return 2;
    
    rotate90(work, temp);
    if(isSame(temp, target)) return 3;
    

    reflect(original, temp);
    if(isSame(temp, target)) return 4;
    

    rotate90(temp, work);
    if(isSame(work, target)) return 5;
    
    rotate90(work, temp);
    if(isSame(temp, target)) return 5;
    
    rotate90(temp, work);
    if(isSame(work, target)) return 5;
    
    if(isSame(original, target)) return 6;
    
    return 7;
}

int main() {
    int i;
    
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        scanf("%s", original[i]);
    }
    
    for(i = 0; i < n; i++) {
        scanf("%s", target[i]);
    }
    
    printf("%d", solve());
    
    return 0;
}