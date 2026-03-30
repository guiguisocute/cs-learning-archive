#ifndef BANKER_H
#define BANKER_H

#include <stdbool.h>

#define MAX_RESOURCE_TYPES 10
#define MAX_PROCESSES 20
#define MAX_NAME_LEN 15

typedef struct {
    int resource_types;
    int process_count;
    int total[MAX_RESOURCE_TYPES];
    int available[MAX_RESOURCE_TYPES];
    int max[MAX_PROCESSES][MAX_RESOURCE_TYPES];
    int need[MAX_PROCESSES][MAX_RESOURCE_TYPES];
    int allocation[MAX_PROCESSES][MAX_RESOURCE_TYPES];
    int request[MAX_PROCESSES][MAX_RESOURCE_TYPES];
    int safe_sequence[MAX_PROCESSES];
    int work[MAX_RESOURCE_TYPES];
    int finish[MAX_PROCESSES];
    int state[MAX_PROCESSES];
    char name[MAX_PROCESSES][MAX_NAME_LEN];
} banker_system_t;

void banker_init(banker_system_t *system);
bool banker_read_initial_state(banker_system_t *system);
void banker_print_system_state(const banker_system_t *system);
int banker_find_process(const banker_system_t *system, const char *name);
bool banker_request_resources(
    banker_system_t *system,
    int process_index,
    const int request[]
);
bool banker_check_safe_sequence(banker_system_t *system, bool verbose);

#endif
