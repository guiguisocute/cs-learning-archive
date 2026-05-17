#include "paging_lab.h"

#include <stdio.h>
#include <string.h>

static char job_name[MAX_NAME_LEN];
static int frame_count_limit;
static int job_length;
static int page_seq[MAX_PAGES];
static int frame_snapshot[MAX_FRAMES][MAX_PAGES];
static int page_fault[MAX_PAGES];
static int fault_page[MAX_PAGES];
static int fault_total;
static int current_algorithm;
static int has_schedule_result;

static void reset_run_state(void)
{
    int i;
    int j;

    fault_total = 0;
    has_schedule_result = 0;
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
    puts("**********请求分页式存储管理**********");
    puts("* 1. FIFO分配        *");
    puts("* 2. LRU(LFU)分配    *");
    puts("* 0. 退出            *");
    printf("**********请输入选项: ");
}

void input(void)
{
    int i;

    printf("请输入作业名: ");
    scanf("%63s", job_name);
    printf("请输入作业页面长度: ");
    scanf("%d", &job_length);
    printf("请输入作业页面顺序: \n");
    for (i = 0; i < job_length; ++i) {
        scanf("%d", &page_seq[i]);
    }
}

void print(void)
{
    int row;
    int col;
    const char *title = current_algorithm == 2 ? "LRU" : "FIFO";

    /* TODO:
     * 1. 打印进程表表头（时间步编号）。
     * 2. 打印各物理块在每一步的页面内容。
     * 3. 打印缺页标记行（+）。
     * 4. 打印缺页页号行。
     * 5. 打印缺页率。
     */
    printf("**********打印作业%s调度进入主存页的过程**********\n", title);
    printf("作业名: %s\n", job_name);
    if (!has_schedule_result) {
        puts("作业调度过程: ");
        puts("TODO: 请先在 solve1/solve2 中完成页面置换核心逻辑。");
        return;
    }

    puts("作业调度过程: ");

    printf("  ");
    for (col = 0; col < job_length; ++col) {
        printf("%3d", col);
    }
    putchar('\n');

    printf("  ");
    for (col = 0; col < job_length; ++col) {
        printf("%3d", page_seq[col]);
    }
    putchar('\n');

    for (row = 0; row < frame_count_limit; ++row) {
        printf("%-2d", row);
        for (col = 0; col < job_length; ++col) {
            if (frame_snapshot[row][col] >= 0) {
                printf("%3d", frame_snapshot[row][col]);
            } else {
                printf("%3c", ' ');
            }
        }
        putchar('\n');
    }

    printf("  ");
    for (col = 0; col < job_length; ++col) {
        if (page_fault[col]) {
            printf("%3c", '+');
        } else {
            printf("%3c", ' ');
        }
    }
    putchar('\n');

    printf("  ");
    for (col = 0; col < job_length; ++col) {
        if (fault_page[col] >= 0) {
            printf("%3d", fault_page[col]);
        } else {
            printf("%3c", ' ');
        }
    }
    putchar('\n');

    printf("缺页中断率为: %.2f\n", (double)fault_total * 100.0 / (double)job_length);
}

void solve1(void)
{
    int disp[MAX_FRAMES];
    int used_frames = 0;
    int i;
    int k;
    int hit_index;
    int shift_from;

    /* 对角移位显示：disp[0] 为最近装入的页，缺页时整列下移，
     * 最底端被挤出的页即 FIFO 淘汰页。命中不改变顺序（FIFO）。 */
    reset_run_state();
    current_algorithm = 1;

    for (i = 0; i < job_length; ++i) {
        hit_index = find_page(disp, used_frames, page_seq[i]);
        if (hit_index < 0) {
            page_fault[i] = 1;
            ++fault_total;
            if (used_frames == frame_count_limit) {
                fault_page[i] = disp[frame_count_limit - 1];
            }
            shift_from = used_frames < frame_count_limit
                             ? used_frames
                             : frame_count_limit - 1;
            for (k = shift_from; k > 0; --k) {
                disp[k] = disp[k - 1];
            }
            disp[0] = page_seq[i];
            if (used_frames < frame_count_limit) {
                ++used_frames;
            }
        }
        copy_snapshot(disp, used_frames, i);
    }

    has_schedule_result = 1;
}

void solve2(void)
{
    int disp[MAX_FRAMES];
    int used_frames = 0;
    int i;
    int k;
    int hit_index;
    int shift_from;

    /* 对角移位显示：disp[0] 为最近被引用的页。命中时把该页移到列首，
     * 缺页时整列下移，底端被挤出的页即 LRU 淘汰页。 */
    reset_run_state();
    current_algorithm = 2;

    for (i = 0; i < job_length; ++i) {
        hit_index = find_page(disp, used_frames, page_seq[i]);
        if (hit_index >= 0) {
            for (k = hit_index; k > 0; --k) {
                disp[k] = disp[k - 1];
            }
            disp[0] = page_seq[i];
        } else {
            page_fault[i] = 1;
            ++fault_total;
            if (used_frames == frame_count_limit) {
                fault_page[i] = disp[frame_count_limit - 1];
            }
            shift_from = used_frames < frame_count_limit
                             ? used_frames
                             : frame_count_limit - 1;
            for (k = shift_from; k > 0; --k) {
                disp[k] = disp[k - 1];
            }
            disp[0] = page_seq[i];
            if (used_frames < frame_count_limit) {
                ++used_frames;
            }
        }
        copy_snapshot(disp, used_frames, i);
    }

    has_schedule_result = 1;
}

int main(void)
{
    int choice;

    printf("请输入物理块的块数: ");
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
