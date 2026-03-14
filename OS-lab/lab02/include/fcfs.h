#ifndef FCFS_H
#define FCFS_H

#include "queue.h"

int is_earlier_time(TimePoint first_time, TimePoint second_time);

void init_process_queue(ProcessQueue *queue);

void insert_process_by_arrival(ProcessQueue *queue, ProcessNode process_node);

void remove_front_process(ProcessQueue *queue);

void read_processes(ProcessQueue *queue);

TimePoint add_minutes_to_time(TimePoint start_time, int duration_minutes);

int calculate_time_difference(TimePoint earlier_time, TimePoint later_time);

void run_fcfs_schedule(ProcessQueue *queue);

void print_schedule_results(ProcessQueue *queue);

#endif
