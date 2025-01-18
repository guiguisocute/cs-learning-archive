#include<stdio.h>

// 使用两个数组分别存储值和下一个位置
int val[100010], nxt[100010];
int pos[1000010];  // 记录每个值的位置
int q,op,x,y,tt = 1;

void insert(int x,int y){
    tt++;
    val[tt] = y;
    int idx = pos[x];
    nxt[tt] = nxt[idx];
    nxt[idx] = tt;
    pos[y] = tt;
}

void erase(int x){
    int idx = pos[x];
    if(nxt[idx] > 0){
        pos[val[nxt[idx]]] = 0;
        nxt[idx] = nxt[nxt[idx]];
    }
}

int main(){
    val[1] = 1; nxt[1] = -1;
    pos[1] = 1;
    
    scanf("%d",&q);
    while(q--){
        scanf("%d",&op);
        if(op == 1){
            scanf("%d %d",&x,&y);
            insert(x,y);
        }else if(op == 2){
            scanf("%d",&x);
            int idx = pos[x];
            if(nxt[idx] > 0){
                printf("%d\n",val[nxt[idx]]);
            }else{
                printf("0\n");
            }
        }else if(op == 3){
            scanf("%d",&x);
            erase(x);
        }
    }
    return 0;
}