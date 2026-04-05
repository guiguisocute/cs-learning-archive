#include <stdio.h>
#include <string.h>

#include "disk_scheduler.h"

int length = 0;
int sequence[N];
int result[N];
int now = 0;

void in(void)
{
    printf("请输入访问序列的长度：");
    scanf("%d", &length);

    printf("请输入访问的柱面顺序：");
    for (int i = 0; i < length; ++i) {
        scanf("%d", &sequence[i]);
    }

    printf("请输入正在访问的柱面：");
    scanf("%d", &now);
}

void Out(void)
{
    printf("\n*****************磁盘驱动调度*****************\n");
    printf("* 1. FCFS           *\n");
    printf("* 2. SSTF           *\n");
    printf("* 3. 单向扫描       *\n");
    printf("* 4. 双向扫描       *\n");
    printf("* 5. 电梯调度       *\n");
    printf("* 0. 退出           *\n");
    printf("            请输入选项[");
}
