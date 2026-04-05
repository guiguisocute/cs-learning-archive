#include "seg_paged_mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct memory_system g_memory = {0};

static void free_job_list(void) {
    struct job_node *node = g_memory.job_list_head;
    while (node != NULL) {
        struct job_node *next = node->next;
        free(node);
        node = next;
    }
    g_memory.job_list_head = NULL;
}

void mem_reset_system(void) {
    g_memory.memory_size = 0;
    g_memory.word_length = 0;
    g_memory.block_length = 0;
    g_memory.block_count = 0;
    g_memory.word_count = 0;
    g_memory.free_block_count = 0;
    g_memory.bitmap_words = NULL;
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

void mem_init_bitmap(void) {
    /* TODO: 按题目要求初始化位示图。
     * 建议先做全 0 初始化，确认空闲块统计与打印正确后，再尝试随机初始化。 */
    if (!mem_is_ready()) {
        return;
    }
    memset(g_memory.bitmap_words, 0, (size_t)g_memory.word_count * sizeof(unsigned long long));
    memset(g_memory.block_used, 0, (size_t)g_memory.block_count * sizeof(unsigned char));
    g_memory.free_block_count = g_memory.block_count;
    free_job_list();
}

struct job_node *mem_find_job(const char *name) {
    struct job_node *node = g_memory.job_list_head;

    /* TODO: 遍历作业链表，按作业名匹配并返回目标结点。 */
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

int mem_allocate_job(const char *name, int size, int segment_count, const int *page_counts,
                     char *message, size_t message_size) {
    struct job_node *job;
    int required_pages;
    int current_page = 0;
    int segment_index;
    int page_index;
    int *allocated_blocks;

    /* TODO:
     * 1. 统计每段页数之和，得到总页数需求
     * 2. 检查空闲块数和作业名冲突
     * 3. 扫描位示图找空闲块
     * 4. 创建作业结点，填写段表和页表
     * 5. 更新位示图与剩余空闲块数
     */
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

int mem_recycle_job(const char *name, char *message, size_t message_size) {
    struct job_node **cursor = &g_memory.job_list_head;
    int segment_index;
    int page_index;

    /* TODO:
     * 1. 在作业链表中找到目标作业
     * 2. 遍历页表，把占用块重新置 0
     * 3. 更新空闲块数
     * 4. 删除作业结点
     */
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

int mem_translate(const char *name, int segment_no, int page_no, int offset,
                  int *block_no, int *physical_address,
                  char *message, size_t message_size) {
    struct job_node *job = mem_find_job(name);

    /* TODO:
     * 1. 查找作业
     * 2. 依次检查段号、页号、页内偏移是否合法
     * 3. 根据页表项得到块号
     * 4. 计算物理地址
     */
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
