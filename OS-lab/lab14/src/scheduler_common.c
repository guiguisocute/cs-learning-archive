#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "disk_scheduler.h"

void clear_result(void)
{
    memset(result, 0, sizeof(result));
}

void capture_snapshot(struct scheduler_snapshot *snapshot)
{
    snapshot->request_count = length;
    snapshot->current_cylinder = now;
    for (int i = 0; i < length; ++i) {
        snapshot->requests[i] = sequence[i];
    }
}

void print_path(const char *label, const int *path, int count)
{
    printf("\n%s\n", label);
    for (int i = 0; i < count; ++i) {
        printf("%d", path[i]);
        if (i + 1 < count) {
            printf(" ");
        }
    }
    printf("\n");
}

int calc_total_movement(const int *path, int count)
{
    int total = 0;

    for (int i = 1; i < count; ++i) {
        int diff = path[i] - path[i - 1];
        total += diff >= 0 ? diff : -diff;
    }

    return total;
}

static int cmp_int_asc(const void *lhs, const void *rhs)
{
    const int *a = lhs;
    const int *b = rhs;

    return (*a > *b) - (*a < *b);
}

void sort_requests_copy(int *dst, const int *src, int count)
{
    for (int i = 0; i < count; ++i) {
        dst[i] = src[i];
    }
    qsort(dst, (size_t)count, sizeof(dst[0]), cmp_int_asc);
}

int split_index_from_current(const int *sorted, int count, int current_cylinder)
{
    int split = 0;

    while (split < count && sorted[split] < current_cylinder) {
        ++split;
    }

    return split;
}

void print_todo_notice(const char *function_name, const char *next_hint)
{
    printf("[TODO] 请在 %s 中补全核心调度逻辑。\n", function_name);
    printf("当前脚手架保留了工程化输入输出与公共工具，但没有替你完成算法。\n");
    printf("下一步建议：%s\n", next_hint);
}
