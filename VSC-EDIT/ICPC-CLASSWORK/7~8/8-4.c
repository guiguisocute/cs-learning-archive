#include<stdio.h>
#include<stdlib.h>

int main(){
    int l,m;
    scanf("%d %d",&l,&m);

    int tree[l + 1];
    for(int i = 0; i <= l; i++){
        tree[i] = 1;
    }

    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d",&u,&v);

        for(int j = u; j <= v; j++){
            tree[j] = 0;
        }
    }

    int ans = 0;
    for(int i = 0; i <= l; i++){
        if(tree[i] == 1){
            ans++;
        }
    }
    printf("%d",ans);

    return 0; 
}