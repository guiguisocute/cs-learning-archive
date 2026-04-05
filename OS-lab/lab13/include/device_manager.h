#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_DEVICE_TYPES 16
#define MAX_DEVICE_COUNT 128
#define MAX_CONTROLLER_COUNT 64
#define MAX_CHANNEL_COUNT 32
#define MAX_JOB_COUNT 64
#define MAX_JOB_DEVICE_COUNT 32
#define MAX_NAME_LEN 32

typedef struct {
    int absolute_id;
    char device_type[MAX_NAME_LEN];
    bool is_good;
    char owner[MAX_NAME_LEN];
    int relative_id;
} dct_entry_t;

typedef struct {
    char device_type[MAX_NAME_LEN];
    int total_count;
    int available_count;
    int sdt_id;
} sdt_entry_t;

typedef struct {
    int controller_id;
    char name[MAX_NAME_LEN];
    bool is_good;
    char status[MAX_NAME_LEN];
    int channel_id;
} coct_entry_t;

typedef struct {
    int relative_id;
    int absolute_id;
    int sdt_id;
} lut_item_t;

typedef struct {
    char job_name[MAX_NAME_LEN];
    int count;
    lut_item_t items[MAX_JOB_DEVICE_COUNT];
} lut_entry_t;

typedef struct {
    int channel_count;
    int controller_count;
    int next_absolute_id;
    int sdt_count;
    int dct_count;
    int lut_count;
    int available_controller_count;
    sdt_entry_t sdt[MAX_DEVICE_TYPES];
    dct_entry_t dct[MAX_DEVICE_COUNT];
    coct_entry_t coct[MAX_CONTROLLER_COUNT];
    lut_entry_t lut[MAX_JOB_COUNT];
} device_system_t;

void init_device_system(device_system_t *system, int channel_count, int controller_count);
void run_device_manager(device_system_t *system);

#endif
