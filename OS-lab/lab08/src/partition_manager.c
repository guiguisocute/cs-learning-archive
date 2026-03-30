#include "partition_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static node *create_partition_node(int size, int address, const char *flag)
{
    node *part = (node *)malloc(sizeof(node));

    if (part == NULL)
    {
        return NULL;
    }

    part->size = size;
    part->address = address;
    part->next = NULL;
    strncpy(part->flag, flag, FLAG_LEN - 1);
    part->flag[FLAG_LEN - 1] = '\0';
    return part;
}

static void destroy_list(node *head)
{
    node *current = head;

    while (current != NULL)
    {
        node *next = current->next;
        free(current);
        current = next;
    }
}

static void print_table(const char *title, const node *head)
{
    int index = 1;
    const node *current = head;

    printf("%s:\n", title);
    printf("分区号    大小(KB)        起始(KB)        状态\n");

    while (current != NULL)
    {
        printf("%3d%12d%16d%15s\n", index, current->size, current->address, current->flag);
        current = current->next;
        index++;
    }
}

void init_partition_tables(partitionTables *tables, int total_size_kb, int base_address_kb)
{
    if (tables == NULL)
    {
        return;
    }

    tables->memory.size = total_size_kb;
    tables->memory.address = base_address_kb;
    tables->allocated_head = NULL;
    tables->free_head = create_partition_node(total_size_kb, base_address_kb, "空闲");
    tables->next_job_id = 1;
}

void destroy_partition_tables(partitionTables *tables)
{
    if (tables == NULL)
    {
        return;
    }

    destroy_list(tables->allocated_head);
    destroy_list(tables->free_head);
    tables->allocated_head = NULL;
    tables->free_head = NULL;
}

bool allocate_partition(partitionTables *tables, const job *new_job, allocationPolicy policy)
{
    /*
     * TODO(学生实现):
     * 1. 根据 policy 在未分配分区表中选择目标空闲分区:
     *    - 最先适应
     *    - 最优适应
     *    - 最坏适应
     * 2. 检查分区是否足够容纳 new_job->size。
     * 3. 将目标空闲分区一分为二:
     *    - 前半部分写入已分配分区表，flag 设为作业名
     *    - 剩余部分保留在未分配分区表
     * 4. 如果剩余大小为 0，注意从未分配分区表中移除该分区。
     * 5. 维护链表按起始地址有序，方便后续回收合并。
     */

    node *prev_target = NULL;
    node *target = NULL;
    node *prev = NULL;
    node *current = tables->free_head;

    while (current != NULL)
    {
        if (current->size >= new_job->size)
        {
            if (target == NULL)
            {
                target = current;
                prev_target = prev;
            }
            else if (policy == POLICY_BEST_FIT && current->size < target->size)
            {
                target = current;
                prev_target = prev;
            }
            else if (policy == POLICY_WORST_FIT && current->size > target->size)
            {
                target = current;
                prev_target = prev;
            }

            if (policy == POLICY_FIRST_FIT)
            {
                break;
            }
        }
        prev = current;
        current = current->next;
    }

    if (target == NULL)
    {
        return false;
    }

    node *allocated = create_partition_node(new_job->size, target->address, new_job->name);
    if (allocated == NULL)
    {
        return false;
    }

    int remaining = target->size - new_job->size;
    if (remaining > 0)
    {
        target->address += new_job->size;
        target->size = remaining;
    }
    else
    {
        if (prev_target == NULL)
        {
            tables->free_head = target->next;
        }
        else
        {
            prev_target->next = target->next;
        }
        free(target);
    }

    node *aprev = NULL;
    node *acur = tables->allocated_head;
    while (acur != NULL && acur->address < allocated->address)
    {
        aprev = acur;
        acur = acur->next;
    }
    allocated->next = acur;
    if (aprev == NULL)
    {
        tables->allocated_head = allocated;
    }
    else
    {
        aprev->next = allocated;
    }

    return true;
}

bool reclaim_partition(partitionTables *tables, const char *job_name)
{
    /*
     * TODO(学生实现):
     * 1. 在已分配分区表中按作业名查找目标分区。
     * 2. 将该分区从已分配分区表移除，插入未分配分区表的正确位置。
     * 3. 分别处理四种合并场景:
     *    - 无上邻无下邻
     *    - 有上邻无下邻
     *    - 无上邻有下邻
     *    - 有上邻有下邻
     * 4. 保持未分配分区表按地址递增，便于观察和调试。
     */

    node *prev = NULL;
    node *current = tables->allocated_head;
    while (current != NULL && strcmp(current->flag, job_name) != 0)
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
    {
        return false;
    }

    if (prev == NULL)
    {
        tables->allocated_head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    int addr = current->address;
    int size = current->size;
    free(current);

    node *fprev = NULL;
    node *fcur = tables->free_head;
    while (fcur != NULL && fcur->address < addr)
    {
        fprev = fcur;
        fcur = fcur->next;
    }

    bool merged_upper = false;
    bool merged_lower = false;

    if (fprev != NULL && fprev->address + fprev->size == addr)
    {
        fprev->size += size;
        merged_upper = true;
    }

    if (fcur != NULL && addr + size == fcur->address)
    {
        merged_lower = true;
    }

    if (merged_upper && merged_lower)
    {
        fprev->size += fcur->size;
        fprev->next = fcur->next;
        free(fcur);
    }
    else if (!merged_upper && merged_lower)
    {
        fcur->address = addr;
        fcur->size += size;
    }
    else if (!merged_upper && !merged_lower)
    {
        node *new_node = create_partition_node(size, addr, "空闲");
        new_node->next = fcur;
        if (fprev == NULL)
        {
            tables->free_head = new_node;
        }
        else
        {
            fprev->next = new_node;
        }
    }

    return true;
}

void print_partition_report(const partitionTables *tables)
{
    printf("*******************主存分配情况*******************\n");

    if (tables == NULL)
    {
        print_table("已分配", NULL);
        print_table("未分配", NULL);
        return;
    }

    print_table("已分配", tables->allocated_head);
    print_table("未分配", tables->free_head);
}

void print_main_menu(void)
{
    printf("*******************可变分区管理*******************\n");
    printf("* 1. 内存管理        *\n");
    printf("* 2. 内存去配        *\n");
    printf("* 0. 退出           *\n");
    printf("************************************************\n");
}

void print_policy_menu(void)
{
    printf("*******************分配算法*******************\n");
    printf("* 1. 最先适应算法    *\n");
    printf("* 2. 最优适应算法    *\n");
    printf("* 3. 最坏适应算法    *\n");
    printf("********************************************\n");
}
