#include<stdio.h>
#include<math.h>
#include<string.h>

int main(){
    int n;
    char line[201];
    scanf("%s", line);
    n = strlen(line);
    char grid[200][201];
    strcpy(grid[0], line);
    for (int i = 1; i < n; i++) {
        scanf("%s", grid[i]);
    }

    char c_char = '0';
    int count = 0;
    printf("%d ",n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (grid[i][j] == c_char){
                count++;
            }else{
                printf("%d ",count);
                c_char = grid[i][j];
                count = 1;
            }
        }
    }

    printf("%d\n",count);

    return 0;
}