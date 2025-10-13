#include<stdio.h>

// 定义二维数组 a 和 b 用于存储拼图的状态，row 和 col 用于记录行和列的交换状态
int a[1010][1010], b[1010][1010], row[1010], col[1010];

int main() {
    int n, m;
    // 读取拼图的大小 n 和操作次数 m
    scanf("%d %d", &n, &m);

    // 初始化行和列的映射为自身
    for (int i = 1; i <= n; i++) {
        row[i] = i; // row[i] 表示第 i 行当前映射到的行
        col[i] = i; // col[i] 表示第 i 列当前映射到的列
        for (int j = 1; j <= n; j++) {
            // 读取拼图的初始状态
            scanf("%d", &a[i][j]);
        }
    }

    // 处理 m 次操作
    while (m--) {
        int op, x, y;
        // 读取操作类型和操作的行或列
        scanf("%d %d %d", &op, &x, &y);
        if (op == 1) {
            // 如果 op 为 1，交换行 x 和行 y
            int temp = row[x];
            row[x] = row[y];
            row[y] = temp;
        } else {
            // 如果 op 为 0，交换列 x 和列 y
            int temp = col[x];
            col[x] = col[y];
            col[y] = temp;
        }
    }

    // 根据行的映射更新数组 b
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            b[i][j] = a[row[i]][j];

    // 根据列的映射更新数组 a
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= n; i++)
            a[i][j] = b[i][col[j]];

    // 输出复原后的拼图
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 输出每个位置的值，注意格式
            printf("%d%c", a[i][j], j == n ? '\n' : ' ');
        }
    }

    return 0;
}