#include "banker.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_vector(const int values[], int count) {
    for (int i = 0; i < count; ++i) {
        printf("%d", values[i]);
        if (i + 1 < count) {
            printf(" ");
        }
    }
}

static void recompute_need_and_available(banker_system_t *system) {
    for (int j = 0; j < system->resource_types; ++j) {
        int allocated_sum = 0;
        for (int i = 0; i < system->process_count; ++i) {
            system->need[i][j] = system->max[i][j] - system->allocation[i][j];
            allocated_sum += system->allocation[i][j];
        }
        system->available[j] = system->total[j] - allocated_sum;
    }
}

static bool vector_is_zero(const int values[], int count) {
    for (int i = 0; i < count; ++i) {
        if (values[i] != 0) {
            return false;
        }
    }
    return true;
}

static void update_process_states(banker_system_t *system) {
    for (int i = 0; i < system->process_count; ++i) {
        system->state[i] = vector_is_zero(system->need[i], system->resource_types) ? 1 : 0;
    }
}

static void print_process_rows(const banker_system_t *system) {
    printf("进程名  最大需求量   尚需求量   已分配量   执行状态:\n");
    for (int i = 0; i < system->process_count; ++i) {
        printf("%-6s", system->name[i]);
        print_vector(system->max[i], system->resource_types);
        printf("      ");
        print_vector(system->need[i], system->resource_types);
        printf("      ");
        print_vector(system->allocation[i], system->resource_types);
        printf("      %s\n", system->state[i] ? "finish" : "working");
    }
}

void banker_init(banker_system_t *system) {
    memset(system, 0, sizeof(*system));
}

bool banker_read_initial_state(banker_system_t *system) {
    printf("请输入资源种类的数量:\n");
    if (scanf("%d", &system->resource_types) != 1) {
        return false;
    }
    if (system->resource_types <= 0 || system->resource_types > MAX_RESOURCE_TYPES) {
        fprintf(stderr, "资源种类数量不合法。\n");
        return false;
    }

    printf("请输入进程的数量:\n");
    if (scanf("%d", &system->process_count) != 1) {
        return false;
    }
    if (system->process_count <= 0 || system->process_count > MAX_PROCESSES) {
        fprintf(stderr, "进程数量不合法。\n");
        return false;
    }

    printf("请输入%d类资源初始化的资源总数:\n", system->resource_types);
    for (int j = 0; j < system->resource_types; ++j) {
        if (scanf("%d", &system->total[j]) != 1) {
            return false;
        }
    }

    printf("请按“进程名 最大需求量 已分配量”输入进程信息:\n");
    printf("例如: p1 7 5 3 0 1 0\n");
    for (int i = 0; i < system->process_count; ++i) {
        if (scanf("%14s", system->name[i]) != 1) {
            return false;
        }
        for (int j = 0; j < system->resource_types; ++j) {
            if (scanf("%d", &system->max[i][j]) != 1) {
                return false;
            }
        }
        for (int j = 0; j < system->resource_types; ++j) {
            if (scanf("%d", &system->allocation[i][j]) != 1) {
                return false;
            }
            if (system->allocation[i][j] > system->max[i][j]) {
                fprintf(stderr, "%s 的已分配量不能大于最大需求量。\n", system->name[i]);
                return false;
            }
        }
    }

    recompute_need_and_available(system);
    for (int j = 0; j < system->resource_types; ++j) {
        if (system->available[j] < 0) {
            fprintf(stderr, "初始化数据不合法，某类资源已分配总量超过资源总数。\n");
            return false;
        }
    }

    update_process_states(system);
    printf("初始化完成!\n");
    banker_print_system_state(system);
    return true;
}

void banker_print_system_state(const banker_system_t *system) {
    print_process_rows(system);
    printf("系统剩余资源:");
    for (int j = 0; j < system->resource_types; ++j) {
        printf(" %d", system->available[j]);
    }
    printf("\n");
}

int banker_find_process(const banker_system_t *system, const char *name) {
    for (int i = 0; i < system->process_count; ++i) {
        if (strcmp(system->name[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

bool banker_check_safe_sequence(banker_system_t *system, bool verbose) {
    /*
     * TODO:
     * 1. 用 available 初始化 work。
     * 2. 用 finish 标记已经能够顺利完成的进程。
     * 3. 重复查找 need <= work 的进程，并把 allocation 回收到 work。
     * 4. 记录 safe_sequence。
     * 5. 若无法覆盖全部进程，则返回 false。
     */

    for (int j = 0; j < system->resource_types; ++j) {
        system->work[j] = system->available[j];
    }
    for (int i = 0; i < system->process_count; ++i) {
        system->finish[i] = 0;
    }

    int safe_count = 0;
    bool progress = true;
    while (safe_count < system->process_count && progress) {
        progress = false;
        for (int i = 0; i < system->process_count; ++i) {
            if (system->finish[i]) {
                continue;
            }

            bool can_finish = true;
            for (int j = 0; j < system->resource_types; ++j) {
                if (system->need[i][j] > system->work[j]) {
                    can_finish = false;
                    break;
                }
            }

            if (!can_finish) {
                continue;
            }

            for (int j = 0; j < system->resource_types; ++j) {
                system->work[j] += system->allocation[i][j];
            }
            system->finish[i] = 1;
            system->safe_sequence[safe_count++] = i;
            progress = true;
        }
    }

    if (safe_count != system->process_count) {
        if (verbose) {
            printf("申请失败! 当前状态不安全, 不存在安全序列。\n");
        }
        return false;
    }

    if (verbose) {
        printf("申请成功! 安全序列为:");
        for (int i = 0; i < safe_count; ++i) {
            printf("%s%s", i == 0 ? "" : "->", system->name[system->safe_sequence[i]]);
        }
        printf("\n");
    }
    return true;
}

static bool request_not_exceed_need(
    const banker_system_t *system,
    int process_index,
    const int request[]
) {
    for (int j = 0; j < system->resource_types; ++j) {
        if (request[j] > system->need[process_index][j]) {
            return false;
        }
    }
    return true;
}

static bool request_not_exceed_available(const banker_system_t *system, const int request[]) {
    for (int j = 0; j < system->resource_types; ++j) {
        if (request[j] > system->available[j]) {
            return false;
        }
    }
    return true;
}

static void apply_request(banker_system_t *system, int process_index, const int request[]) {
    for (int j = 0; j < system->resource_types; ++j) {
        system->available[j] -= request[j];
        system->allocation[process_index][j] += request[j];
        system->need[process_index][j] -= request[j];
        system->request[process_index][j] = request[j];
    }
    update_process_states(system);
}

static void rollback_request(banker_system_t *system, int process_index, const int request[]) {
    for (int j = 0; j < system->resource_types; ++j) {
        system->available[j] += request[j];
        system->allocation[process_index][j] -= request[j];
        system->need[process_index][j] += request[j];
        system->request[process_index][j] = 0;
    }
    update_process_states(system);
}

bool banker_request_resources(
    banker_system_t *system,
    int process_index,
    const int request[]
) {
    /*
     * TODO:
     * 1. 判断 request 是否超过 need。
     * 2. 判断 request 是否超过 available。
     * 3. 先做试探分配。
     * 4. 调用 banker_check_safe_sequence 判断是否安全。
     * 5. 若不安全则回滚；若安全则确认分配并输出安全序列。
     */

    if (!request_not_exceed_need(system, process_index, request)) {
        printf("申请失败! 申请量超过了该进程的剩余需求。\n");
        return false;
    }

    if (!request_not_exceed_available(system, request)) {
        printf("申请失败! 当前没有足够的系统剩余资源!\n");
        return false;
    }

    apply_request(system, process_index, request);
    if (!banker_check_safe_sequence(system, true)) {
        rollback_request(system, process_index, request);
        printf("已执行回滚操作，资源分配恢复到申请前状态。\n");
        return false;
    }

    banker_print_system_state(system);
    return true;
}

int main(void) {
    banker_system_t system;
    banker_init(&system);

    if (!banker_read_initial_state(&system)) {
        return EXIT_FAILURE;
    }

    while (1) {
        char answer[8];
        printf("\n是否需要申请资源?(Y/N):\n");
        if (scanf("%7s", answer) != 1) {
            return EXIT_FAILURE;
        }

        if (answer[0] == 'N' || answer[0] == 'n') {
            break;
        }
        if (answer[0] != 'Y' && answer[0] != 'y') {
            printf("请输入 Y 或 N。\n");
            continue;
        }

        char process_name[MAX_NAME_LEN];
        int request[MAX_RESOURCE_TYPES] = {0};

        printf("请输入进程名:\n");
        if (scanf("%14s", process_name) != 1) {
            return EXIT_FAILURE;
        }

        int process_index = banker_find_process(&system, process_name);
        if (process_index < 0) {
            printf("不存在名为 %s 的进程。\n", process_name);
            continue;
        }

        printf("请输入该进程当前申请的各个资源数量:\n");
        for (int j = 0; j < system.resource_types; ++j) {
            if (scanf("%d", &request[j]) != 1) {
                return EXIT_FAILURE;
            }
        }

        banker_request_resources(&system, process_index, request);
    }

    printf("程序结束。\n");
    return EXIT_SUCCESS;
}
