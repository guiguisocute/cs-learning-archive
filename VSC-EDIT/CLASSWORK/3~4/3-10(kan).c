#include <stdio.h>
#include<stdlib.h>

int main() {
    char isbn[13];
    int sum = 0;
    int k = 0;

    scanf("%s", isbn);

    // 计算前9位数字的和
    for (int i = 0; i < 11; i++) {
        if (isbn[i] != '-') {
            sum += (isbn[i] - '0') * (++k);
        }
    }

    // 计算校验码
    int checksum = sum % 11;
    char expected_check_digit;
    if (checksum == 10) {
        expected_check_digit = 'X';
    } else {
        expected_check_digit = '0' + checksum;
    }

    // 比较输入的校验码和计算出的校验码
    if (isbn[12] == expected_check_digit) {
        printf("Right\n");
    } else {
        isbn[12] = expected_check_digit;  // 修正校验码
        printf("%s\n", isbn);
    }

    system("pause");
    return 0;
}