#include <stdio.h>

#include "disk_scheduler.h"

void FCFS(void)
{
    struct scheduler_snapshot snapshot;

    printf("\n************FCFS磁盘移臂调度过程************\n");
    in();
    clear_result();
    capture_snapshot(&snapshot);
    int count = 0;
    int i;

    /*
     * TODO:
     * 1. 按 snapshot.requests[] 的原始顺序，依次写入 result[]。
     * 2. 维护结果长度 count，并让起始柱面始终位于 result[0]。
     * 3. 用 calc_total_movement() 输出最终总移臂量。
     */
    result[count++] = snapshot.current_cylinder;
    for (i = 0; i < snapshot.request_count; ++i) {
        result[count++] = snapshot.requests[i];
    }

    print_path("移动的顺序为:", result, count);
    printf("移动柱面为: %d\n", calc_total_movement(result, count));
}
