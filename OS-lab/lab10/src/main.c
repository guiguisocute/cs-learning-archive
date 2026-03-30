#include "segment_manager.h"

#include <stdio.h>

int main(void)
{
    node *head = initMemory();

    if (head == NULL)
    {
        fprintf(stderr, "初始化主存失败。\n");
        return 1;
    }

    while (1)
    {
        if (operation(head) == 1)
        {
            break;
        }
    }

    destroy_all(head);
    return 0;
}
