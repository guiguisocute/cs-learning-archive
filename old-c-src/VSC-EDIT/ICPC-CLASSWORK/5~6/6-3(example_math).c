#include <stdio.h>

int countDigit(int n, int x) {
    int count = 0;
    for (int pos = 1; pos <= n; pos *= 10) {
        int current = (n / pos) % 10;  // 当前位
        int higher = n / (pos * 10);   // 更高位
        int lower = n - (n / pos) * pos; // 更低位

        // 计算当前位上 x 出现的次数
        if (current > x) {
            count += (higher + 1) * pos; // 当前位置为x的次数
        } else if (current == x) {
            count += higher * pos + lower + 1;
        } else {
            count += higher * pos;
        }
    }

    // 处理 x 为 0 的特殊情况
    if (x == 0) {
        for (int pos = 1; pos <= n; pos *= 10) {
            if (n / pos == 0) {
                count -= (n / (pos * 10)) * pos; // 如果高位是0，需要减去
            }
        }
    }

    return count;
}

int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    int result = countDigit(n, x);
    printf("%d\n", result);
    return 0;
}