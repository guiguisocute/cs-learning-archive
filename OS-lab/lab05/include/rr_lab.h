#ifndef RR_LAB_H
#define RR_LAB_H

#include <stdbool.h>

#define PROCESS_NAME_LEN 20

typedef struct data {
    int hour;
    int minute;
} time;

typedef struct node {
    int id;
    char name[PROCESS_NAME_LEN];
    time arrive;       //到达时间
    int zx;            //总执行时间
    time start;        //首次开始时间
    time finish;       //完成时间
    int zz;            //周转时间
    float zzxs;        //带权周转时间
    time current;      //当前轮开始时间
    int ywcsj;         //已完成时间
    int sysj;          //剩余时间
    int started_flag;  //是否已首次运行
    struct node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *tail;
} Queue;

Queue *init(void);
bool timecompare(time tt, time p);
bool Namecompare(const char *s1, const char *s2);
bool Choose(Node *p, Node *q, int flag);
void Time_or_Name_Sorted(Queue *que, int flag);
time ComputeTime(time *tt, Node *q, int tp);
void Print_Current(Queue *que, time tt, int i);
Queue *Time_Slice_Rotation(Queue *que, int tp);
void Print(Queue *que, int n);
void ScanIn(Queue *wait, int n);
void FreeQueue(Queue *que);

#endif
