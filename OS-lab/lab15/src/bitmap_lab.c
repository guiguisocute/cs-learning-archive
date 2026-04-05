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

static int find_job_index(const char *job_name)
{
    linklist *current = work;
    int index = 1;

    while (current != NULL) {
        if (strcmp(current->name, job_name) == 0) {
            return index;
        }
        current = current->next;
        ++index;
    }

    return -1;
}


void print(void)
{
    int row;
    int col;

    printf("\n========== 辅存位示图 ==========\n");
    printf("总块数：%d\t空闲块数：%d\t字长：%d\n", sum, available, word);
    printf("行数：%d（每行对应一个字）\n", line);

    for (row = 0; row < line; ++row) {
        printf("字%03d: ", row);
        for (col = 0; col < word && row * word + col < sum; ++col) {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }
    printf("================================\n");
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

    print();
    printf("请输入作业名和作业需要的辅存空间大小：");
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

    if (find_job_index(job_name) != -1) {
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

    /*
     * TODO:
     * 1. 顺序扫描 map[][]，遇到 0 就尝试分配。
     * 2. 记录块号、字号、位号。
     * 3. 将物理块号换算为柱面号、磁头号、扇区号。
     * 4. 修改 map[][] 和 available，并把作业挂到 work 链表上。
     */
    found = 0;
    block_no = 0;
    for (row = 0; row < line && found < need_size; ++row) {
        for (col = 0; col < word && block_no < sum && found < need_size; ++col) {
            if (map[row][col] == 0) {
                node->a[found] = block_no;
                node->zihao[found] = row;
                node->weihao[found] = col;
                node->zhu[found] = block_no / cylinder;
                node->citou[found] = (block_no % cylinder) / sector;
                node->shanqu[found] = (block_no % cylinder) % sector;
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

    printf("\n作业 %s 分配成功，共分配 %d 块：\n", job_name, need_size);
    printf("%-6s %-8s %-8s %-8s %-8s %-8s\n",
           "块号", "字号", "位号", "柱面号", "磁头号", "扇区号");
    for (i = 0; i < need_size; ++i) {
        printf("%-6d %-8d %-8d %-8d %-8d %-8d\n",
               node->a[i], node->zihao[i], node->weihao[i],
               node->zhu[i], node->citou[i], node->shanqu[i]);
    }
    printf("剩余空闲块数：%d\n", available);
    print();
}

void recycle(void)
{
    char job_name[10];
    linklist *prev;
    linklist *current;
    int freed_size;
    int i;

    print();
    printf("请输入要回收的作业名：");
    if (scanf("%9s", job_name) != 1) {
        printf("输入格式错误，无法继续回收。\n");
        return;
    }

    /*
     * TODO:
     * 1. 在 work 链表中找到对应作业结点。
     * 2. 按记录的字号/位号把 map[][] 重新置为 0。
     * 3. 回收块数后更新 available。
     * 4. 从链表删除该结点并释放内存。
     */
    prev = NULL;
    current = work;
    while (current != NULL) {
        if (strcmp(current->name, job_name) == 0) {
            break;
        }
        prev = current;
        current = current->next;
    }

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

    printf("作业 %s 已成功回收，释放 %d 块，当前空闲块数：%d\n",
           job_name, freed_size, available);
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
    srand((unsigned int)time(NULL));

    mode = getenv("BITMAP_LAB_INIT_MODE");

    if (mode != NULL && strcmp(mode, "empty") == 0) {
        /* All-zeros for reproducible testing */
        for (row = 0; row < line; ++row) {
            for (col = 0; col < word && block_no < sum; ++col) {
                map[row][col] = 0;
                ++block_no;
            }
        }
    } else {
        /*
         * TODO:
         * 随机初始化：约 20% 的块随机标记为已占用，同步修正 available。
         */
        for (row = 0; row < line; ++row) {
            for (col = 0; col < word && block_no < sum; ++col) {
                if (rand() % 5 == 0) {
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

    printf("\n========== 菜单 ==========\n");
    printf("1. 为作业分配空间\n");
    printf("2. 回收作业空间\n");
    printf("0. 退出程序\n");
    printf("==========================\n");
    printf("请输入你的选择：");

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
        printf("程序结束。\n");
        break;
    default:
        printf("无效选项，请重新输入。\n");
        break;
    }

    return choice;
}
