#include <stdio.h>

int main() {
    // 判断是 C 还是 C++
    #ifdef __cplusplus
        // 处理 C++ 版本
        printf("C++ Version: ");
        #if __cplusplus == 202002L
            printf("C++20\n");
        #elif __cplusplus == 201703L
            printf("C++17\n");
        #elif __cplusplus == 201402L
            printf("C++14\n");
        #elif __cplusplus == 201103L
            printf("C++11\n");
        #elif __cplusplus == 199711L
            printf("C++98\n");
        #else
            printf("Unknown C++ Standard (__cplusplus = %ld)\n", __cplusplus);
        #endif
    #else
        // 处理 C 版本
        printf("C Version: ");
        #ifdef __STDC_VERSION__
            #if __STDC_VERSION__ >= 201710L
                printf("C17 (C18)\n");
            #elif __STDC_VERSION__ >= 201112L
                printf("C11\n");
            #elif __STDC_VERSION__ >= 199901L
                printf("C99\n");
            #else
                printf("C89/C90 (__STDC_VERSION__ = %ld)\n", __STDC_VERSION__);
            #endif
        #else
            // __STDC_VERSION__ 未定义，可能是 C89 或更早
            #ifdef __STDC__
                printf("C89/C90 (ANSI C)\n");
            #else
                printf("Pre-ANSI C\n");
            #endif
        #endif
    #endif

    return 0;
}