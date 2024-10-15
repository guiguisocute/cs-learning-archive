#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);

    int a[n][n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            a[i][j] = 0;
        }
    }

    int torch_dx[] = {2,0,-2,0,1,1,1,0,0,0,-1,-1,-1}; 
    int torch_dy[] = {0,2,0,-2,0,1,-1,1,0,-1,0,1,-1};

    int glow_dx[] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
    int glow_dy[] = {-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2};

    for(int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;
        for(int j = 0; j < 13; j++) {
            int new_x = x + torch_dx[j];
            int new_y = y + torch_dy[j];
            if (new_x >= 0 && new_x <= n && new_y >= 0 && new_y <= n) {
                a[new_x][new_y] = 1;
            }
        }
    }

    for(int i = 1; i <= k; i++){
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        for(int j = 0; j < 25; j++){
            int new_x = x + glow_dx[j];
            int new_y = y + glow_dy[j];
            if (new_x >= 0 && new_x <= n && new_y >= 0 && new_y <= n) {
                a[new_x][new_y] = 1;
            }
        }
    }

    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(a[i][j] == 0){
                count++;
            }
        }
    }

    printf("%d",count);
    return 0;
}