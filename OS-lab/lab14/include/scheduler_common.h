#ifndef SCHEDULER_COMMON_H
#define SCHEDULER_COMMON_H

#include "scheduler_api.h"

struct scheduler_snapshot {
    int request_count;
    int current_cylinder;
    int requests[N];
};

void clear_result(void);
void capture_snapshot(struct scheduler_snapshot *snapshot);
void print_path(const char *label, const int *path, int count);
int calc_total_movement(const int *path, int count);
void sort_requests_copy(int *dst, const int *src, int count);
int split_index_from_current(const int *sorted, int count, int current_cylinder);
void print_todo_notice(const char *function_name, const char *next_hint);

#endif
