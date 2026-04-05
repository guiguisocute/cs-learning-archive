#include "device_manager.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void print_menu(void);
static void print_all_tables(const device_system_t *system);
static void print_sdt(const device_system_t *system);
static void print_dct(const device_system_t *system);
static void print_type_dct(const device_system_t *system, const char *device_type);
static void print_coct(const device_system_t *system);
static void print_chct(const device_system_t *system);
static void print_lut(const device_system_t *system);
static int find_sdt_index(const device_system_t *system, const char *device_type);
static int find_dct_by_type_relative(const device_system_t *system, const char *device_type, int relative_id);
static int find_lut_index(const device_system_t *system, const char *job_name);
static int assign_free_controller(device_system_t *system, int absolute_id);
static void release_controller_for_device(device_system_t *system, int absolute_id);
static bool add_device_type(device_system_t *system);
static bool allocate_devices(device_system_t *system);
static bool release_devices(device_system_t *system);
static bool read_token(char *buffer, size_t buffer_size);

void init_device_system(device_system_t *system, int channel_count, int controller_count) {
    int i;

    memset(system, 0, sizeof(*system));
    system->channel_count = channel_count;
    system->controller_count = controller_count;

    /*
     * TODO:
     * 1. 初始化 COCT：编号、名字、好坏、是否空闲、所属通道。
     * 2. 统计 available_controller_count。
     * 3. 让 CHCT 的打印结果能对应题目给出的通道分布。
     */
    for (i = 0; i < controller_count && i < MAX_CONTROLLER_COUNT; ++i) {
        system->coct[i].controller_id = i;
        snprintf(system->coct[i].name, sizeof(system->coct[i].name), "control_%d", i);
        system->coct[i].is_good = (i != 0);
        strcpy(system->coct[i].status, "yes");

        if (channel_count <= 0) {
            system->coct[i].channel_id = 0;
        } else if (channel_count == 1 || i == 0) {
            system->coct[i].channel_id = 0;
        } else {
            system->coct[i].channel_id = 1 + ((i - 1) % (channel_count - 1));
        }

        if (system->coct[i].is_good) {
            system->available_controller_count++;
        }
    }
}

void run_device_manager(device_system_t *system) {
    int option = -1;

    while (1) {
        print_menu();
        printf("请输入选项：");
        if (scanf("%d", &option) != 1) {
            return;
        }

        if (option == 0) {
            break;
        }

        if (option == 1) {
            if (add_device_type(system)) {
                print_all_tables(system);
            }
        } else if (option == 2) {
            if (allocate_devices(system)) {
                print_lut(system);
                print_all_tables(system);
            }
        } else if (option == 3) {
            if (release_devices(system)) {
                print_lut(system);
                print_all_tables(system);
            }
        } else {
            printf("无效选项，请重新输入！\n");
        }
    }
}

static void print_menu(void) {
    printf("**********设备独占分配管理**********\n");
    printf("      *   1.设备添加   *\n");
    printf("      *   2.设备分配   *\n");
    printf("      *   3.回收释放   *\n");
    printf("      *   0.退出      *\n");
}

static void print_all_tables(const device_system_t *system) {
    print_sdt(system);
    print_dct(system);
    print_coct(system);
    print_chct(system);
}

static void print_sdt(const device_system_t *system) {
    int i;

    /* TODO: 遍历 SDT，按题目表头输出。 */
    printf("**********打印系统设备表SDT**********\n");
    printf("%-10s %-12s %-12s %-10s\n", "设备类型", "设备总数量", "设备可用数量", "设备DCT号");
    for (i = 0; i < system->sdt_count; ++i) {
        printf("%-10s %-12d %-12d %-10d\n",
               system->sdt[i].device_type,
               system->sdt[i].total_count,
               system->sdt[i].available_count,
               system->sdt[i].sdt_id);
    }
}

static void print_dct(const device_system_t *system) {
    int i;

    /* TODO: 遍历 DCT，打印全部设备实例。 */
    printf("**********打印系统设备控制表DCT**********\n");
    printf("%-12s %-10s %-8s %-8s %-10s\n",
           "设备绝对号", "设备类型", "设备好坏", "设备空闲", "设备相对号");
    for (i = 0; i < system->dct_count; ++i) {
        printf("%-12d %-10s %-8s %-8s %-10d\n",
               system->dct[i].absolute_id,
               system->dct[i].device_type,
               system->dct[i].is_good ? "好" : "坏",
               system->dct[i].owner,
               system->dct[i].relative_id);
    }
}

static void print_type_dct(const device_system_t *system, const char *device_type) {
    int i;

    /* TODO: 只打印某一类设备，供用户选择相对号。 */
    printf("**********打印%s设备控制表DCT**********\n", device_type);
    printf("%-12s %-10s %-8s %-8s %-10s\n",
           "设备绝对号", "设备类型", "设备好坏", "设备空闲", "设备相对号");
    for (i = 0; i < system->dct_count; ++i) {
        if (strcmp(system->dct[i].device_type, device_type) == 0) {
            printf("%-12d %-10s %-8s %-8s %-10d\n",
                   system->dct[i].absolute_id,
                   system->dct[i].device_type,
                   system->dct[i].is_good ? "好" : "坏",
                   system->dct[i].owner,
                   system->dct[i].relative_id);
        }
    }
}

static void print_coct(const device_system_t *system) {
    int i;

    /* TODO: 遍历 COCT，打印控制器状态。 */
    printf("**********系统控制器控制表COCT**********\n");
    printf("%-4s %-10s %-4s %-8s %-8s\n", "编号", "名字", "好坏", "空闲", "所属通道");
    for (i = 0; i < system->controller_count; ++i) {
        printf("%-4d %-10s %-4s %-8s %-8d\n",
               system->coct[i].controller_id,
               system->coct[i].name,
               system->coct[i].is_good ? "好" : "坏",
               system->coct[i].status,
               system->coct[i].channel_id);
    }
    printf("系统剩余可用控制器数量：%d\n", system->available_controller_count);
}

static void print_chct(const device_system_t *system) {
    int channel_id;
    int first;
    int i;

    /* TODO: 根据控制器所属通道关系，打印每个通道下的控制器序号列表。 */
    printf("**********系统通道控制表CHCT**********\n");
    printf("%-4s %s\n", "编号", "通道内控制器序号");
    for (channel_id = 0; channel_id < system->channel_count; ++channel_id) {
        printf("%-4d ", channel_id);
        first = 1;
        for (i = 0; i < system->controller_count; ++i) {
            if (system->coct[i].channel_id == channel_id) {
                if (!first) {
                    printf(",");
                }
                printf("%d", system->coct[i].controller_id);
                first = 0;
            }
        }
        printf("\n");
    }
}

static void print_lut(const device_system_t *system) {
    int i;
    int j;

    /* TODO: 按作业名打印 LUT，每个作业下面列出占用设备的相对号、绝对号、SDT号。 */
    printf("**********系统逻辑单位表LUT**********\n");
    for (i = 0; i < system->lut_count; ++i) {
        printf("%s占用设备的设备相对号和设备绝对号及SDT号：\n", system->lut[i].job_name);
        printf("%-12s %-10s %-6s\n", "设备相对号", "设备绝对号", "SDT号");
        for (j = 0; j < system->lut[i].count; ++j) {
            printf("%-12d %-10d %-6d\n",
                   system->lut[i].items[j].relative_id,
                   system->lut[i].items[j].absolute_id,
                   system->lut[i].items[j].sdt_id);
        }
    }
}

static int find_sdt_index(const device_system_t *system, const char *device_type) {
    int i;

    for (i = 0; i < system->sdt_count; ++i) {
        if (strcmp(system->sdt[i].device_type, device_type) == 0) {
            return i;
        }
    }
    return -1;
}

static int find_dct_by_type_relative(const device_system_t *system, const char *device_type, int relative_id) {
    int i;

    for (i = 0; i < system->dct_count; ++i) {
        if (strcmp(system->dct[i].device_type, device_type) == 0 &&
            system->dct[i].relative_id == relative_id) {
            return i;
        }
    }
    return -1;
}

static int find_lut_index(const device_system_t *system, const char *job_name) {
    int i;

    for (i = 0; i < system->lut_count; ++i) {
        if (strcmp(system->lut[i].job_name, job_name) == 0) {
            return i;
        }
    }
    return -1;
}

static int assign_free_controller(device_system_t *system, int absolute_id) {
    int i;

    for (i = 0; i < system->controller_count; ++i) {
        if (system->coct[i].is_good && strcmp(system->coct[i].status, "yes") == 0) {
            snprintf(system->coct[i].status, sizeof(system->coct[i].status), "%d", absolute_id);
            system->available_controller_count--;
            return i;
        }
    }
    return -1;
}

static void release_controller_for_device(device_system_t *system, int absolute_id) {
    int i;
    char target[MAX_NAME_LEN];

    snprintf(target, sizeof(target), "%d", absolute_id);
    for (i = 0; i < system->controller_count; ++i) {
        if (system->coct[i].is_good && strcmp(system->coct[i].status, target) == 0) {
            strcpy(system->coct[i].status, "yes");
            system->available_controller_count++;
            return;
        }
    }
}

static bool add_device_type(device_system_t *system) {
    char device_type[MAX_NAME_LEN];
    int add_count = 0;
    int sdt_index;
    int start_relative;
    int i;

    printf("请输入添加的设备类型：");
    if (!read_token(device_type, sizeof(device_type))) {
        return false;
    }

    printf("请输入添加的数量：");
    if (scanf("%d", &add_count) != 1 || add_count <= 0) {
        printf("添加失败！数量非法！\n");
        return false;
    }

    sdt_index = find_sdt_index(system, device_type);
    if (sdt_index < 0) {
        if (system->sdt_count >= MAX_DEVICE_TYPES) {
            printf("添加失败！设备类型表已满！\n");
            return false;
        }

        sdt_index = system->sdt_count;
        memset(&system->sdt[sdt_index], 0, sizeof(system->sdt[sdt_index]));
        strcpy(system->sdt[sdt_index].device_type, device_type);
        system->sdt[sdt_index].sdt_id = sdt_index;
        system->sdt_count++;
    }

    start_relative = system->sdt[sdt_index].total_count;
    if (system->dct_count + add_count > MAX_DEVICE_COUNT) {
        printf("添加失败！设备表容量不足！\n");
        return false;
    }

    for (i = 0; i < add_count; ++i) {
        dct_entry_t *entry = &system->dct[system->dct_count++];
        entry->absolute_id = system->next_absolute_id++;
        strcpy(entry->device_type, device_type);
        entry->relative_id = start_relative + i;
        entry->is_good = (entry->relative_id != 0);
        strcpy(entry->owner, "yes");
        if (entry->is_good) {
            system->sdt[sdt_index].available_count++;
        }
    }

    system->sdt[sdt_index].total_count += add_count;
    printf("添加成功！\n");
    return true;
}

static bool allocate_devices(device_system_t *system) {
    char job_name[MAX_NAME_LEN];
    char device_type[MAX_NAME_LEN];
    int request_count = 0;
    int sdt_index;
    int item_index;

    printf("请输入作业名：");
    if (!read_token(job_name, sizeof(job_name))) {
        return false;
    }

    if (find_lut_index(system, job_name) >= 0) {
        printf("分配失败！作业名已存在！\n");
        return false;
    }

    printf("请输入作业所需的设备类型：");
    if (!read_token(device_type, sizeof(device_type))) {
        return false;
    }

    sdt_index = find_sdt_index(system, device_type);
    if (sdt_index < 0) {
        printf("分配失败！系统中不存在该设备类型！\n");
        return false;
    }

    printf("设备可用数量为：%d\n", system->sdt[sdt_index].available_count);
    printf("请输入作业所需的设备数量：");
    if (scanf("%d", &request_count) != 1 || request_count <= 0) {
        printf("分配失败！数量非法！\n");
        return false;
    }

    if (request_count > system->sdt[sdt_index].available_count ||
        request_count > system->available_controller_count) {
        printf("分配失败！可用设备或控制器数量不足！\n");
        return false;
    }

    if (system->lut_count >= MAX_JOB_COUNT) {
        printf("分配失败！LUT已满！\n");
        return false;
    }

    print_type_dct(system, device_type);
    memset(&system->lut[system->lut_count], 0, sizeof(system->lut[system->lut_count]));
    strcpy(system->lut[system->lut_count].job_name, job_name);

    for (item_index = 0; item_index < request_count; ++item_index) {
        int relative_id = -1;
        int dct_index = -1;

        while (1) {
            printf("请输入你选择的设备的设备相对号：");
            if (scanf("%d", &relative_id) != 1) {
                return false;
            }

            dct_index = find_dct_by_type_relative(system, device_type, relative_id);
            if (dct_index < 0 ||
                !system->dct[dct_index].is_good ||
                strcmp(system->dct[dct_index].owner, "yes") != 0) {
                printf("分配失败！请重新申请！\n");
                continue;
            }

            if (assign_free_controller(system, system->dct[dct_index].absolute_id) < 0) {
                printf("分配失败！请重新申请！\n");
                continue;
            }

            strcpy(system->dct[dct_index].owner, job_name);
            system->sdt[sdt_index].available_count--;
            system->lut[system->lut_count].items[item_index].relative_id = system->dct[dct_index].relative_id;
            system->lut[system->lut_count].items[item_index].absolute_id = system->dct[dct_index].absolute_id;
            system->lut[system->lut_count].items[item_index].sdt_id = sdt_index;
            system->lut[system->lut_count].count++;
            printf("分配成功！\n");
            break;
        }
    }

    system->lut_count++;
    return true;
}

static bool release_devices(device_system_t *system) {
    char job_name[MAX_NAME_LEN];
    int lut_index;
    int i;

    printf("请输入要回收的作业名：");
    if (!read_token(job_name, sizeof(job_name))) {
        return false;
    }

    lut_index = find_lut_index(system, job_name);
    if (lut_index < 0) {
        printf("回收失败！无法找到作业对应的设备！请重新申请回收！\n");
        return false;
    }

    for (i = 0; i < system->lut[lut_index].count; ++i) {
        int absolute_id = system->lut[lut_index].items[i].absolute_id;
        int sdt_id = system->lut[lut_index].items[i].sdt_id;
        int dct_index = -1;
        int j;

        for (j = 0; j < system->dct_count; ++j) {
            if (system->dct[j].absolute_id == absolute_id) {
                dct_index = j;
                break;
            }
        }

        if (dct_index >= 0) {
            strcpy(system->dct[dct_index].owner, "yes");
            if (system->dct[dct_index].is_good) {
                system->sdt[sdt_id].available_count++;
            }
            release_controller_for_device(system, absolute_id);
        }
    }

    for (i = lut_index; i + 1 < system->lut_count; ++i) {
        system->lut[i] = system->lut[i + 1];
    }
    system->lut_count--;
    printf("回收成功！\n");
    return true;
}

static bool read_token(char *buffer, size_t buffer_size) {
    if (scanf("%31s", buffer) != 1) {
        return false;
    }
    buffer[buffer_size - 1] = '\0';
    return true;
}
