#include <stdio.h>
#include <stdlib.h>

int main() {
    int t;
    int apple[10];

    // 读取10个苹果的高度
    for (int i = 0; i < 10; i++) {
        scanf("%d", &apple[i]);
    }

    // 读取陶陶的最大可达到高度，并加上板凳高度
    scanf("%d", &t);
    t += 30;

    int count = 0;  // 用于记录陶陶能摘到的苹果数

    // 遍历所有苹果的高度
    for (int i = 0; i < 10; i++) {
        if (apple[i] <= t) {
            count++;  // 如果陶陶能达到这个苹果，则增加计数
        }
    }

    // 输出陶陶能摘到的苹果数量
    printf("%d\n", count);

    system("pause");  // 等待用户操作后退出
    return 0;
}