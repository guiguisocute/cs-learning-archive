#include<stdio.h>
#include<stdlib.h>

int main(){
    int w,x,h;
    scanf("%d %d %d",&w,&x,&h);

    int cube[w][x][h];

    for(int i = 0; i < w; i++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < h; k++){
                cube[i][j][k] = 0;
            }
        }
    }

    int q;
    scanf("%d",&q);

    for(int t = 0; t < q; t++){
        int x1,x2,y1,y2,z1,z2;
        scanf("%d %d %d %d %d %d",&x1,&y1,&z1,&x2,&y2,&z2);

        for(int i = x1 - 1; i < x2; i++){
            for(int j = y1 - 1; j < y2; j++){
                for(int k = z1 - 1; k < z2; k++){
                    cube[i][j][k] = 1;
                }
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < w; i++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < h; k++){
                if(cube[i][j][k] == 0){
                    ans++;
                }
            }
        }
    }

    printf("%d",ans);
    return 0;
}