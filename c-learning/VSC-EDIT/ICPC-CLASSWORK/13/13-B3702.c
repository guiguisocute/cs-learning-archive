//这题就是用输出本身的坐标储存了“要去的坐标”，然后一直走到00就停这个样子
//第一（0+1）行第一个就代表（1.1），以此类推6
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

typedef struct {
    int nextx;
    int nexty;
} info;

info a[1007][1007];

int main(){
    int m,n,sx,sy;

    scanf("%d %d %d %d",&m,&n,&sx,&sy);

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d %d",&a[i][j].nextx,&a[i][j].nexty);
        }
    }
    int currentx = sx,currenty = sy;

    while(1){
        printf("%d %d\n",currentx,currenty);

        int nextx = a[currentx][currenty].nextx;
        int nexty = a[currentx][currenty].nexty;
            if(nextx == 0 && nexty ==0){
                break;
            }
        currentx = nextx;
        currenty = nexty;
            }

    return 0;
}



