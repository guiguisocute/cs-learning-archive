#include<stdio.h>
#include<stdlib.h>

int main() {
    int n, a, b, c, a_p, b_p, c_p;
    scanf("%d", &n);
    scanf("%d %d", &a, &a_p);
    scanf("%d %d", &b, &b_p);
    scanf("%d %d", &c, &c_p);

    // 计算买够 n 支铅笔所需要的最小费用
    int sum1 = ((n + a - 1) / a) * a_p;  // 用整数来处理，n+a-1是为了向上取整
    int sum2 = ((n + b - 1) / b) * b_p;
    int sum3 = ((n + c - 1) / c) * c_p;

    // 直接比较三种价格
    int min = sum1;  // 假设第一种方案是最小的
    if (sum2 < min) {
        min = sum2;  // 如果第二种方案更小，更新 min
    }
    if (sum3 < min) {
        min = sum3;  // 如果第三种方案更小，更新 min
    }

    printf("%d\n", min);

    system("pause");
    return 0;
}