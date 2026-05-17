# 固定分区分配与回收参考实现

下面保存的是已经用样例验证过的一份完整参考实现。`src/` 目录当前留给学生的是 `TODO` 骨架，所以如果你想看可运行版本，可以先看这里。

## 参考思路

### `input()`

思考：

- 这个函数负责把单个分区的信息读入结构体。
- 新建分区时为什么状态应该初始化为空，而不是 `"0"`？

思路：

- 分区表真正的“空闲”标记放在打印阶段展示成 `0`。
- 内部实现里把空闲状态设为空字符串，更方便比较和回收。

### `print()`

思考：

- 终端显示的是学习接口，不一定等同于内部存储格式。
- 为什么空闲分区打印 `0`，而已占用分区打印作业名？

思路：

- 打印时统一判断状态字段是否为空。
- 为空时输出 `0`，否则直接输出作业名，效果就与截图一致。

### `allocate_job_to_partition()`

思考：

- 固定分区的关键决策是什么？
- 为什么样例中 30KB 不会进入 12KB 分区，而是进入 32KB 分区？

思路：

- 按分区表顺序扫描。
- 找到第一个“足够大且空闲”的分区就停止。
- 把状态改成 `JOB1`、`JOB2` 这种形式。

### `recycle_job_by_name()`

思考：

- 回收是按分区号还是按作业名进行？
- 如果输入的是 `2` 而不是 `JOB2`，程序该如何兼容？

思路：

- 先把输入统一转换成标准作业名。
- 再遍历分区表，找到状态匹配的分区并清空状态。

## 完整代码

### `include/partition.h`

```cpp
#ifndef PARTITION_H
#define PARTITION_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_PARTITIONS 110
#define MAX_JOBS 1000000
#define JOB_NAME_LEN 32

typedef struct partition_info {
    int id;
    int size_kb;
    int start_kb;
    char status[JOB_NAME_LEN];
} partition_info;

extern int n;
extern int m;
extern int job_sizes[MAX_JOBS + 5];
extern partition_info partitions[MAX_PARTITIONS];

partition_info input(void);
void print(void);
bool allocate_job_to_partition(int job_index);
bool recycle_job_by_name(const char *raw_name);
void normalize_job_name(const char *raw_name, char *normalized, size_t normalized_size);

#endif
```

### `src/partition.c`

```cpp
#include "partition.h"

#include <stdio.h>
#include <string.h>

int n = 0;
int m = 0;
int job_sizes[MAX_JOBS + 5];
partition_info partitions[MAX_PARTITIONS];

static bool is_partition_free(const partition_info *entry) {
    return entry->status[0] == '\0';
}

void normalize_job_name(const char *raw_name, char *normalized, size_t normalized_size) {
    if (normalized_size == 0U) {
        return;
    }

    if (raw_name == NULL || raw_name[0] == '\0') {
        normalized[0] = '\0';
        return;
    }

    if (strncmp(raw_name, "JOB", 3) == 0) {
        snprintf(normalized, normalized_size, "%s", raw_name);
        return;
    }

    snprintf(normalized, normalized_size, "JOB%s", raw_name);
}

partition_info input(void) {
    partition_info entry;

    scanf("%d%d%d", &entry.id, &entry.size_kb, &entry.start_kb);
    entry.status[0] = '\0';
    return entry;
}

void print(void) {
    int i;

    puts("**********打印分区信息**********");
    puts("分区号\t大小(KB)\t起址(KB)\t状态");
    for (i = 1; i <= n; ++i) {
        printf("%d\t%d\t\t%d\t\t", partitions[i].id, partitions[i].size_kb, partitions[i].start_kb);
        if (is_partition_free(&partitions[i])) {
            puts("0");
        } else {
            puts(partitions[i].status);
        }
    }
}

bool allocate_job_to_partition(int job_index) {
    int i;
    char job_name[JOB_NAME_LEN];

    snprintf(job_name, sizeof(job_name), "JOB%d", job_index);
    for (i = 1; i <= n; ++i) {
        if (partitions[i].size_kb >= job_sizes[job_index] && is_partition_free(&partitions[i])) {
            snprintf(partitions[i].status, sizeof(partitions[i].status), "%s", job_name);
            return true;
        }
    }

    return false;
}

bool recycle_job_by_name(const char *raw_name) {
    int i;
    char normalized[JOB_NAME_LEN];

    normalize_job_name(raw_name, normalized, sizeof(normalized));
    for (i = 1; i <= n; ++i) {
        if (strcmp(partitions[i].status, normalized) == 0) {
            partitions[i].status[0] = '\0';
            return true;
        }
    }

    return false;
}
```

### `src/main.c`

```cpp
#include "partition.h"

#include <stdio.h>

int main(void) {
    int i;
    char recycle_choice[8];
    char recycle_name[JOB_NAME_LEN];

    printf("请输入系统的分区块数：");
    scanf("%d", &n);

    printf("请依次输入：\n");
    printf("分区号 大小 起始\n");
    for (i = 1; i <= n; ++i) {
        partitions[i] = input();
    }
    print();

    printf("请输入作业的个数：");
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        printf("请输入作业%d的大小：", i);
        scanf("%d", &job_sizes[i]);
    }

    puts("打印各作业的信息：");
    puts("作业名 作业大小");
    for (i = 1; i <= m; ++i) {
        printf("JOB%d %dKB\n", i, job_sizes[i]);
    }

    for (i = 1; i <= m; ++i) {
        allocate_job_to_partition(i);
    }
    print();

    while (1) {
        printf("是否需要回收(y/n)？");
        scanf("%7s", recycle_choice);
        if (recycle_choice[0] == 'n' || recycle_choice[0] == 'N') {
            break;
        }

        printf("请输入回收的作业名：");
        scanf("%31s", recycle_name);
        recycle_job_by_name(recycle_name);
        puts("回收成功");
        print();
    }

    return 0;
}
```
