#include <stdio.h>

//试着去理解题解：
//完全没理解啊，样例都没整明白啊
int a[110][110], n, m, k, cnt;

int main() {
    // 读入矩阵大小和需要的满足条件的位置数
    scanf("%d %d %d", &n, &m, &k);
    
    // 读入矩阵并同时计算行和列的和
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            a[i][0] += a[i][j];  // a[i][0] 存储第i行的和
            a[0][j] += a[i][j];  // a[0][j] 存储第j列的和
        }
    }
    
    // 无限循环，直到找到满足条件的解
    for (int t = 0; ; t++) {
        cnt = 0;  // 重置满足条件的位置计数
        
        // 检查每个位置是否满足条件
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // 如果当前位置的值大于等于行和与列和之和，则满足条件
                if (a[i][j] >= a[i][0] + a[0][j]) {
                    cnt++;
                }
            }
        }
        
        // 如果满足条件的位置数量达到要求，输出当前魔法释放次数并结束
        if (cnt >= k) {
            printf("%d\n", t);
            return 0;
        }
        
        // 释放一次魔法，所有数字减1
        for (int i = 1; i <= n; i++) {
            a[i][0] -= m;  // 每行的和减少m
        }
        for (int j = 1; j <= m; j++) {
            a[0][j] -= n;  // 每列的和减少n
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                a[i][j]--;  // 每个位置的值减1
            }
        }
    }
    
    return 0;
}