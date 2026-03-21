#ifndef SJF_LAB_H
#define SJF_LAB_H

#include <stdbool.h>

struct sched_time {
    int hour;   /* 小时 */
    int minute; /* 分钟 */
};

struct process_node {
    int process_id;                 /* 进程编号（唯一标识） */
    char process_name[20];          /* 进程名（最多 19 个字符 + 终止符） */
    struct sched_time arrival_time; /* 到达时间 */
    int cpu_burst_minutes;          /* 运行所需 CPU 时间（分钟） */
    struct sched_time start_time;   /* 实际开始执行时间 */
    struct sched_time finish_time;  /* 执行完成时间 */
    int turnaround_minutes;         /* 周转时间（完成时间 - 到达时间，分钟） */
    double weighted_turnaround;     /* 带权周转系数（周转时间 / 执行时间） */
    struct process_node *next;      /* 指向下一个进程结点 */
};

struct process_queue {
    struct process_node *head; /* 队首指针 */
    struct process_node *tail; /* 队尾指针 */
};

typedef struct sched_time sched_time;
typedef struct process_node process_node;
typedef struct process_queue process_queue;

process_queue *queue_create(void);
void enqueue_process(process_queue *proc_queue, process_node *new_process);
void dequeue_process(process_queue *proc_queue);
void schedule_input(process_queue *proc_queue);
void sort_by_arrival_time(process_queue *proc_queue);
void run_sjf_schedule(process_queue *proc_queue);
void queue_destroy(process_queue *proc_queue);

int sched_time_to_minutes(sched_time time_value);
sched_time minutes_to_sched_time(int total_minutes);
int compare_sched_time(sched_time left_time, sched_time right_time);
bool scan_sched_time(sched_time *out_time);

#endif
