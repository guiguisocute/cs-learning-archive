#include "seg_paged_io.h"
#include "seg_paged_mem.h"

#include <stdio.h>
#include <string.h>

static int current_segment_count = 0;
static int current_page_counts[MAX_SEGMENTS] = {0};

void init(void) {
    /* TODO: 在这里调用位示图初始化逻辑。 */
    mem_init_bitmap();
}

void Print(void) {
    struct job_node *node;

    /* TODO: 在这里整合位示图和作业分配情况的输出。 */
    io_print_bitmap();
    node = g_memory.job_list_head;
    while (node != NULL) {
        io_print_job_detail(node);
        node = node->next;
    }
}

void distribute(char *name, int size) {
    char message[128];

    /* TODO:
     * 读取段数和每段页数后，调用 mem_allocate_job。
     * 成功时打印段表和页表，失败时打印错误提示。
     */
    if (mem_allocate_job(name, size, current_segment_count, current_page_counts,
                         message, sizeof(message)) != 0) {
        io_print_message(message);
        return;
    }

    io_print_bitmap();
    io_print_job_detail(mem_find_job(name));
}

void recycle(char *name) {
    char message[128];

    /* TODO: 调用 mem_recycle_job，并在回收后刷新显示。 */
    mem_recycle_job(name, message, sizeof(message));
    io_print_message(message);
    io_print_bitmap();
}

void menu(void) {
    io_print_menu();
}

int main(void) {
    /* TODO:
     * 1. 读取主存大小、字长和块长
     * 2. 调用 mem_configure 和 init
     * 3. 菜单循环处理分配、回收、地址转换和查看状态
     */
    int choose;
    int size;
    int segment_index;
    int segment_no;
    int page_no;
    int offset;
    int block_no;
    int physical_address;
    char name[MAX_NAME_LEN];
    char message[128];

    printf("请输入内存大小为：");
    if (scanf("%d", &g_memory.memory_size) != 1) {
        return 1;
    }
    printf("请输入系统字长大小(32/64)为：");
    if (scanf("%d", &g_memory.word_length) != 1) {
        return 1;
    }
    printf("请输入块长:");
    if (scanf("%d", &g_memory.block_length) != 1) {
        return 1;
    }

    if (mem_configure(g_memory.memory_size, g_memory.word_length, g_memory.block_length) != 0) {
        puts("主存参数初始化失败。");
        return 1;
    }

    init();
    Print();

    while (1) {
        int segment_size;
        int remaining_size;

        menu();
        if (scanf("%d", &choose) != 1) {
            break;
        }

        if (choose == 1) {
            printf("请输入作业名: ");
            if (scanf("%63s", name) != 1) {
                break;
            }
            printf("请输入%s所需主存大小: ", name);
            if (scanf("%d", &size) != 1) {
                break;
            }
            printf("请输入要将作业分成几段: ");
            if (scanf("%d", &current_segment_count) != 1) {
                break;
            }
            if (current_segment_count <= 0 || current_segment_count > MAX_SEGMENTS) {
                puts("段数不合法。");
                continue;
            }
            memset(current_page_counts, 0, sizeof(current_page_counts));
            remaining_size = size;
            for (segment_index = 0; segment_index < current_segment_count; ++segment_index) {
                printf("剩余%d的内存未分配, 请输入第%d段的大小: ", remaining_size, segment_index);
                if (scanf("%d", &segment_size) != 1) {
                    return 1;
                }
                remaining_size -= segment_size;
                current_page_counts[segment_index] =
                    g_memory.block_length > 0 ? segment_size / g_memory.block_length : segment_size;
                puts("内存分配成功!");
            }
            distribute(name, size);
        } else if (choose == 2) {
            printf("请输入作业名: ");
            if (scanf("%63s", name) != 1) {
                break;
            }
            recycle(name);
        } else if (choose == 3) {
            printf("请输入作业名: ");
            if (scanf("%63s", name) != 1) {
                break;
            }
            printf("请输入段号: ");
            if (scanf("%d", &segment_no) != 1) {
                break;
            }
            printf("请输入页号: ");
            if (scanf("%d", &page_no) != 1) {
                break;
            }
            printf("请输入页内偏移: ");
            if (scanf("%d", &offset) != 1) {
                break;
            }
            if (mem_translate(name, segment_no, page_no, offset, &block_no, &physical_address,
                              message, sizeof(message)) != 0) {
                io_print_message(message);
                continue;
            }
            io_print_message(message);
            io_print_translation_result(name, segment_no, page_no, offset, block_no, physical_address);
        } else if (choose == 4) {
            Print();
        } else if (choose == 0) {
            break;
        } else {
            puts("输入有误!");
        }
    }

    mem_release_system();
    return 0;
}
