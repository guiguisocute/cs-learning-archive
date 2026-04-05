#include <stdio.h>
#include <stdlib.h>

#include "disk_scheduler.h"

void app_run(void)
{
    while (1) {
        int choice = 0;

        Out();
        if (scanf("%d", &choice) != 1) {
            printf("\n输入结束，程序退出。\n");
            return;
        }
        printf("]\n");

        switch (choice) {
        case 1:
            FCFS();
            break;
        case 2:
            SSTF();
            break;
        case 3:
            Oneway_scan();
            break;
        case 4:
            Twoway_scan();
            break;
        case 5:
            Elevator();
            break;
        default:
            printf("\n调度结束！");
            exit(1);
        }
    }
}
