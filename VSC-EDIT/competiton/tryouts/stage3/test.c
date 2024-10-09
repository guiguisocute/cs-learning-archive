#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define lli long long int

// 定义一个精度误差范围
#define EPS 1e-9

int main() {
    lli x;
    scanf("%lld", &x);
    
    // 计算可能的等边三角形边长 a
    double a = sqrt((4.0 * x) / sqrt(3.0));
    lli int_a = (lli)(a + 0.5);  // 将浮点数四舍五入为最近的整数

    // 正方形的判断
    if (fabs(sqrt(x) - (lli)sqrt(x)) < EPS && fabs((sqrt(3.0) / 4.0 * (int_a * int_a)) - x) < EPS) {
        printf("2\n");  // 既是正方形又是等边三角形
    } else if (fabs(sqrt(x) - (lli)sqrt(x)) < EPS) {
        printf("0\n");  // 仅为正方形
    } else if (fabs((sqrt(3.0) / 4.0 * (int_a * int_a)) - x) < EPS) {
        printf("1\n");  // 仅为等边三角形
    } else {
        printf("3\n");  // 两者皆不可能
    }

    system("pause");
    return 0;
}