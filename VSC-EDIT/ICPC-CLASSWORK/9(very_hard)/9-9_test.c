#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);  // 读取矩阵大小

    int matrix[N][N];  // 存储生成的点阵矩阵
    int index = 0;     // 当前矩阵填充的总个数
    int fill = 0;      // 交替填充 0 和 1

    // 填充矩阵
    while (index < N * N) {
        int count;
        scanf("%d", &count);  // 读取压缩码中的一个数字
        for (int j = 0; j < count; j++) {
            matrix[index / N][index % N] = fill;  // 按行列顺序填充
            index++;
        }
        fill = 1 - fill;  // 交替填充 0 和 1
    }

    // 输出结果矩阵
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}