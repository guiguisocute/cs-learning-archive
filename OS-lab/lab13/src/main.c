#include "device_manager.h"

#include <stdio.h>

int main(void) {
    device_system_t system;
    int channel_count = 0;
    int controller_count = 0;

    printf("请输入通道的数量：");
    if (scanf("%d", &channel_count) != 1) {
        return 1;
    }

    printf("请输入控制器的数量：");
    if (scanf("%d", &controller_count) != 1) {
        return 1;
    }

    init_device_system(&system, channel_count, controller_count);
    run_device_manager(&system);
    return 0;
}
