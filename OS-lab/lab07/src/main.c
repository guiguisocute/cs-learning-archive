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

    /* TODO: 完成固定分区分配后，再观察这里打印出来的分区状态变化。 */
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
