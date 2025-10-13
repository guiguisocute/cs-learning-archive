#include <stdio.h>
#include <stdlib.h>

int main() {
    // 输出 C 语言标准版本
    printf("C Standard Version: %ld\n", __STDC_VERSION__);

    // 检查是否是 C23 版本
    #if __STDC_VERSION__ >= 202300L
        printf("You are using C23 or later.\n");
    #else
        printf("You are using a pre-C23 standard.\n");
    #endif

}