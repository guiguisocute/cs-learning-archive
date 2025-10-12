#include <stdio.h>
#include <stdbool.h>

#define MAX_N 30000

bool friends[MAX_N + 1][MAX_N + 1]; // 存储朋友关系
bool enemies[MAX_N + 1][MAX_N + 1]; // 存储敌人关系
bool processed[MAX_N + 1][MAX_N + 1]; // 标记是否已处理

int main() {
    int n, p, q, u, v;
    scanf("%d %d %d", &n, &p, &q);

    int ans = (n * (n - 1)) / 2; // 初始为所有可能的握手对数

    for (int i = 0; i < p; i++) {
        scanf("%d %d", &u, &v);
        friends[u][v] = true;
        friends[v][u] = true;
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &u, &v);
        enemies[u][v] = true;
        enemies[v][u] = true;
        ans--; // 敌人之间不握手
    }

    for (u = 1; u <= n; u++) {
        for (v = u + 1; v <= n; v++) {
            if (friends[u][v] || enemies[u][v]) continue; // 已处理的关系
            bool can_handshake = true;
            for (int i = 1; i <= n; i++) {
                if ((friends[u][i] && enemies[v][i]) || (friends[v][i] && enemies[u][i])) {
                    can_handshake = false;
                    break;
                }
            }
            if (!can_handshake) {
                ans--; // 减去不能握手的陌生人对
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}

