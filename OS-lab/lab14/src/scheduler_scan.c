#include <stdio.h>

#include "disk_scheduler.h"

void Oneway_scan(void)
{
    struct scheduler_snapshot snapshot;
    int sorted[N];

    printf("\n***********单向扫描过程***********\n");
    in();
    clear_result();
    capture_snapshot(&snapshot);
    sort_requests_copy(sorted, snapshot.requests, snapshot.request_count);

    int split = split_index_from_current(sorted, snapshot.request_count, snapshot.current_cylinder);
    int count = 0;
    int i;

    /*
     * TODO:
     * 1. 用 split_index_from_current() 找到左右分界点。
     * 2. 先访问 sorted[] 中右半部分请求。
     * 3. 再加入 199、0，最后访问左半部分请求。
     */
    result[count++] = snapshot.current_cylinder;
    for (i = split; i < snapshot.request_count; ++i) {
        result[count++] = sorted[i];
    }
    result[count++] = MAX_CYLINDER;
    result[count++] = 0;
    for (i = 0; i < split; ++i) {
        result[count++] = sorted[i];
    }

    print_path("单向扫描移动的顺序为：", result, count);
    printf("移动柱面为：%d\n", calc_total_movement(result, count));
}

void Twoway_scan(void)
{
    struct scheduler_snapshot snapshot;
    int sorted[N];

    printf("\n***********双向扫描过程***********\n");
    in();
    clear_result();
    capture_snapshot(&snapshot);
    sort_requests_copy(sorted, snapshot.requests, snapshot.request_count);

    int split2 = split_index_from_current(sorted, snapshot.request_count, snapshot.current_cylinder);
    int count2 = 0;
    int i2;

    /*
     * TODO:
     * 1. 先访问不小于当前柱面的请求。
     * 2. 到达 199 后折返。
     * 3. 逆序访问左半部分请求，不要额外空扫到 0。
     */
    result[count2++] = snapshot.current_cylinder;
    for (i2 = split2; i2 < snapshot.request_count; ++i2) {
        result[count2++] = sorted[i2];
    }
    result[count2++] = MAX_CYLINDER;
    for (i2 = split2 - 1; i2 >= 0; --i2) {
        result[count2++] = sorted[i2];
    }

    print_path("双向扫描移动的顺序为：", result, count2);
    printf("移动柱面为：%d\n", calc_total_movement(result, count2));
}

void Elevator(void)
{
    struct scheduler_snapshot snapshot;
    int sorted[N];

    printf("\n***********电梯调度过程***********\n");
    in();
    clear_result();
    capture_snapshot(&snapshot);
    sort_requests_copy(sorted, snapshot.requests, snapshot.request_count);

    int split3 = split_index_from_current(sorted, snapshot.request_count, snapshot.current_cylinder);
    int count3 = 0;
    int i3;

    /*
     * TODO:
     * 1. 本实验按样例实现为 LOOK 风格。
     * 2. 先访问小于当前柱面的请求，再反向访问较大请求。
     * 3. 不强制走到边界柱面，只在真实请求间折返。
     */
    result[count3++] = snapshot.current_cylinder;
    for (i3 = split3 - 1; i3 >= 0; --i3) {
        result[count3++] = sorted[i3];
    }
    for (i3 = split3; i3 < snapshot.request_count; ++i3) {
        result[count3++] = sorted[i3];
    }

    print_path("电梯调度(由里向外)移动的顺序为：", result, count3);
    printf("移动柱面为：%d\n", calc_total_movement(result, count3));
}
