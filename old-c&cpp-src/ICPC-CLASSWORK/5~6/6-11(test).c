#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    // 计算第 n 行的最大宽度
    int max_width = n * 6 - 1;  // 每个乘法式 "x* y= z" 占 6 个字符

    for (int i = 1; i <= n; i++) {
        // 计算当前行的宽度
        int current_width = i * 6 - 1;

        // 输出前导空格，保证右对齐
        for (int space = 0; space < max_width - current_width; space++) {
            printf(" ");
        }

        // 输出乘法表达式
        for (int j = i; j >= 1; j--) {
            printf("%d*%2d=%2d", i, j, i * j);
            if (j > 1) {
                printf(" ");  // 数字之间留一个空格
            }
        }

        // 每行结束后换行
        printf("\n");
    }

    return 0;
}