#include "rr_lab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 创建一个初始化为零时的时间结构体 */
static time make_zero_time(void)
{
    time t;

    t.hour = 0;
    t.minute = 0;
    return t;
}

/* 将时间结构体转换为总分钟数 */
static int time_to_minutes(time t)
{
    return t.hour * 60 + t.minute;
}

/* 将总分钟数转换为时间结构体 */
static time minutes_to_time(int total_minutes)
{
    time t;

    t.hour = total_minutes / 60;
    t.minute = total_minutes % 60;
    return t;
}

/* 在给定时间基础上增加指定的分钟数 */
static time add_minutes(time base, int delta)
{
    return minutes_to_time(time_to_minutes(base) + delta);
}

/* 计算两个时间之间的分钟差 */
static int diff_minutes(time end, time start)
{
    return time_to_minutes(end) - time_to_minutes(start);
}

/* 以HH:MM格式打印时间 */
static void print_time_field(time t)
{
    printf("%02d:%02d", t.hour, t.minute);
}

/* 将节点添加到队列的尾部（入队） */
static void enqueue(Queue *queue, Node *node)
{
    node->next = NULL;

    if (queue->tail == NULL)
    {
        queue->front = node;
        queue->tail = node;
        return;
    }

    queue->tail->next = node;
    queue->tail = node;
}

/* 从队列的头部移除并返回节点（出队） */
static Node *dequeue(Queue *queue)
{
    Node *node = queue->front;

    if (node == NULL)
    {
        return NULL;
    }

    queue->front = node->next;
    if (queue->front == NULL)
    {
        queue->tail = NULL;
    }

    node->next = NULL;
    return node;
}

/* 将已到达的进程从等待队列移到就绪队列 */
static void move_arrived_processes(Queue *wait, Queue *ready, time now)
{
    while (wait->front != NULL && timecompare(now, wait->front->arrive))
    {
        enqueue(ready, dequeue(wait));
    }
}

Queue *init(void)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue == NULL)
    {
        return NULL;
    }

    queue->front = NULL;
    queue->tail = NULL;
    return queue;
}

bool timecompare(time tt, time p)
{
    /* TODO: 将两个时间转换为总分钟数后比较大小。 */
    return time_to_minutes(tt) >= time_to_minutes(p);
}

bool Namecompare(const char *s1, const char *s2)
{
    /* TODO: 比较两个进程名的字典序。 */
    return strcmp(s1, s2) < 0;
}

bool Choose(Node *p, Node *q, int flag)
{
    /* TODO: flag == 1 时按到达时间比较，否则按名字比较。 更小时返回true*/
    if (flag == 1)
    {
        if (time_to_minutes(p->arrive) != time_to_minutes(q->arrive))
        {
            return time_to_minutes(p->arrive) < time_to_minutes(q->arrive);
        }

        return Namecompare(p->name, q->name);
    }
    return Namecompare(p->name, q->name);
}

void Time_or_Name_Sorted(Queue *que, int flag)
{

    /* TODO: 选择一种链表排序策略，对队列进行原地重排。 */
    // 维护一个 sorted 链表，把原链表结点逐个插入到正确位置。
    Node *sorted = NULL;
    Node *current = que->front;

    while (current != NULL)
    {
        Node *next = current->next;
        Node **indirect = &sorted;  //有序链表头指针的地址，

        while (*indirect != NULL && !Choose(current, *indirect, flag))
        {
            indirect = &(*indirect)->next;
        }

        current->next = *indirect;
        *indirect = current;
        current = next;
    }

    que->front = sorted;
    que->tail = NULL;
    current = que->front;
    while (current != NULL)
    {
        if (current->next == NULL)
        {
            que->tail = current;
        }

        current = current->next;
    }
}

time ComputeTime(time *tt, Node *q, int tp)
{
    /* TODO:
     * 1. 首次执行时记录开始时间；
     * 2. 更新当前开始时间、已完成时间、剩余时间；
     * 3. 完成时计算 finish / zz / zzxs。
     */
    int slice = q->sysj < tp ? q->sysj : tp;

    if (!q->started_flag)
    {
        q->start = *tt;
        q->started_flag = 1;
    }

    q->current = *tt;
    *tt = add_minutes(*tt, slice);
    q->ywcsj += slice;
    q->sysj -= slice;

    if (q->sysj == 0)
    {
        q->finish = *tt;
        q->zz = diff_minutes(q->finish, q->arrive);
        if (q->zx > 0)
        {
            q->zzxs = (float)q->zz / (float)q->zx;
        }
        else
        {
            q->zzxs = 0.0f;
        }
    }

    return *tt;
}

void Print_Current(Queue *que, time tt, int i)
{
    Node *current = que->front;

    (void)tt;
    printf("%d轮执行和就绪队列的结果:\n", i);
    printf("编号  名字  到达时间  总执行时间(分钟)  当前开始时间  已完成时间(分钟)  剩余完成时间(分钟)\n");

    while (current != NULL)
    {
        printf("%d  %s  ", current->id, current->name);
        print_time_field(current->arrive);
        printf("  %d  ", current->zx);

        if (current == que->front)
        {
            print_time_field(current->current);
        }
        else
        {
            printf("00:00");
        }

        printf("  %d  %d\n", current->ywcsj, current->sysj);
        current = current->next;
    }
}

Queue *Time_Slice_Rotation(Queue *que, int tp)
//最核心的函数捏
{
    /* TODO:
     * 1. 维护待到达队列、就绪队列和完成队列；
     * 2. 处理"当前进程完成 / 未完成 / CPU 暂时空闲"三种情况；
     * 3. 每轮调用 ComputeTime() 和 Print_Current()。
     */
    Queue ready = {NULL, NULL};
    Queue finished = {NULL, NULL};
    time now;
    int round = 1;

    if (que->front == NULL)
    {
        return que;
    }

    now = que->front->arrive;

    while (que->front != NULL || ready.front != NULL)
    {
        Node *current;
        Queue display;

        move_arrived_processes(que, &ready, now);

        if (ready.front == NULL)
        {
            now = que->front->arrive;
            move_arrived_processes(que, &ready, now);
        }

        current = dequeue(&ready);
        ComputeTime(&now, current, tp);
        move_arrived_processes(que, &ready, now);

        display.front = current;
        display.tail = current;
        if (ready.front != NULL)
        {
            current->next = ready.front;
            display.tail = ready.tail;
        }

        Print_Current(&display, now, round++);
        current->next = NULL;

        if (current->sysj == 0)
        {
            enqueue(&finished, current);
        }
        else
        {
            enqueue(&ready, current);
        }
    }

    que->front = finished.front;
    que->tail = finished.tail;
    return que;
}

void Print(Queue *que, int n)
{
    /* TODO: 按名字输出所有进程的统计信息，并计算系统平均指标。 */
    Node *current = que->front;
    float total_turnaround = 0.0f;
    float total_weighted_turnaround = 0.0f;

    printf("所有进程完成后的信息:\n");
    printf("编号  名字  到达时间  开始时间  完成时间  周转时间(分钟)  带权周转时间\n");

    while (current != NULL)
    {
        printf("%d  %s  ", current->id, current->name);
        print_time_field(current->arrive);
        printf("  ");
        print_time_field(current->start);
        printf("  ");
        print_time_field(current->finish);
        printf("  %d  %.2f\n", current->zz, current->zzxs);
        total_turnaround += (float)current->zz;
        total_weighted_turnaround += current->zzxs;
        current = current->next;
    }

    if (n > 0)
    {
        printf("系统平均周转时间: %.2f\n", total_turnaround / (float)n);
        printf("系统平均带权周转时间: %.2f\n", total_weighted_turnaround / (float)n);
    }
}

void ScanIn(Queue *wait, int n)
{
    int index;

    wait->front = NULL;
    wait->tail = NULL;

    printf("请输入进程的信息:\n");
    printf("编号  名字  到达时间  执行时间(分钟):\n");

    for (index = 0; index < n; ++index)
    {
        Node *node = (Node *)malloc(sizeof(Node));

        if (node == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        if (scanf("%d %19s %d:%d %d",
                  &node->id,
                  node->name,
                  &node->arrive.hour,
                  &node->arrive.minute,
                  &node->zx) != 5)
        {
            free(node);
            exit(EXIT_FAILURE);
        }

        node->start = make_zero_time();
        node->finish = make_zero_time();
        node->current = make_zero_time();
        node->zz = 0;
        node->zzxs = 0.0f;
        node->ywcsj = 0;
        node->sysj = node->zx;
        node->started_flag = 0;
        node->next = NULL;
        enqueue(wait, node);
    }
}

void FreeQueue(Queue *que)
{
    Node *current;

    if (que == NULL)
    {
        return;
    }

    current = que->front;
    while (current != NULL)
    {
        Node *next = current->next;

        free(current);
        current = next;
    }

    free(que);
}
