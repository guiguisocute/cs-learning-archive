#include "paging_lab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sc[MAX][MAX] = {{0}};
int MemorySize = 0;
int WordLength = 0;
int WordNum = 0;
int BlockSize = 0;
int BlockNum = 0;
int UsingBolckNum = 0;
int AvailableBlockNum = 0;

static node *head = NULL;

static int bytes_per_block(void)
{
    return WordLength * BlockSize;
}

static int calc_job_pages(int job_size)
{
    int page_bytes = bytes_per_block();

    if (page_bytes <= 0) {
        return 0;
    }

    return (job_size + page_bytes - 1) / page_bytes;
}

static int find_free_block(void)
{
    int block_index;

    for (block_index = 0; block_index < BlockNum; ++block_index) {
        if (sc[block_index][0] == 0) {
            return block_index;
        }
    }

    return -1;
}

static node *find_job(const char *job_name)
{
    node *current = head;

    while (current != NULL) {
        if (strcmp(current->name, job_name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

static void reset_job_page_table(node *job)
{
    int row;
    int col;

    for (row = 0; row < MAX; ++row) {
        for (col = 0; col < MAX; ++col) {
            job->size[row][col] = -1;
        }
    }
}

static void mark_block_usage(int block_index, int byte_count)
{
    int cell_index;

    for (cell_index = 0; cell_index < bytes_per_block(); ++cell_index) {
        sc[block_index][cell_index] = cell_index < byte_count ? 1 : 0;
    }
}

static void release_block_usage(int block_index)
{
    int cell_index;

    for (cell_index = 0; cell_index < bytes_per_block(); ++cell_index) {
        sc[block_index][cell_index] = 0;
    }
}

static void print_memory_bitmap(void)
{
    int block_index;
    int cell_index;

    printf("系统内存位示图如下：\n");
    printf("    ");
    for (cell_index = 0; cell_index < bytes_per_block(); ++cell_index) {
        printf("%2d ", cell_index);
    }
    printf("\n");

    for (block_index = 0; block_index < BlockNum; ++block_index) {
        printf("%2d: ", block_index);
        for (cell_index = 0; cell_index < bytes_per_block(); ++cell_index) {
            printf("%2d ", sc[block_index][cell_index]);
        }
        printf("\n");
    }
}

static void print_free_block_list(void)
{
    int block_index;

    printf("剩余空闲块号如下：\n");
    printf("**********************\n");
    for (block_index = 0; block_index < BlockNum; ++block_index) {
        if (sc[block_index][0] == 0) {
            printf("%2d\n", block_index);
        }
    }
    printf("**********************\n");
}

static void print_memory_summary(void)
{
    printf("系统内存空间为%4d\n", MemorySize);
    printf("字长为%12d\n", WordLength);
    printf("一个物理块大小为%2d\n", bytes_per_block());
    printf("总块数为%12d\n", BlockNum);
    printf("已使用块数为%8d\n", UsingBolckNum);
    printf("剩余块数为%10d\n", AvailableBlockNum);
}

static void print_job_table(const node *job)
{
    int page_index;

    printf("作业%s的页表如下：\n", job->name);
    printf("***************************************\n");
    printf("页号\t物理块号\t装入标志\t页大小\n");
    for (page_index = 0; page_index < job->page_count; ++page_index) {
        printf("%2d\t%8d\t%8d\t%6d\n",
               job->size[page_index][0],
               job->size[page_index][1],
               job->size[page_index][2],
               job->size[page_index][3]);
    }
    printf("***************************************\n");
}

static void print_menu(void)
{
    printf("\n");
    printf("****************分页存储管理****************\n");
    printf("*             1.分配作业内存             *\n");
    printf("*             2.回收作业内存             *\n");
    printf("*             0.退出系统                 *\n");
    printf("********************************************\n");
}

static void reset_system_memory(void)
{
    int row;
    int col;

    for (row = 0; row < MAX; ++row) {
        for (col = 0; col < MAX; ++col) {
            sc[row][col] = 0;
        }
    }
}

int OperationChoice(void)
{
    int choice;

    /* TODO:
     * 1. 如截图所示打印菜单。
     * 2. 读取并返回用户操作编号。
     * 3. 非法输入时给出重试提示。
     */
    print_menu();
    printf("请输入操作编号：");
    if (scanf("%d", &choice) != 1) {
        return 0;
    }
    return choice;
}

void print(void)
{
    int block_index;

    /* TODO:
     * 1. 打印系统内存摘要信息。
     * 2. 打印位示图/块使用情况，输出风格尽量贴近实验截图。
     * 3. 打印当前剩余空闲块号列表。
     */
    (void)block_index;
    print_memory_summary();
    print_memory_bitmap();
    print_free_block_list();
}

node *allocate(node *list_head)
{
    char job_name[JOB_NAME_LEN];
    int job_size;
    int required_pages;
    int page_index;
    int remaining_size;
    node *job;

    /* TODO:
     * 1. 创建新的作业节点，并检查作业名是否重复。
     * 2. 按页计算该作业需要多少物理块。
     * 3. 在系统空闲块足够时更新页表、位示图和统计量。
     * 4. 将新作业插入链表，并打印该作业页表与系统内存信息。
     */
    (void)list_head;

    job = (node *)calloc(1, sizeof(node));
    if (job == NULL) {
        fprintf(stderr, "内存申请失败。\n");
        return head;
    }

    printf("请输入作业名：");
    if (scanf("%9s", job_name) != 1) {
        free(job);
        return head;
    }
    strncpy(job->name, job_name, JOB_NAME_LEN - 1);
    job->name[JOB_NAME_LEN - 1] = '\0';

    if (find_job(job->name) != NULL) {
        printf("作业%s已经存在，不能重复分配。\n", job->name);
        free(job);
        return head;
    }

    printf("请输入作业大小：");
    if (scanf("%d", &job_size) != 1) {
        free(job);
        return head;
    }

    required_pages = calc_job_pages(job_size);
    if (job_size <= 0 || required_pages <= 0) {
        printf("作业大小不合法。\n");
        free(job);
        return head;
    }

    if (required_pages > AvailableBlockNum) {
        printf("剩余空闲块不足，无法为作业%s分配内存。\n", job->name);
        free(job);
        return head;
    }

    reset_job_page_table(job);
    job->job_size = job_size;
    job->page_count = required_pages;

    remaining_size = job_size;
    for (page_index = 0; page_index < required_pages; ++page_index) {
        int block_index = find_free_block();
        int current_page_bytes;

        if (block_index < 0) {
            printf("系统空闲块搜索失败。\n");
            free(job);
            return head;
        }

        current_page_bytes = remaining_size > bytes_per_block()
            ? bytes_per_block()
            : remaining_size;

        job->size[page_index][0] = page_index;
        job->size[page_index][1] = block_index;
        job->size[page_index][2] = 1;
        job->size[page_index][3] = current_page_bytes;

        mark_block_usage(block_index, current_page_bytes);
        remaining_size -= current_page_bytes;
    }

    UsingBolckNum += required_pages;
    AvailableBlockNum = BlockNum - UsingBolckNum;

    job->next = head;
    head = job;

    printf("已成功为作业%s分配%d个物理块。\n", job->name, required_pages);
    print_job_table(job);
    print();

    return head;
}

node *recycle(node *list_head)
{
    char job_name[JOB_NAME_LEN];
    node *current;
    node *previous;
    int page_index;

    /* TODO:
     * 1. 在作业链表中查找待回收作业。
     * 2. 根据页表释放对应物理块。
     * 3. 更新已使用块数/剩余块数，并从链表删除该节点。
     * 4. 重新打印系统内存信息。
     */
    (void)list_head;

    printf("请输入要回收的作业名：");
    if (scanf("%9s", job_name) != 1) {
        return head;
    }

    current = head;
    previous = NULL;
    while (current != NULL && strcmp(current->name, job_name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("未找到作业%s，无法回收。\n", job_name);
        return head;
    }

    for (page_index = 0; page_index < current->page_count; ++page_index) {
        release_block_usage(current->size[page_index][1]);
    }

    UsingBolckNum -= current->page_count;
    AvailableBlockNum = BlockNum - UsingBolckNum;

    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    printf("已成功回收作业%s占用的内存。\n", job_name);
    free(current);
    print();

    return head;
}

void initMemory(void)
{
    /* TODO:
     * 1. 输入内存大小、字长、每块包含的字数。
     * 2. 推导总字数、块大小、总块数等实验参数。
     * 3. 初始化系统内存位示图和统计量。
     */
    printf("请输入内存大小：");
    if (scanf("%d", &MemorySize) != 1) {
        return;
    }
    printf("请输入字长：");
    if (scanf("%d", &WordLength) != 1) {
        return;
    }
    printf("请输入一个物理块包含的字数：");
    if (scanf("%d", &BlockSize) != 1) {
        return;
    }

    WordNum = WordLength == 0 ? 0 : MemorySize / WordLength;
    BlockNum = bytes_per_block() == 0 ? 0 : MemorySize / bytes_per_block();
    UsingBolckNum = 0;
    AvailableBlockNum = BlockNum;
    reset_system_memory();

    print();
}

void Apply(void)
{
    int choice;

    /* TODO:
     * 1. 初始化系统内存。
     * 2. 按菜单循环处理分配/回收请求。
     * 3. 结合截图完善退出前后的交互细节。
     */
    initMemory();
    while (1) {
        choice = OperationChoice();
        switch (choice) {
        case 1:
            head = allocate(head);
            break;
        case 2:
            head = recycle(head);
            break;
        case 0:
            return;
        default:
            printf("输入的操作编号无效，请重新输入。\n");
            break;
        }
    }
}

int main(void)
{
    Apply();
    return 0;
}
