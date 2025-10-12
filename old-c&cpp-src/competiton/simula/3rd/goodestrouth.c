#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define ll long long
#define INF 1e18


typedef struct {
    ll x, y;
} point;

int n;
ll v;

point points[16];
ll fee[16][16];
ll minfee[65536][16];

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll abs_ll(ll a) {
    return a >= 0 ? a : -a;
}

int main(){
    scanf("%d %lld",&n,&v);
    for(int i = 0; i < n; i++){
        scanf("%lld %lld",&points[i].x,&points[i].y);
    }

    for (int i = 0; i < n; i++) {
        fee[n][i] = v * (abs_ll(points[i].x) + abs_ll(points[i].y));   //fee[n]是起点
        for (int j = 0; j < n; j++) {
            fee[i][j] = v * (abs_ll(points[i].x - points[j].x) + abs_ll(points[i].y - points[j].y));
        }
    }

    int all_state = pow(2,n);

    for(int i = 0; i < all_state; i++){
        for(int j = 0; j < n; j++){
            minfee[i][j] = INF;
        }
    }

    for(int i = 0; i < n; i++){
        int mask = pow(2,i);
        minfee[mask][i] = fee[n][i];
    }

    for (int mask = 1; mask < all_state; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))){
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)){
                continue;
                }
                int next_mask = mask | (1 << j);
                minfee[next_mask][j] = min(minfee[next_mask][j], minfee[mask][u] + fee[u][j]);
            }
        }
    }

    ll ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, minfee[all_state - 1][i]);
    }

    printf("%lld", ans);

    return 0;
}