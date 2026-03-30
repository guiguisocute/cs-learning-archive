#ifndef PARTITION_H
#define PARTITION_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_PARTITIONS 110
#define MAX_JOBS 1000000
#define JOB_NAME_LEN 32

typedef struct partition_info {
    int id;
    int size_kb;
    int start_kb;
    char status[JOB_NAME_LEN];
} partition_info;

extern int n;
extern int m;
extern int job_sizes[MAX_JOBS + 5];
extern partition_info partitions[MAX_PARTITIONS];

partition_info input(void);
void print(void);
bool allocate_job_to_partition(int job_index);
bool recycle_job_by_name(const char *raw_name);
void normalize_job_name(const char *raw_name, char *normalized, size_t normalized_size);

#endif
