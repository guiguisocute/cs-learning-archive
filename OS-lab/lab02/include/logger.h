#ifndef LOGGER_H
#define LOGGER_H

#include "queue.h"

void print_time_point(TimePoint time_point);
void print_ready_queue(ProcessQueue *queue);
void print_fcfs_dispatch_reason(ProcessNode *process_node);

#endif
