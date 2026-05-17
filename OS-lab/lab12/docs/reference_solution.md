# 段页式存储管理参考实现

下面保留的是本项目在“回退成教学脚手架之前”已经验证过的一份 C11 参考实现。  
建议你先自己完成 `src/` 里的 TODO，再回来看这里。

## 参考实现说明

- 采用顺序扫描空闲块的方式分配物理块，便于观察位示图变化。
- 保留了题面要求的 `Print / distribute / recycle / menu / init` 五个公共函数名。
- 输出风格尽量贴近截图，但没有伪造固定结果。

## 头文件

```c
#ifndef SEG_PAGED_MEM_H
#define SEG_PAGED_MEM_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_SEGMENTS 32
#define MAX_PAGES_PER_SEGMENT 128
#define MAX_JOBS 64
#define MAX_NAME_LEN 64

struct page_entry {
    int page_no;
    int block_no;
};

struct segment_entry {
    int segment_no;
    int page_count;
    struct page_entry pages[MAX_PAGES_PER_SEGMENT];
};

struct job_node {
    char name[MAX_NAME_LEN];
    int requested_size;
    int segment_count;
    int total_pages;
    struct segment_entry segments[MAX_SEGMENTS];
    struct job_node *next;
};

struct memory_system {
    int memory_size;
    int word_length;
    int block_length;
    int block_count;
    int word_count;
    int free_block_count;
    unsigned long long *bitmap_words;
    unsigned char *block_used;
    struct job_node *job_list_head;
};

extern struct memory_system g_memory;

void init(void);
void Print(void);
void distribute(char *name, int size);
void recycle(char *name);
void menu(void);

void mem_reset_system(void);
void mem_release_system(void);
int mem_configure(int memory_size, int word_length, int block_length);
bool mem_is_ready(void);
void mem_init_bitmap(void);
int mem_allocate_job(const char *name, int size, int segment_count, const int *page_counts,
                     char *message, size_t message_size);
int mem_recycle_job(const char *name, char *message, size_t message_size);
int mem_translate(const char *name, int segment_no, int page_no, int offset,
                  int *block_no, int *physical_address,
                  char *message, size_t message_size);
struct job_node *mem_find_job(const char *name);
int mem_block_is_used(int block_no);

#endif
```

## 核心存储管理代码

```c
#include "seg_paged_mem.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct memory_system g_memory = {0};

/*
思考:
- 位示图不仅要能打印，还要支持快速判定某块是否已占用。
- 回收时如果只知道作业名，就必须能从作业链表一路找到页表里的块号。

思路:
- 用 block_used[] 直接表示每个块当前是否占用，便于扫描。
- 用 bitmap_words[] 保留“位示图”这一课程语义，输出时仍可按字长排版。
*/
static void free_job_list(void) {
    struct job_node *node = g_memory.job_list_head;
    while (node != NULL) {
        struct job_node *next = node->next;
        free(node);
        node = next;
    }
    g_memory.job_list_head = NULL;
}

static void set_block_state(int block_no, int used) {
    int word_index;
    int bit_index;
    unsigned long long mask;

    if (block_no < 0 || block_no >= g_memory.block_count) {
        return;
    }

    word_index = block_no / g_memory.word_length;
    bit_index = block_no % g_memory.word_length;
    mask = 1ULL << bit_index;

    g_memory.block_used[block_no] = (unsigned char)(used ? 1 : 0);
    if (used) {
        g_memory.bitmap_words[word_index] |= mask;
    } else {
        g_memory.bitmap_words[word_index] &= ~mask;
    }
}

static int count_required_pages(int segment_count, const int *page_counts) {
    int i;
    int total = 0;

    for (i = 0; i < segment_count; ++i) {
        total += page_counts[i];
    }

    return total;
}

static int collect_free_blocks(int required_pages, int *blocks_out) {
    int block_no;
    int found = 0;

    for (block_no = 0; block_no < g_memory.block_count && found < required_pages; ++block_no) {
        if (!g_memory.block_used[block_no]) {
            blocks_out[found++] = block_no;
        }
    }

    return found == required_pages ? 0 : -1;
}

static void append_job(struct job_node *job) {
    struct job_node **tail = &g_memory.job_list_head;
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }
    *tail = job;
}

void mem_reset_system(void) {
    g_memory.memory_size = 0;
    g_memory.word_length = 0;
    g_memory.block_length = 0;
    g_memory.block_count = 0;
    g_memory.word_count = 0;
    g_memory.free_block_count = 0;
    g_memory.block_used = NULL;
    g_memory.job_list_head = NULL;
}

void mem_release_system(void) {
    free_job_list();
    free(g_memory.bitmap_words);
    free(g_memory.block_used);
    g_memory.bitmap_words = NULL;
    g_memory.block_used = NULL;
    mem_reset_system();
}

void mem_init_bitmap(void) {
    if (!mem_is_ready()) {
        return;
    }
    memset(g_memory.bitmap_words, 0, (size_t)g_memory.word_count * sizeof(unsigned long long));
    memset(g_memory.block_used, 0, (size_t)g_memory.block_count * sizeof(unsigned char));
    g_memory.free_block_count = g_memory.block_count;
    free_job_list();
}

int mem_configure(int memory_size, int word_length, int block_length) {
    mem_release_system();
    if (memory_size <= 0 || word_length <= 0 || block_length <= 0) {
        return -1;
    }

    g_memory.memory_size = memory_size;
    g_memory.word_length = word_length;
    g_memory.block_length = block_length;
    g_memory.block_count = memory_size / block_length;
    g_memory.word_count = (g_memory.block_count + word_length - 1) / word_length;
    g_memory.free_block_count = g_memory.block_count;
    g_memory.bitmap_words = calloc((size_t)g_memory.word_count, sizeof(unsigned long long));
    g_memory.block_used = calloc((size_t)g_memory.block_count, sizeof(unsigned char));
    if (g_memory.bitmap_words == NULL || g_memory.block_used == NULL) {
        mem_reset_system();
        return -1;
    }
    return 0;
}

bool mem_is_ready(void) {
    return g_memory.bitmap_words != NULL;
}

struct job_node *mem_find_job(const char *name) {
    struct job_node *node = g_memory.job_list_head;

    while (node != NULL) {
        if (strcmp(node->name, name) == 0) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

int mem_block_is_used(int block_no) {
    if (block_no < 0 || block_no >= g_memory.block_count || g_memory.block_used == NULL) {
        return 0;
    }
    return g_memory.block_used[block_no] ? 1 : 0;
}

/*
思考:
- 题目既给了作业大小，也让用户输入每段页数，两者可能出现不一致。
- 分配成功后必须同时维护作业链表、页表和位示图，不能只更新其中一处。

思路:
- 先把每段页数求和，得到总页数需求。
- 再扫描空闲块，拿到足够数量的块号后统一写入页表。
*/
int mem_allocate_job(const char *name, int size, int segment_count, const int *page_counts,
                     char *message, size_t message_size) {
    struct job_node *job;
    int required_pages;
    int current_page = 0;
    int segment_index;
    int page_index;
    int *allocated_blocks;

    if (!mem_is_ready()) {
        snprintf(message, message_size, "主存尚未初始化。");
        return -1;
    }
    if (name == NULL || name[0] == '\0') {
        snprintf(message, message_size, "作业名不能为空。");
        return -1;
    }
    if (segment_count <= 0 || segment_count > MAX_SEGMENTS) {
        snprintf(message, message_size, "段数不合法。");
        return -1;
    }
    if (mem_find_job(name) != NULL) {
        snprintf(message, message_size, "作业 %s 已存在，不能重复装入。", name);
        return -1;
    }

    required_pages = count_required_pages(segment_count, page_counts);
    if (required_pages <= 0) {
        snprintf(message, message_size, "页数总和必须大于 0。");
        return -1;
    }
    if (required_pages > g_memory.free_block_count) {
        snprintf(message, message_size, "主存空间不足，无法装载！");
        return -1;
    }
    if (required_pages * g_memory.block_length < size) {
        snprintf(message, message_size, "页表容量不足以容纳该作业大小。");
        return -1;
    }

    allocated_blocks = malloc((size_t)required_pages * sizeof(int));
    job = calloc(1U, sizeof(*job));
    if (allocated_blocks == NULL || job == NULL) {
        free(allocated_blocks);
        free(job);
        snprintf(message, message_size, "内存分配失败。");
        return -1;
    }
    if (collect_free_blocks(required_pages, allocated_blocks) != 0) {
        free(allocated_blocks);
        free(job);
        snprintf(message, message_size, "主存空间不足，无法装载！");
        return -1;
    }

    strncpy(job->name, name, MAX_NAME_LEN - 1);
    job->requested_size = size;
    job->segment_count = segment_count;
    job->total_pages = required_pages;
    job->next = NULL;

    for (segment_index = 0; segment_index < segment_count; ++segment_index) {
        job->segments[segment_index].segment_no = segment_index;
        job->segments[segment_index].page_count = page_counts[segment_index];
        for (page_index = 0; page_index < page_counts[segment_index]; ++page_index) {
            int block_no = allocated_blocks[current_page++];
            job->segments[segment_index].pages[page_index].page_no = page_index;
            job->segments[segment_index].pages[page_index].block_no = block_no;
            set_block_state(block_no, 1);
            g_memory.free_block_count--;
        }
    }

    append_job(job);
    free(allocated_blocks);
    snprintf(message, message_size, "作业 %s 分配成功。", name);
    return 0;
}

/*
思考:
- 回收不是简单删除链表节点，而是要先恢复位示图和空闲块数。
- 如果作业不存在，必须返回明确错误，不要静默失败。

思路:
- 用二级指针在单链表里删除节点。
- 在释放节点前，先遍历段表和页表，把对应块全部置回 0。
*/
int mem_recycle_job(const char *name, char *message, size_t message_size) {
    struct job_node **cursor = &g_memory.job_list_head;
    int segment_index;
    int page_index;

    while (*cursor != NULL) {
        if (strcmp((*cursor)->name, name) == 0) {
            struct job_node *victim = *cursor;
            *cursor = victim->next;

            for (segment_index = 0; segment_index < victim->segment_count; ++segment_index) {
                for (page_index = 0; page_index < victim->segments[segment_index].page_count; ++page_index) {
                    int block_no = victim->segments[segment_index].pages[page_index].block_no;
                    if (mem_block_is_used(block_no)) {
                        set_block_state(block_no, 0);
                        g_memory.free_block_count++;
                    }
                }
            }

            free(victim);
            snprintf(message, message_size, "作业 %s 回收成功。", name);
            return 0;
        }
        cursor = &(*cursor)->next;
    }

    snprintf(message, message_size, "未找到作业 %s。", name);
    return -1;
}

/*
思考:
- 地址转换最容易出错的是越界检查顺序。
- 物理地址计算只依赖“块号 * 块长 + 页内偏移”，前提是前面的索引都合法。

思路:
- 先找作业，再检查段号、页号、偏移。
- 全部通过后再取块号并计算物理地址。
*/
int mem_translate(const char *name, int segment_no, int page_no, int offset,
                  int *block_no, int *physical_address,
                  char *message, size_t message_size) {
    struct job_node *job = mem_find_job(name);

    if (job == NULL) {
        snprintf(message, message_size, "地址转换失败：未找到作业 %s。", name);
        return -1;
    }
    if (segment_no < 0 || segment_no >= job->segment_count) {
        snprintf(message, message_size, "地址转换失败：段号越界。");
        return -1;
    }
    if (page_no < 0 || page_no >= job->segments[segment_no].page_count) {
        snprintf(message, message_size, "地址转换失败：页号越界。");
        return -1;
    }
    if (offset < 0 || offset >= g_memory.block_length) {
        snprintf(message, message_size, "地址转换失败：页内偏移越界。");
        return -1;
    }

    *block_no = job->segments[segment_no].pages[page_no].block_no;
    *physical_address = (*block_no) * g_memory.block_length + offset;
    snprintf(message, message_size, "地址转换成功。");
    return 0;
}
```

## 输出层与交互层代码

```c
#include "seg_paged_io.h"
#include "seg_paged_mem.h"

#include <stdio.h>

void io_print_menu(void) {
    puts("**********************菜单**********************");
    puts("*              1. 内存分配                    *");
    puts("*              2. 内存回收                    *");
    puts("*              3. 地址转换                    *");
    puts("*              4. 查看当前内存状态            *");
    puts("*              0. 退出                        *");
    puts("**********************************************");
}

void io_print_bitmap(void) {
    int row;
    int col;
    int index;

    puts("主存位示图如下：");
    printf("共 %d 块(列宽为 %d)\n", g_memory.block_count, g_memory.word_length);
    printf("   ");
    for (col = 0; col < g_memory.word_length; ++col) {
        printf("%2d ", col);
    }
    putchar('\n');

    for (row = 0; row < g_memory.word_count; ++row) {
        printf("%2d ", row);
        for (col = 0; col < g_memory.word_length; ++col) {
            index = row * g_memory.word_length + col;
            if (index < g_memory.block_count) {
                printf("%2d ", mem_block_is_used(index));
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

    if (job == NULL) {
        return;
    }

    printf("作业名: %s\n", job->name);
    printf("作业大小: %d\n", job->requested_size);
    printf("段数: %d\n", job->segment_count);

    for (segment_index = 0; segment_index < job->segment_count; ++segment_index) {
        printf("段号:%d 页数:%d\n",
               job->segments[segment_index].segment_no,
               job->segments[segment_index].page_count);
        puts("页号  块号");
        for (page_index = 0; page_index < job->segments[segment_index].page_count; ++page_index) {
            printf("%3d %4d\n",
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
    printf("作业名:%s\n", job_name);
    printf("逻辑地址(段号=%d, 页号=%d, 页内偏移=%d)\n", segment_no, page_no, offset);
    printf("物理块号:%d\n", block_no);
    printf("物理地址:%d\n", physical_address);
}
```

```c
#include "seg_paged_io.h"
#include "seg_paged_mem.h"

#include <stdio.h>
#include <string.h>

static int current_segment_count = 0;
static int current_page_counts[MAX_SEGMENTS] = {0};

void init(void) {
    mem_init_bitmap();
}

void Print(void) {
    struct job_node *node;

    io_print_bitmap();
    node = g_memory.job_list_head;
    while (node != NULL) {
        io_print_job_detail(node);
        node = node->next;
    }
}

void distribute(char *name, int size) {
    char message[128];

    if (mem_allocate_job(name, size, current_segment_count, current_page_counts,
                         message, sizeof(message)) != 0) {
        io_print_message(message);
        return;
    }

    io_print_message(message);
    io_print_job_detail(mem_find_job(name));
}

void recycle(char *name) {
    char message[128];

    mem_recycle_job(name, message, sizeof(message));
    io_print_message(message);
    Print();
}

void menu(void) {
    io_print_menu();
}

int main(void) {
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
        menu();
        printf("请输入你的选择:");
        if (scanf("%d", &choose) != 1) {
            break;
        }

        if (choose == 1) {
            printf("请输入作业名:");
            if (scanf("%63s", name) != 1) {
                break;
            }
            printf("请输入%s所需主存大小:", name);
            if (scanf("%d", &size) != 1) {
                break;
            }
            printf("请输入段数:");
            if (scanf("%d", &current_segment_count) != 1) {
                break;
            }
            if (current_segment_count <= 0 || current_segment_count > MAX_SEGMENTS) {
                puts("段数不合法。");
                continue;
            }
            memset(current_page_counts, 0, sizeof(current_page_counts));
            for (segment_index = 0; segment_index < current_segment_count; ++segment_index) {
                printf("请输入第%d段页数:", segment_index);
                if (scanf("%d", &current_page_counts[segment_index]) != 1) {
                    return 1;
                }
            }
            distribute(name, size);
        } else if (choose == 2) {
            printf("请输入作业名:");
            if (scanf("%63s", name) != 1) {
                break;
            }
            recycle(name);
        } else if (choose == 3) {
            printf("请输入作业名:");
            if (scanf("%63s", name) != 1) {
                break;
            }
            printf("请输入段号:");
            if (scanf("%d", &segment_no) != 1) {
                break;
            }
            printf("请输入页号:");
            if (scanf("%d", &page_no) != 1) {
                break;
            }
            printf("请输入页内偏移:");
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
```
