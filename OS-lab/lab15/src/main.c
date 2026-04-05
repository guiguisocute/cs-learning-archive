#include "bitmap_lab.h"

int main(void)
{
    printf("请输入辅存空间的大小（单位：K）和字长（32 or 64）和块长（单位：K）：");
    if (scanf("%d %d %d", &disksize, &word, &blocksize) != 3) {
        fprintf(stderr, "输入格式错误，程序结束。\n");
        return 1;
    }

    printf("请输入该辅存硬盘的磁头数和每个磁道的扇区数：");
    if (scanf("%d %d", &head, &sector) != 2) {
        fprintf(stderr, "输入格式错误，程序结束。\n");
        return 1;
    }

    sum = available = disksize / blocksize;
    line = sum / word + (sum % word ? 1 : 0);
    cylinder = head * sector;

    init();

    while (1) {
        int choice = menu();

        if (choice == 0) {
            break;
        }
    }

    return 0;
}
