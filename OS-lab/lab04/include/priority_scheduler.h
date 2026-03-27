#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include <stdbool.h>

#define PROCESS_NAME_LEN 20

typedef struct data {
    int hour;
    int minute;
} time;

typedef struct node {
    int id;
    char name[PROCESS_NAME_LEN];
    int good;   //优先级，数制越大越高
    time arrive;
    int zx;     //执行
    time start;
    time finish;
    int zz;     //周转，完成-到达
    float zzxs; //周转除执行
    struct node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *tail;
} Queue;

Queue *init(void);
bool timecompare(time current_time, time arrive_time);
bool timecompare2(time current_time, time arrive_time);
bool Levelcompare(Node *lhs, Node *rhs);
void LevelSorted(Queue *que);
time ComputeTime(time *current_time, Node *current_process);
Queue *priority(Queue *que, time current_time, int process_count);
void Print(Queue *que, int process_count);
time ScanIn(Queue *wait, int process_count);
void FreeQueue(Queue *que);

#endif
