#include <stdio.h>


char grid[505][505];  
int r, c, N, M;  

int can_escape(int x, int y, int dx, int dy, char type) {
    x += dx;
    y += dy;

    while(x >= 0 && x < r && y >= 0 && y < c) {

        if((type == 'F' && grid[x][y] == 'M') || 
           (type == 'M' && grid[x][y] == 'F')) {
            return 0;
        }
        x += dx;
        y += dy;
    }
    
    return 1;  
}

int count_escape_paths(int x, int y) {
    char type = grid[x][y];
    if(type != 'F' && type != 'M') return 0;
    
    int paths = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for(int i = 0; i < 4; i++) {
        if(can_escape(x, y, dx[i], dy[i], type)) {
            paths++;
        }
    }
    
    return paths;
}

int main() {
    scanf("%d %d %d %d", &r, &c, &N, &M);

    for(int i = 0; i < r; i++) {
        scanf("%s", grid[i]);
    }
    

    int answer = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(grid[i][j] != '.') {

                if(count_escape_paths(i, j) >= 3) {
                    answer++;
                }
            }
        }
    }
    
    printf("%d\n", answer);
    return 0;
}