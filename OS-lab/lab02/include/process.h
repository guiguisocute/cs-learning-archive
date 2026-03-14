#ifndef PROCESS_H
#define PROCESS_H

typedef struct data {
    int hour;
    int min;
} TimePoint;

typedef struct node {
    int process_id;
    char process_name[32];
    TimePoint arrival_time;
    int burst_time;
    TimePoint start_time;
    TimePoint finish_time;
    int turnaround_time;
    float weighted_turnaround_time;
    struct node *next; 
} ProcessNode;

//链表的一个结点，表示“一个进程一生的记录”

#endif
