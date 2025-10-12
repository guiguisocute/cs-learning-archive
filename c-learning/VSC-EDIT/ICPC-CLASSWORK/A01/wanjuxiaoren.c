#include<stdio.h>
#define MAXN 100100

int n,m,a,s,ans = 1;
int out[MAXN];
char job[MAXN][20];

int main(){
    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++){
        scanf("%d %s",&out[i],job[i]);
    }

    for(int i = 1; i <= m; i++){
        scanf("%d %d",&a,&s);
        if (a ^ out[ans]) {
            ans = (ans + s) % n;
        } else {
            ans = (ans + (n - s)) % n;
        }
        if (ans == 0) {
            ans = n;
        }
    }
    printf("%s",job[ans]);
    return 0;
    

}

