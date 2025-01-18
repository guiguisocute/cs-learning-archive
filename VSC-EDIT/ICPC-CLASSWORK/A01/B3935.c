#include <stdio.h>
#include <string.h>

#define MAX_M 100005

// 计算两个数的最大公约数
int gcd(int a, int b) {
    while (b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n, m;
        char s[MAX_M];
        scanf("%d %d %s", &n, &m, s);
        
        if (s[0] != '1') {
            printf("No\n");
            continue;
        }
        
        int positions[MAX_M];
        int pos_count = 0;
        int len = strlen(s);
        
        // 记录所有 '1' 的位置
        for (int i = 0; i < len; i++) {
            if (s[i] == '1') {
                positions[pos_count++] = i;
            }
        }
        
        // 如果只有一个 '1'
        if (pos_count == 1) {
            int L = len;
            int k = L - 1;
            if (k <= n) {
                int valid = 1;
                for (int i = 0; i < len; i++) {
                    if ((i == 0 && s[i] != '1') || (i != 0 && s[i] != '0')) {
                        valid = 0;
                        break;
                    }
                }
                printf("%s\n", valid ? "Yes" : "No");
            } else {
                printf("No\n");
            }
            continue;
        }
        
        // 计算相邻 '1' 位置差的 GCD
        int current_gcd = positions[1] - positions[0];
        for (int i = 2; i < pos_count; i++) {
            int diff = positions[i] - positions[i - 1];
            current_gcd = gcd(current_gcd, diff);
        }
        
        int L = current_gcd;
        int k = L - 1;
        
        if (k > n || L == 0) {
            printf("No\n");
            continue;
        }
        
        // 验证字符串是否符合周期模式
        int valid = 1;
        for (int i = 0; i < len; i++) {
            if ((i % L == 0 && s[i] != '1') || (i % L != 0 && s[i] != '0')) {
                valid = 0;
                break;
            }
        }
        
        printf("%s\n", valid ? "Yes" : "No");
    }
    
    return 0;
}