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
