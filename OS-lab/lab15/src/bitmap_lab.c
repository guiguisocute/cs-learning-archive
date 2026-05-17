#include "bitmap_lab.h"

linklist *work = NULL;

int disksize;
int word;
int blocksize;
int head;
int sector;
int cylinder;
int sum;
int available;
int map[MAX_BITMAP_ROWS][MAX_BITMAP_COLS];
int line;

static void clear_bitmap(void)
{
    int row;

    for (row = 0; row < line; ++row) {
        memset(map[row], 0, sizeof(map[row]));
    }
}

static void fill_block_record(linklist *node, int index, int block_no)
{
    int cylinder_offset;

    node->a[index] = block_no;
    node->zihao[index] = block_no / word;
    node->weihao[index] = block_no % word;

    cylinder_offset = block_no % cylinder;
    node->zhu[index] = block_no / cylinder;
    node->citou[index] = cylinder_offset / sector;
    node->shanqu[index] = cylinder_offset % sector;
}

static linklist *find_job(const char *job_name, linklist **prev_out)
{
    linklist *current = work;
    linklist *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, job_name) == 0) {
            if (prev_out != NULL) {
                *prev_out = prev;
            }
            return current;
        }
        prev = current;
        current = current->next;
    }

    if (prev_out != NULL) {
        *prev_out = NULL;
    }
    return NULL;
}

void print(void)
{
    int row;
    int col;

    printf("******************************辅存使用情况******************************\n");
    printf("    ");
    for (col = 0; col < word; ++col) {
        printf("%3d", col);
    }
    printf("\n");

    for (row = 0; row < line; ++row) {
        printf("%-4d", row);
        for (col = 0; col < word && row * word + col < sum; ++col) {
            printf("%3d", map[row][col]);
        }
        printf("\n");
    }
    printf("辅存剩余空闲块数: %d\n", available);
}

void allocate(void)
{
    char job_name[10];
    int need_size;
    linklist *node;
    int found;
    int row;
    int col;
    int block_no;
    int i;
    linklist *tail;

    printf("请输入申请空间的作业名字和需要分配辅存空间的大小(单位: K): ");
    if (scanf("%9s %d", job_name, &need_size) != 2) {
        printf("输入格式错误，无法继续分配。\n");
        return;
    }

    if (need_size <= 0) {
        printf("作业空间大小必须大于 0。\n");
        return;
    }

    if (need_size > available) {
        printf("剩余空闲块不足，分配不成功。\n");
        return;
    }

    if (find_job(job_name, NULL) != NULL) {
        printf("存在同名作业，请先回收或更换作业名。\n");
        return;
    }

    if (need_size > MAX_JOB_BLOCKS) {
        printf("申请块数超过单作业最大限制，分配不成功。\n");
        return;
    }

    node = (linklist *)malloc(sizeof(linklist));
    if (node == NULL) {
        printf("内存分配失败。\n");
        return;
    }
    memset(node, 0, sizeof(linklist));
    strncpy(node->name, job_name, sizeof(node->name) - 1);
    node->size = need_size;
    node->next = NULL;

    found = 0;
    block_no = 0;
    for (row = 0; row < line && found < need_size; ++row) {
        for (col = 0; col < word && block_no < sum && found < need_size; ++col) {
            if (map[row][col] == 0) {
                fill_block_record(node, found, block_no);
                map[row][col] = 1;
                ++found;
            }
            ++block_no;
        }
    }

    available -= need_size;

    if (work == NULL) {
        work = node;
    } else {
        tail = work;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }

    printf("辅存申请成功!\n");
    print();

    printf("*******************%s被分配的辅存*******************\n", job_name);
    printf("    序号  块号  字  位  柱面号  磁头号  扇区号\n");
    for (i = 0; i < need_size; ++i) {
        printf("    %-5d %-5d %-3d %-4d %-6d %-7d %d\n",
               i + 1,
               node->a[i], node->zihao[i], node->weihao[i],
               node->zhu[i], node->citou[i], node->shanqu[i]);
    }
}

void recycle(void)
{
    char job_name[10];
    linklist *prev;
    linklist *current;
    int freed_size;
    int i;

    /* 显示当前已分配的作业链表 */
    printf("当前分配的作业：");
    if (work == NULL) {
        printf("（无）\n");
    } else {
        current = work;
        while (current != NULL) {
            printf("%s", current->name);
            if (current->next != NULL) {
                printf("->");
            }
            current = current->next;
        }
        printf("\n");
    }

    printf("请输入要回收的作业名字: ");
    if (scanf("%9s", job_name) != 1) {
        printf("输入格式错误，无法继续回收。\n");
        return;
    }

    current = find_job(job_name, &prev);

    if (current == NULL) {
        printf("未找到作业 %s ，回收失败。\n", job_name);
        return;
    }

    for (i = 0; i < current->size; ++i) {
        map[current->zihao[i]][current->weihao[i]] = 0;
    }
    available += current->size;
    freed_size = current->size;

    if (prev == NULL) {
        work = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);

    printf("回收成功！\n");
    (void)freed_size;
    print();
}

void init(void)
{
    int row;
    int col;
    int block_no = 0;
    const char *mode;

    clear_bitmap();
    available = sum;
    mode = getenv("BITMAP_LAB_INIT_MODE");

    if (mode != NULL && strcmp(mode, "empty") == 0) {
        for (row = 0; row < line; ++row) {
            for (col = 0; col < word && block_no < sum; ++col) {
                map[row][col] = 0;
                ++block_no;
            }
        }
    } else if (mode != NULL && strcmp(mode, "random") == 0) {
        srand((unsigned int)time(NULL));
        for (row = 0; row < line; ++row) {
            for (col = 0; col < word && block_no < sum; ++col) {
                if (rand() % 5 == 0) {
                    map[row][col] = 1;
                    --available;
                }
                ++block_no;
            }
        }
    } else {
        for (row = 0; row < line; ++row) {
            for (col = 0; col < word && block_no < sum; ++col) {
                if (block_no % 3 == 0) {
                    map[row][col] = 1;
                    --available;
                }
                ++block_no;
            }
        }
    }

    print();
}

int menu(void)
{
    int choice;

    printf("**********辅存调度管理**********\n");
    printf("* 1. 空间分配        *\n");
    printf("* 2. 空间去配        *\n");
    printf("* 0. 退出            *\n");
    printf("**********请输入选项");

    if (scanf("%d", &choice) != 1) {
        printf("输入格式错误，程序结束。\n");
        return 0;
    }

    switch (choice) {
    case 1:
        allocate();
        break;
    case 2:
        recycle();
        break;
    case 0:
        break;
    default:
        printf("无效选项，请重新输入。\n");
        break;
    }

    return choice;
}
