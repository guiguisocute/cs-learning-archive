#include "partition.h"

#include <stdio.h>
#include <string.h>

int n = 0;
int m = 0;
int job_sizes[MAX_JOBS + 5];
partition_info partitions[MAX_PARTITIONS];

static bool is_partition_free(const partition_info *entry) {
    return entry->status[0] == '\0';
}

void normalize_job_name(const char *raw_name, char *normalized, size_t normalized_size) {
    if (normalized_size == 0U) {
        return;
    }

    if (raw_name == NULL || raw_name[0] == '\0') {
        normalized[0] = '\0';
        return;
    }

    if (strncmp(raw_name, "JOB", 3) == 0) {
        snprintf(normalized, normalized_size, "%s", raw_name);
        return;
    }

    snprintf(normalized, normalized_size, "JOB%s", raw_name);
}

partition_info input(void) {
    partition_info entry;

    /* TODO: 学生可在这里补充输入校验或更严格的初始化策略。 */
    scanf("%d%d%d", &entry.id, &entry.size_kb, &entry.start_kb);
    entry.status[0] = '\0';
    return entry;
}

void print(void) {
    int i;

    /* TODO: 如果老师要求严格对齐输出，可在这里继续调整表格格式。 */
    puts("**********打印分区信息**********");
    puts("分区号\t大小(KB)\t起址(KB)\t状态");
    for (i = 1; i <= n; ++i) {
        printf("%d\t%d\t\t%d\t\t", partitions[i].id, partitions[i].size_kb, partitions[i].start_kb);
        if (is_partition_free(&partitions[i])) {
            puts("0");
        } else {
            puts(partitions[i].status);
        }
    }
}

bool allocate_job_to_partition(int job_index) {
    /*
     * TODO:
     * 1. 按分区表顺序查找第一个"容量足够且空闲"的分区。
     * 2. 找到后把状态改成 JOB1 / JOB2 / JOB3 这样的作业名。
     * 3. 若没有合适分区，返回 false。
     */
    int i;
    char job_name[JOB_NAME_LEN];

    snprintf(job_name, sizeof(job_name), "JOB%d", job_index);
    for (i = 1; i <= n; ++i) {
        if (partitions[i].size_kb >= job_sizes[job_index] && is_partition_free(&partitions[i])) {
            snprintf(partitions[i].status, sizeof(partitions[i].status), "%s", job_name);
            return true;
        }
    }

    return false;
}

bool recycle_job_by_name(const char *raw_name) {
    /*
     * TODO:
     * 1. 兼容输入 "2" 和 "JOB2" 两种形式，可先规范化成统一作业名。
     * 2. 遍历分区表，找到状态等于该作业名的分区。
     * 3. 将状态清空，表示该分区重新空闲。
     */
    int i;
    char normalized[JOB_NAME_LEN];

    normalize_job_name(raw_name, normalized, sizeof(normalized));
    for (i = 1; i <= n; ++i) {
        if (strcmp(partitions[i].status, normalized) == 0) {
            partitions[i].status[0] = '\0';
            return true;
        }
    }

    return false;
}
