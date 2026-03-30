#include "partition_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void read_line(char *buffer, size_t size)
{
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}

static int read_int(void)
{
    char buffer[64] = {0};
    read_line(buffer, sizeof(buffer));
    return (int)strtol(buffer, NULL, 10);
}

static void handle_allocate(partitionTables *tables)
{
    job new_job = {0};
    int policy_value = 0;

    print_policy_menu();
    printf("请输入选项: ");
    policy_value = read_int();

    if (policy_value < POLICY_FIRST_FIT || policy_value > POLICY_WORST_FIT)
    {
        printf("分配算法选项无效!\n");
        return;
    }

    new_job.id = tables->next_job_id;
    printf("请输入作业名: ");
    read_line(new_job.name, sizeof(new_job.name));
    printf("%s需要分配的主存大小(单位: KB): ", new_job.name);
    new_job.size = read_int();

    if (new_job.size <= 0)
    {
        printf("作业大小必须大于 0!\n");
        return;
    }

    if (allocate_partition(tables, &new_job, (allocationPolicy)policy_value))
    {
        tables->next_job_id++;
        printf("分配成功!\n");
    }
    else
    {
        printf("分配失败! 当前脚手架保留为 TODO，请在 allocate_partition 中补全算法。\n");
    }

    print_partition_report(tables);
}

static void handle_reclaim(partitionTables *tables)
{
    char job_name[JOB_NAME_LEN] = {0};

    printf("请输入要回收的作业名: ");
    read_line(job_name, sizeof(job_name));

    if (reclaim_partition(tables, job_name))
    {
        printf("回收成功!\n");
    }
    else
    {
        printf("回收失败! 当前脚手架保留为 TODO，请在 reclaim_partition 中补全算法。\n");
    }

    print_partition_report(tables);
}

int main(void)
{
    partitionTables tables = {0};
    int option = -1;

    init_partition_tables(&tables, DEFAULT_MEMORY_SIZE_KB, DEFAULT_MEMORY_BASE_KB);

    while (option != 0)
    {
        print_main_menu();
        printf("请输入选项: ");
        option = read_int();

        switch (option)
        {
            case 1:
                handle_allocate(&tables);
                break;
            case 2:
                handle_reclaim(&tables);
                break;
            case 0:
                break;
            default:
                printf("菜单选项无效，请重新输入。\n");
                break;
        }

        if (option == 0)
        {
            break;
        }

        printf("\n");
    }

    destroy_partition_tables(&tables);
    return 0;
}
