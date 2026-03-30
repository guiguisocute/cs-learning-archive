#ifndef PARTITION_MANAGER_H
#define PARTITION_MANAGER_H

#include <stdbool.h>

#define FLAG_LEN 20
#define JOB_NAME_LEN 20
#define DEFAULT_MEMORY_SIZE_KB 256
#define DEFAULT_MEMORY_BASE_KB 40

typedef enum allocation_policy
{
    POLICY_FIRST_FIT = 1,
    POLICY_BEST_FIT = 2,
    POLICY_WORST_FIT = 3
} allocationPolicy;

// 内存结构体
typedef struct memory_node
{
    int size;    // 内存大小
    int address; // 内存始址
} memoryNode;

// 分区结构体
typedef struct link_node
{
    int size;                 // 分区大小
    int address;              // 分区始址
    char flag[FLAG_LEN];      // 分区状态，空闲或者占用作业名
    struct link_node *next;
} node;

// 作业结构体
typedef struct job_node
{
    int id;                    // 作业编号
    char name[JOB_NAME_LEN];   // 作业名
    int size;                  // 作业大小
} job;

typedef struct partition_tables
{
    memoryNode memory;
    node *allocated_head;
    node *free_head;
    int next_job_id;
} partitionTables;

void init_partition_tables(partitionTables *tables, int total_size_kb, int base_address_kb);
void destroy_partition_tables(partitionTables *tables);

bool allocate_partition(partitionTables *tables, const job *new_job, allocationPolicy policy);
bool reclaim_partition(partitionTables *tables, const char *job_name);

void print_partition_report(const partitionTables *tables);
void print_main_menu(void);
void print_policy_menu(void);

#endif
