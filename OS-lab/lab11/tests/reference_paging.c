#include "paging_lab.h"

#include <stdio.h>

static char job_name[MAX_NAME_LEN];
static int frame_count_limit;
static int job_length;
static int page_seq[MAX_PAGES];
static int page_fault[MAX_PAGES];
static int frame_snapshot[MAX_FRAMES][MAX_PAGES];
static int fault_page[MAX_PAGES];
static int fault_total;
static int current_algorithm;

static void reset_run_state(void)
{
    int i;
    int j;

    fault_total = 0;
    for (i = 0; i < MAX_PAGES; ++i) {
        page_fault[i] = 0;
        fault_page[i] = -1;
    }

    for (i = 0; i < MAX_FRAMES; ++i) {
        for (j = 0; j < MAX_PAGES; ++j) {
            frame_snapshot[i][j] = -1;
        }
    }
}

static void copy_snapshot(const int frames[], int used_frames, int step)
{
    int i;

    for (i = 0; i < frame_count_limit; ++i) {
        if (i < used_frames) {
            frame_snapshot[i][step] = frames[i];
        } else {
            frame_snapshot[i][step] = -1;
        }
    }
}

static int find_page(const int frames[], int used_frames, int page_no)
{
    int i;

    for (i = 0; i < used_frames; ++i) {
        if (frames[i] == page_no) {
            return i;
        }
    }
    return -1;
}

void out(void)
{
    puts("***********请求分页式存储管理***********");
    puts("\t*\t1.FIFO分配\t*\t");
    puts("\t*\t2.LRU(LFU)分配\t*\t");
    puts("\t*\t0.退出\t*\t");
    printf("\t\t请输入选项：");
}

void input(void)
{
    int i;

    printf("请输入作业名：");
    scanf("%63s", job_name);
    printf("请输入作业页面长度：");
    scanf("%d", &job_length);
    printf("请输入作业页面顺序：\n");
    for (i = 0; i < job_length; ++i) {
        scanf("%d", &page_seq[i]);
    }
}

void print(void)
{
    int row;
    int col;
    const char *title = current_algorithm == 2 ? "LRU" : "FIFO";

    printf("************作业%s%s调度进入主存页的过程************\n", job_name, title);
    puts("调度过程：");

    for (col = 0; col < job_length; ++col) {
        printf("%3d", col);
    }
    putchar('\n');

    for (row = 0; row < frame_count_limit; ++row) {
        for (col = 0; col < job_length; ++col) {
            if (frame_snapshot[row][col] >= 0) {
                printf("%3d", frame_snapshot[row][col]);
            } else {
                printf("%3c", ' ');
            }
        }
        putchar('\n');
    }

    for (col = 0; col < job_length; ++col) {
        if (page_fault[col]) {
            printf("%3c", '+');
        } else {
            printf("%3c", ' ');
        }
    }
    putchar('\n');

    for (col = 0; col < job_length; ++col) {
        if (fault_page[col] >= 0) {
            printf("%3d", fault_page[col]);
        } else {
            printf("%3c", ' ');
        }
    }
    putchar('\n');

    printf("缺页率为：%.2f\n", (double) fault_total * 100.0 / (double) job_length);
}

void solve1(void)
{
    int frames[MAX_FRAMES];
    int used_frames = 0;
    int fifo_head = 0;
    int i;
    int hit_index;

    reset_run_state();
    current_algorithm = 1;

    for (i = 0; i < job_length; ++i) {
        hit_index = find_page(frames, used_frames, page_seq[i]);
        if (hit_index < 0) {
            page_fault[i] = 1;
            fault_page[i] = page_seq[i];
            ++fault_total;
            if (used_frames < frame_count_limit) {
                frames[used_frames++] = page_seq[i];
            } else {
                frames[fifo_head] = page_seq[i];
                fifo_head = (fifo_head + 1) % frame_count_limit;
            }
        }
        copy_snapshot(frames, used_frames, i);
    }
}

void solve2(void)
{
    int frames[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int used_frames = 0;
    int i;
    int j;
    int hit_index;
    int replace_index;

    reset_run_state();
    current_algorithm = 2;

    for (i = 0; i < job_length; ++i) {
        hit_index = find_page(frames, used_frames, page_seq[i]);
        if (hit_index >= 0) {
            last_used[hit_index] = i;
        } else {
            page_fault[i] = 1;
            fault_page[i] = page_seq[i];
            ++fault_total;
            if (used_frames < frame_count_limit) {
                frames[used_frames] = page_seq[i];
                last_used[used_frames] = i;
                ++used_frames;
            } else {
                replace_index = 0;
                for (j = 1; j < frame_count_limit; ++j) {
                    if (last_used[j] < last_used[replace_index]) {
                        replace_index = j;
                    }
                }
                frames[replace_index] = page_seq[i];
                last_used[replace_index] = i;
            }
        }
        copy_snapshot(frames, used_frames, i);
    }
}

int main(void)
{
    int choice;

    printf("请输入物理块的块数：");
    if (scanf("%d", &frame_count_limit) != 1) {
        return 0;
    }

    if (frame_count_limit <= 0 || frame_count_limit > MAX_FRAMES) {
        printf("物理块数必须在1到%d之间。\n", MAX_FRAMES);
        return 0;
    }

    out();
    if (scanf("%d", &choice) != 1) {
        return 0;
    }

    while (choice != 0) {
        input();
        if (choice == 1) {
            solve1();
            print();
        } else if (choice == 2) {
            solve2();
            print();
        } else {
            puts("选项无效，请重新输入。");
        }
        out();
        if (scanf("%d", &choice) != 1) {
            break;
        }
    }

    return 0;
}
