#include "priority_scheduler.h"

#include <stdio.h>

int main(void)
{
    int flag;

    while (1)
    {
        printf("请输入操作:(1:开始进程;-1:结束进程):");
        if (scanf("%d", &flag) != 1)
        {
            return 1;
        }

        if (flag == -1)
        {
            printf("\n操作结束!\n");
            break;
        }

        if (flag == 1)
        {
            Queue *wait;
            Queue *result;
            int process_count;
            time current_time;

            printf("请输入进程数量:");
            if (scanf("%d", &process_count) != 1 || process_count <= 0)
            {
                return 1;
            }

            wait = init();
            if (wait == NULL)
            {
                return 1;
            }

            current_time = ScanIn(wait, process_count);
            result = priority(wait, current_time, process_count);
            if (result == NULL)
            {
                return 1;
            }

            Print(result, process_count);
            FreeQueue(result);
        }
        else
        {
            printf("输入无效，请重新输入!\n");
        }
    }

    return 0;
}
