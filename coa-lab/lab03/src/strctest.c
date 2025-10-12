#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("input.txt", "rb");
    if (!fp)
    {
        perror("fopen");
        return 1;
    }

    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c < 0x80)
        {
            printf("%02X\n", c & 0xFF);
        }
        else
        {

            int c2 = fgetc(fp);
            if (c2 == EOF)
                break;
            printf("%02X%02X\n", c & 0xFF, c2 & 0xFF);
        }
    }

    fclose(fp);
    system("pause");
    return 0;
}
