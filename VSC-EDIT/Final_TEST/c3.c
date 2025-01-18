#include <stdio.h>

int main() {
    int roosters, hens, chicks;
    int found = 0; // 标记是否找到解

    printf("公鸡\t母鸡\t小鸡\n");
    printf("---------------------\n");

    // 公鸡的价格是5文钱一只，最多可以买20只（5 * 20 = 100）
    for (roosters = 1; roosters <= 20; roosters++) {
        // 母鸡的价格是3文钱一只，至少买1只，最多买(100 - 公鸡数量)只
        for (hens = 1; hens <= 100 - roosters; hens++) {
            chicks = 100 - roosters - hens; // 小鸡的数量

            // 小鸡3只一文钱，必须能被3整除
            if (chicks % 3 != 0) {
                continue;
            }

            // 计算总花费
            // 公鸡5文钱一只，母鸡3文钱一只，小鸡3只1文钱
            // 总花费 = 5 * roosters + 3 * hens + (chicks / 3)
            if (5 * roosters + 3 * hens + (chicks / 3) == 100) {
                printf("%d\t%d\t%d\n", roosters, hens, chicks);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("没有符合条件的解。\n");
    }

    return 0;
}
