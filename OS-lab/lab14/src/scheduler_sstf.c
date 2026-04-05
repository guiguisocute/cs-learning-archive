#include <stdio.h>

#include "disk_scheduler.h"

void SSTF(void)
{
    struct scheduler_snapshot snapshot;

    printf("\n***********SSTF磁盘移臂调度过程***********\n");
    in();
    clear_result();
    capture_snapshot(&snapshot);
    int visited[N] = {0};
    int current;
    int count = 0;
    int step;
    int i;

    /*
     * TODO:
     * 1. 设计 visited[]，跟踪哪些请求已经处理。
     * 2. 从 snapshot.current_cylinder 开始，每轮选择最近的未访问柱面。
     * 3. 把选择结果写入 result[]，最后计算总移臂量。
     */
    current = snapshot.current_cylinder;
    result[count++] = current;

    for (step = 0; step < snapshot.request_count; ++step) {
        int best_index = -1;
        int best_distance = MAX_CYLINDER + 1;

        for (i = 0; i < snapshot.request_count; ++i) {
            if (visited[i]) {
                continue;
            }
            int distance = snapshot.requests[i] - current;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < best_distance) {
                best_distance = distance;
                best_index = i;
            }
        }

        visited[best_index] = 1;
        current = snapshot.requests[best_index];
        result[count++] = current;
    }

    print_path("最短优先的顺序为：", result, count);
    printf("移动柱面为：%d\n", calc_total_movement(result, count));
}
