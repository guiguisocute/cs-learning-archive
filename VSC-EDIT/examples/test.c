#include <stdio.h>
#include <string.h>

int main() {
    int N;
    char line[201]; // 行缓冲区
    scanf("%s", line);
    N = strlen(line); // 获取 N 的值
    char grid[200][201]; // 点阵图数组
    strcpy(grid[0], line); // 复制第一行
    for (int i = 1; i < N; i++) {
        scanf("%s", grid[i]); // 读取剩余的行
    }

    char current_char = grid[0][0]; // 初始化当前字符
    int count = 0; // 初始化计数器
    printf("%d", N); // 输出 N

    for (int i = 0; i < N; i++) { // 遍历每一行
        for (int j = 0; j < N; j++) { // 遍历每一列
            if (grid[i][j] == current_char) {
                count++; // 相同字符，计数加一
            } else {
                printf(" %d", count); // 输出当前计数
                current_char = grid[i][j]; // 更新当前字符
                count = 1; // 重置计数器
            }
        }
    }
    printf(" %d\n", count); // 输出最后一个计数

    return 0;
}