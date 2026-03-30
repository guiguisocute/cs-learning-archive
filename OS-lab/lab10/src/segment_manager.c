#include "segment_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static memoryNode g_memory = {0};
static node *g_allocated_head = NULL;
static node *g_free_head = NULL;
static segmentNode *g_segment_head = NULL;

static int read_int(void)
{
    int value = 0;
    scanf("%d", &value);
    return value;
}

static node *create_partition(int size, int address, const char *flag)
{
    node *part = (node *)calloc(1, sizeof(node));

    if (part == NULL)
    {
        return NULL;
    }

    part->size = size;
    part->address = address;
    strncpy(part->flag, flag, FLAG_LEN - 1);
    part->flag[FLAG_LEN - 1] = '\0';
    return part;
}

static segmentNode *find_segment_table(const char *job_name)
{
    segmentNode *current = g_segment_head;

    while (current != NULL)
    {
        if (strcmp(current->job_name, job_name) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

static segmentNode *create_segment_table(const char *job_name)
{
    segmentNode *table = (segmentNode *)calloc(1, sizeof(segmentNode));

    if (table == NULL)
    {
        return NULL;
    }

    strncpy(table->job_name, job_name, JOB_NAME_LEN - 1);
    table->job_name[JOB_NAME_LEN - 1] = '\0';
    table->next = NULL;

    if (g_segment_head == NULL)
    {
        g_segment_head = table;
        return table;
    }

    table->next = g_segment_head;
    g_segment_head = table;
    return table;
}

static void insert_allocated_sorted(node *part)
{
    node **current = &g_allocated_head;

    while (*current != NULL && (*current)->address < part->address)
    {
        current = &((*current)->next);
    }

    part->next = *current;
    *current = part;
}

static void insert_free_sorted(node *part)
{
    node **current = &g_free_head;

    while (*current != NULL && (*current)->address < part->address)
    {
        current = &((*current)->next);
    }

    part->next = *current;
    *current = part;
}

static int total_free_size(void)
{
    int total = 0;
    node *current = g_free_head;

    while (current != NULL)
    {
        total += current->size;
        current = current->next;
    }

    return total;
}

static void merge_free_neighbors(void)
{
    node *current = g_free_head;

    while (current != NULL && current->next != NULL)
    {
        if (current->address + current->size == current->next->address)
        {
            node *next = current->next;
            current->size += next->size;
            current->next = next->next;
            free(next);
            continue;
        }

        current = current->next;
    }
}

static void remove_segment_table(const char *job_name)
{
    segmentNode **current = &g_segment_head;

    while (*current != NULL)
    {
        if (strcmp((*current)->job_name, job_name) == 0)
        {
            segmentNode *target = *current;
            *current = target->next;
            free(target);
            return;
        }

        current = &((*current)->next);
    }
}

static int segment_index_from_flag(const char *flag, const char *job_name)
{
    size_t prefix_len = strlen(job_name);

    if (strncmp(flag, job_name, prefix_len) != 0)
    {
        return -1;
    }

    return atoi(flag + (int)prefix_len);
}

static int allocate_single_segment(const char *job_name, int segment_no, int segment_size)
{
    node **current = &g_free_head;
    node *selected = NULL;
    node *allocated_part = NULL;
    segmentNode *table = find_segment_table(job_name);

    /* TODO:
     * 在空闲链表中查找第一个足够大的空闲区（最先适应）。
     */
    while (*current != NULL)
    {
        if ((*current)->size >= segment_size)
        {
            selected = *current;
            break;
        }
        current = &((*current)->next);
    }

    if (selected == NULL)
    {
        return 0;
    }

    if (table == NULL)
    {
        table = create_segment_table(job_name);
        if (table == NULL)
        {
            return 0;
        }
    }

    allocated_part = create_partition(segment_size, selected->address, "");
    if (allocated_part == NULL)
    {
        return 0;
    }

    snprintf(allocated_part->flag, FLAG_LEN, "%s%d", job_name, segment_no);
    insert_allocated_sorted(allocated_part);

    table->a[table->segment_count][0] = segment_no;
    table->a[table->segment_count][1] = segment_size;
    table->a[table->segment_count][2] = allocated_part->address;
    table->segment_count++;

    if (selected->size == segment_size)
    {
        *current = selected->next;
        free(selected);
    }
    else
    {
        selected->size -= segment_size;
        selected->address += segment_size;
    }

    reorder(NULL);
    return 1;
}

static void print_segment_table(const char *job_name)
{
    int index = 0;
    segmentNode *table = find_segment_table(job_name);

    if (table == NULL)
    {
        return;
    }

    printf("**************打印%s段表**************\n", job_name);
    printf("段号    段长    基址\n");

    for (index = 0; index < table->segment_count; ++index)
    {
        printf("%d%8d%8d\n", table->a[index][0], table->a[index][1], table->a[index][2]);
    }
}

void reorder(node *head)
{
    node *allocated = g_allocated_head;
    node *free_part = g_free_head;
    int id = 1;

    (void)head;

    while (allocated != NULL || free_part != NULL)
    {
        if (free_part == NULL || (allocated != NULL && allocated->address < free_part->address))
        {
            allocated->id = id++;
            allocated = allocated->next;
        }
        else
        {
            free_part->id = id++;
            free_part = free_part->next;
        }
    }
}

node *initMemory(void)
{
    node *head = (node *)calloc(1, sizeof(node));

    if (head == NULL)
    {
        return NULL;
    }

    printf("请输入主存大小(KB): ");
    g_memory.size = read_int();
    printf("请输入主存起始地址(KB): ");
    g_memory.address = read_int();

    g_free_head = create_partition(g_memory.size, g_memory.address, "空闲");
    if (g_free_head == NULL)
    {
        free(head);
        return NULL;
    }

    reorder(head);
    return head;
}

int operation(node *head)
{
    int choice = -1;

    (void)head;

    printf("***********可变分区管理***********\n");
    printf("*        1.内存分配            *\n");
    printf("*        2.内存去配            *\n");
    printf("*        0.退出                *\n");
    printf("请输入入选项[%d]\n", 0);
    choice = read_int();

    switch (choice)
    {
        case 1:
            printf("1.内存分配\n");
            allocate(head);
            return 0;
        case 2:
            printf("2.内存去配\n");
            recycle(head);
            return 0;
        case 0:
            printf("0.退出\n");
            return 1;
        default:
            printf("选项无效，请重新输入。\n");
            return 0;
    }
}

void allocate(node *head)
{
    char job_name[JOB_NAME_LEN] = {0};
    int job_size = 0;
    int free_size = total_free_size();

    print(head);
    printf("请输入作业名: ");
    scanf("%19s", job_name);
    printf("请输入%s需要分配的主存大小: ", job_name);
    job_size = read_int();

    if (job_size > free_size)
    {
        printf("剩余%dKB的内存，无法满足%s的分配请求。\n", free_size, job_name);
        return;
    }

    firstAllocation(head, job_size, job_name);
}

void firstAllocation(node *head, int size, char c[10])
{
    int remaining = size;
    int segment_count = 0;
    int segment_no = 0;

    /* TODO:
     * 按段进行最先适应分配，并维护段表。
     */
    printf("请输入作业要分成的段数: ");
    segment_count = read_int();

    if (segment_count <= 0 || segment_count > MAX_SEGMENTS)
    {
        printf("段数无效。\n");
        return;
    }

    for (segment_no = 0; segment_no < segment_count; ++segment_no)
    {
        int segment_size = 0;

        printf("剩余%dKB的内存，请输入第%d段的大小: ", remaining, segment_no + 1);
        segment_size = read_int();

        if (segment_size <= 0 || segment_size > remaining)
        {
            printf("输入的段大小无效。\n");
            return;
        }

        if (!allocate_single_segment(c, segment_no, segment_size))
        {
            printf("第%d段分配失败。\n", segment_no + 1);
            return;
        }

        remaining -= segment_size;
        print(head);
    }

    printf("分配成功!\n");
    print_segment_table(c);
}

void recycle(node *head)
{
    char job_name[JOB_NAME_LEN] = {0};
    segmentNode *table = NULL;
    node **current = NULL;

    /* TODO:
     * 根据作业名回收所有段，并处理前后相邻空闲区合并。
     */
    print(head);
    printf("请输入您想回收的作业名: ");
    scanf("%19s", job_name);

    table = find_segment_table(job_name);
    if (table == NULL)
    {
        printf("未找到作业%s。\n", job_name);
        return;
    }

    for (int i = 0; i < table->segment_count; ++i)
    {
        int segment_no = table->a[i][0];
        current = &g_allocated_head;

        while (*current != NULL)
        {
            if (segment_index_from_flag((*current)->flag, job_name) == segment_no)
            {
                node *reclaimed = *current;
                *current = reclaimed->next;
                strncpy(reclaimed->flag, "空闲", FLAG_LEN - 1);
                reclaimed->flag[FLAG_LEN - 1] = '\0';
                reclaimed->next = NULL;
                insert_free_sorted(reclaimed);
                merge_free_neighbors();
                reorder(head);
                printf("回收%s的段%s%d成功!\n", job_name, job_name, segment_no);
                break;
            }
            current = &((*current)->next);
        }
    }

    remove_segment_table(job_name);
    print(head);
}

void print(node *head)
{
    node *current = NULL;

    (void)head;

    reorder(head);
    printf("*******************主存分配情况*******************\n");
    printf("已分配:\n");
    printf("分配号    大小(KB)    起始(KB)    状态\n");
    current = g_allocated_head;
    while (current != NULL)
    {
        printf("%d%12d%12d%12s\n", current->id, current->size, current->address, current->flag);
        current = current->next;
    }

    printf("\n未分配:\n");
    printf("分配号    大小(KB)    起始(KB)    状态\n");
    current = g_free_head;
    while (current != NULL)
    {
        printf("%d%12d%12d%12s\n", current->id, current->size, current->address, current->flag);
        current = current->next;
    }
}

void destroy_all(node *head)
{
    node *next_part = NULL;
    segmentNode *next_segment = NULL;

    while (g_allocated_head != NULL)
    {
        next_part = g_allocated_head->next;
        free(g_allocated_head);
        g_allocated_head = next_part;
    }

    while (g_free_head != NULL)
    {
        next_part = g_free_head->next;
        free(g_free_head);
        g_free_head = next_part;
    }

    while (g_segment_head != NULL)
    {
        next_segment = g_segment_head->next;
        free(g_segment_head);
        g_segment_head = next_segment;
    }

    free(head);
}
