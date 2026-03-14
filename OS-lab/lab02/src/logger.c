#include <stdio.h>

#include "logger.h"

void print_time_point(TimePoint time_point) {
    // TODO: 按 hh:mm 形式输出时间。
    printf("%02d:%02d", time_point.hour, time_point.min);
}

void print_ready_queue(ProcessQueue *queue) {
    // TODO: 输出当前就绪队列。
    // 示例：
    // 当前就绪队列: 李小龙1(09:40) 李小龙2(09:55)
    ProcessNode *current_process = queue->front;

    printf("当前就绪队列: ");
    while (current_process != NULL)
    {
        printf("%s(", current_process->process_name);
        print_time_point(current_process->arrival_time);
        printf(")");
        if (current_process->next != NULL)
        {
            printf(" ");
        }
        current_process = current_process->next;
    }
    printf("\n");
}

void print_fcfs_dispatch_reason(ProcessNode *process_node) {
    // TODO: 输出“为什么当前选中这个进程”。
    // FCFS 的固定理由是：按到达顺序先来先服务
    if (process_node == NULL)
    {
        return;
    }

    printf("调度进程: %s，原因: FCFS 按到达顺序先来先服务\n", process_node->process_name);
}
