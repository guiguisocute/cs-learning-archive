#include "seg_paged_io.h"
#include "seg_paged_mem.h"

#include <stdio.h>

void io_print_menu(void) {
    puts("**********可变分区管理**********");
    puts("* 1. 内存分配    *");
    puts("* 2. 内存去配    *");
    puts("* 3. 地址转换    *");
    puts("* 4. 查看内存    *");
    puts("* 0. 退出        *");
    printf("**********请输入选项: ");
}

void io_print_unavailable(const char *feature_name) {
    printf("%s 尚未实现。\n", feature_name);
}

void io_print_bitmap(void) {
    int row;
    int col;
    int index;

    /* TODO: 按题目截图风格输出主存位示图。 */
    puts("主存位示图如下所示:");
    printf("  ");
    for (col = 0; col < g_memory.word_length; ++col) {
        printf("%3d", col);
    }
    putchar('\n');

    for (row = 0; row < g_memory.word_count; ++row) {
        printf("%-2d", row);
        for (col = 0; col < g_memory.word_length; ++col) {
            index = row * g_memory.word_length + col;
            if (index < g_memory.block_count) {
                printf("%3d", mem_block_is_used(index));
            } else {
                printf("   ");
            }
        }
        putchar('\n');
    }
    printf("剩余空闲块数:%d\n", g_memory.free_block_count);
}

void io_print_job_detail(const struct job_node *job) {
    int segment_index;
    int page_index;

    /* TODO: 输出作业分配后的段表和页表。 */
    if (job == NULL) {
        return;
    }

    printf("作业%s的分配情况如下:\n", job->name);

    for (segment_index = 0; segment_index < job->segment_count; ++segment_index) {
        printf("      第%d段:\n", job->segments[segment_index].segment_no);
        puts("            页号    块号");
        for (page_index = 0; page_index < job->segments[segment_index].page_count; ++page_index) {
            printf("            %-8d%d\n",
                   job->segments[segment_index].pages[page_index].page_no,
                   job->segments[segment_index].pages[page_index].block_no);
        }
    }
}

void io_print_message(const char *message) {
    puts(message);
}

void io_print_translation_result(const char *job_name, int segment_no, int page_no,
                                 int offset, int block_no, int physical_address) {
    /* TODO: 把这里替换成你自己的地址转换结果展示格式。 */
    printf("作业名:%s\n", job_name);
    printf("逻辑地址(段号=%d, 页号=%d, 页内偏移=%d)\n", segment_no, page_no, offset);
    printf("物理块号:%d\n", block_no);
    printf("物理地址:%d\n", physical_address);
}
