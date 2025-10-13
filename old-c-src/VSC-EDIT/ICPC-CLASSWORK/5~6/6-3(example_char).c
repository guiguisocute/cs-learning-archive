#include <stdio.h>
#include <string.h>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);  // 读取输入的 n 和 x
    char num_str[10];        // 存储转换后的数字字符串
    int count = 0;           // 用于计数 x 出现的次数
    char target = x + '0';   // 将数字 x 转换为字符

    for (int i = 1; i <= n; i++) {
        sprintf(num_str, "%d", i);  // 将数字 i 转换为字符串
        for (int j = 0; j < strlen(num_str); j++) {
            if (num_str[j] == target) {
                count++;            // 如果当前字符等于目标字符 x，计数加1
            }
        }
    }

    printf("%d\n", count);  // 输出 x 出现的次数

    return 0;
}