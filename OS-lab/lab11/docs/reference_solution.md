# 请求分页实验参考实现

这个文档保存的是已经验证过样例的 C11 参考实现。建议先完成 `src/main.c` 中的 `TODO`，再回来看这里。

## 命名说明

- 保留老师要求的函数名：`out`、`input`、`print`、`solve1`、`solve2`
- 将内部变量改成更清晰的 C 风格名字，例如 `frame_count_limit`、`page_seq`、`frame_snapshot`
- 菜单文字继续显示 `LRU(LFU)`，因为截图如此；但算法描述“最长时间没有被引用”对应的是 `LRU`

## 头文件

```c
#ifndef PAGING_LAB_H
#define PAGING_LAB_H

#define MAX_PAGES 1010
#define MAX_NAME_LEN 64
#define MAX_FRAMES 64

typedef struct {
    int cnt;
    int val;
} Y;

void out(void);
void input(void);
void print(void);
void solve1(void);
void solve2(void);

#endif
```

## 参考代码

```c
#include "paging_lab.h"

#include <stdio.h>
#include <string.h>

static char job_name[MAX_NAME_LEN];
static int frame_count_limit;
static int job_length;
static int page_seq[MAX_PAGES];
static int page_fault[MAX_PAGES];
static int frame_snapshot[MAX_FRAMES][MAX_PAGES];
static int fault_page[MAX_PAGES];
static int fault_total;
static int current_algorithm;

/*
 * 思考：
 * - 每次调度后都要保留“当前物理块状态”，否则 print 无法按列输出过程表。
 * - FIFO 与 LRU 的差异主要在“替换谁”，输入和输出框架可以共用。
 *
 * 思路：
 * - 用全局数组保存作业名、页面串、缺页标志、缺页页号和每一步快照。
 * - solve1/solve2 只负责填充这些结果；print 只负责展示。
 */
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

/*
 * 思考：
 * - 页面置换过程表是“列表示时间步、行表示物理块”。
 * - 因此每访问一个页面，都要把当前 frames[] 复制到 frame_snapshot[*][step]。
 *
 * 思路：
 * - used_frames 表示当前已经装入多少块。
 * - 未使用的物理块位置记为 -1，print 时输出为空格。
 */
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

/*
 * 思考：
 * - 命中判断是 FIFO 和 LRU 共用的基础操作。
 *
 * 思路：
 * - 线性扫描当前已使用的物理块。
 * - 找到则返回下标，找不到返回 -1。
 */
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

/*
 * 思考：
 * - 这个函数不做算法决策，只负责按截图风格输出。
 * - 标题里的 FIFO/LRU 由 solve1/solve2 预先写入 current_algorithm。
 *
 * 思路：
 * - 先输出时间列。
 * - 再逐行输出 frame_snapshot。
 * - 最后输出缺页标记和缺页页号，再计算缺页率。
 */
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

/*
 * 思考：
 * - FIFO 只关心“谁最早进入内存”。
 * - 因此可以用一个循环队首 fifo_head 表示下一次该淘汰的物理块位置。
 *
 * 思路：
 * - 命中时不换页，只复制快照。
 * - 缺页时先标记 page_fault/fault_page。
 * - 若未装满，直接放入下一空块；若已满，用 fifo_head 指向的位置替换。
 */
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

/*
 * 思考：
 * - 题面把第二个算法写成 LFU，但描述“最长时间没有被引用”实际上是 LRU。
 * - 实现时只需要为每个物理块维护最近一次被访问的时刻。
 *
 * 思路：
 * - 命中：更新该页的 last_used。
 * - 缺页且未装满：直接装入并记录 last_used。
 * - 缺页且已满：找 last_used 最小的物理块换出。
 */
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
```
