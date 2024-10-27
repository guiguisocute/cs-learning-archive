#include <stdio.h>

// 函数：二进制转十进制
unsigned long long binaryToDecimal(int binary) {
    unsigned long long decimal = 0;
    unsigned long long base = 1; // 2^0

    while(binary > 0) {
        // 获取最低位
        int last_bit = binary & 1;
        // 累加到十进制结果
        decimal += last_bit * base;
        // 更新权值（乘以2）
        base <<= 1; // 相当于 base *= 2
        // 右移一位，处理下一个二进制位
        binary >>= 1;
    }

    return decimal;
}

int main() {
    int binary;
    printf("请输入一个二进制数（不带前导零）：");
    scanf("%d", &binary);

    unsigned long long decimal = binaryToDecimal(binary);
    printf("%llu",decimal);
    return 0;
}




