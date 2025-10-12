#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TARGET_COUNT 2000000
#define COLS 10

// 比较函数，用于排序去重（可选）
int cmp(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y;
}

// 哈希方式（简单数组查重太慢），使用 qsort 后去重
int main()
{
    int *nums = malloc(sizeof(int) * TARGET_COUNT * 2); // 多分点防止重复
    if (!nums)
    {
        perror("内存分配失败");
        return 1;
    }

    srand(time(NULL));

    int count = 0;
    while (count < TARGET_COUNT)
    {
        int r = rand() * rand(); // 可生成较大值（注意 rand() 范围）
        nums[count++] = r;
    }

    // 排序后去重
    qsort(nums, count, sizeof(int), cmp);
    int unique_count = 1;
    for (int i = 1; i < count && unique_count < TARGET_COUNT; i++)
    {
        if (nums[i] != nums[unique_count - 1])
        {
            nums[unique_count++] = nums[i];
        }
    }

    // 如不够，再补充
    while (unique_count < TARGET_COUNT)
    {
        int r = rand() * rand();
        int exists = 0;
        for (int i = 0; i < unique_count; i++)
        {
            if (nums[i] == r)
            {
                exists = 1;
                break;
            }
        }
        if (!exists)
        {
            nums[unique_count++] = r;
        }
    }

    // 写入文件
    FILE *fp = fopen("data1.txt", "w");
    if (!fp)
    {
        perror("打开文件失败");
        free(nums);
        return 1;
    }

    for (int i = 0; i < TARGET_COUNT; i++)
    {
        fprintf(fp, "%d%c", nums[i], (i % COLS == COLS - 1) ? '\n' : ' ');
    }

    fclose(fp);
    free(nums);
    printf("完成，已写入 %d 个不重复随机整数。\n", TARGET_COUNT);
    return 0;
}
