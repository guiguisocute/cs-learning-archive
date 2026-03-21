#include <stdio.h>

#include "sjf_lab.h"

int main(void) {
    for (;;) {
        int operation = 0;
        process_queue *proc_queue = NULL;

        printf("请输入操作(1：开始进程调度；-1：结束进程）");
        fflush(stdout);
        if (scanf("%d", &operation) != 1) {
            break;
        }

        if (operation == -1 || operation == 0) {
            break;
        }

        if (operation != 1) {
            printf("无效操作，请重新输入。\n");
            continue;
        }

        proc_queue = queue_create();
        schedule_input(proc_queue);
        run_sjf_schedule(proc_queue);
        queue_destroy(proc_queue);
    }

    return 0;
}
