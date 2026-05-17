#include "bitmap_lab.h"

int main(void)
{
    printf("请输入辅存空间的大小（单位：K）和字长（32 or 64）和块长（单位：K）：");
    if (scanf("%d %d %d", &disksize, &word, &blocksize) != 3) {
        fprintf(stderr, "输入格式错误，程序结束。\n");
        return 1;
    }

    if (disksize <= 0 || blocksize <= 0 || word <= 0 || word > MAX_BITMAP_COLS) {
        fprintf(stderr, "辅存大小、字长和块长参数不合法，程序结束。\n");
        return 1;
    }

    printf("请输入该辅存硬盘的磁道数（磁头数）和每个磁道的扇区数：");
    if (scanf("%d %d", &head, &sector) != 2) {
        fprintf(stderr, "输入格式错误，程序结束。\n");
        return 1;
    }

    if (head <= 0 || sector <= 0) {
        fprintf(stderr, "磁头数和每磁道扇区数必须大于 0，程序结束。\n");
        return 1;
    }

    sum = available = disksize / blocksize;
    line = sum / word + (sum % word ? 1 : 0);
    cylinder = head * sector;

    if (sum <= 0 || line > MAX_BITMAP_ROWS) {
        fprintf(stderr, "位示图规模超出程序限制，程序结束。\n");
        return 1;
    }

    init();

    while (1) {
        int choice = menu();

        if (choice == 0) {
            break;
        }
    }

    return 0;
}
