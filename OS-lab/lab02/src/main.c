#include <stdio.h>

#include "fcfs.h"

int main(void) {
    // TODO: 按实验要求组织主流程。
    // 建议步骤：
    // 1. 读取用户操作
    // 2. 初始化队列
    // 3. 调用 read_processes() 读取进程
    // 4. 调用 run_fcfs_schedule() 执行调度
    // 5. 调用 print_schedule_results() 输出结果
    // 6. 释放链表结点

    int op = 0;
    while (1)
    {
        printf("请输入操作(1:开始进程调度；0:结束进程)：");
        if (scanf("%d", &op) != 1 || op == 0)
        {
            printf("\n操作结束！\n");
            break;
        }

        ProcessQueue x;
        init_process_queue(&x);
        read_processes(&x);
        run_fcfs_schedule(&x);
        print_schedule_results(&x);

        while (x.front != NULL)
        {
            remove_front_process(&x);
        }

        printf("\n");
    }

    return 0;
}
