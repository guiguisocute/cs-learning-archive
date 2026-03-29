#include "rr_lab.h"

#include <stdio.h>

int main(void)
{
    int flag;

    while (1)
    {
        printf("请输入操作(1:开始进程;0:结束进程):");
        if (scanf("%d", &flag) != 1)
        {
            return 1;
        }

        if (flag == 0)
        {
            printf("\n操作结束!\n");
            break;
        }

        if (flag == 1)
        {
            Queue *wait;
            int n;
            int t;

            printf("请输入进程数:\n");
            if (scanf("%d", &n) != 1 || n <= 0)
            {
                return 1;
            }

            printf("请输入时间片时间:\n");
            if (scanf("%d", &t) != 1 || t <= 0)
            {
                return 1;
            }

            wait = init();
            if (wait == NULL)
            {
                return 1;
            }

            ScanIn(wait, n);
            Time_or_Name_Sorted(wait, 1);
            wait = Time_Slice_Rotation(wait, t);
            Time_or_Name_Sorted(wait, 0);
            Print(wait, n);
            FreeQueue(wait);
            wait = init();
        }
        else
        {
            printf("输入无效，请重新输入!\n");
        }
    }

    return 0;
}
