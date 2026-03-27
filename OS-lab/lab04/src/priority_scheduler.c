#include "priority_scheduler.h"

#include <stdio.h>
#include <stdlib.h>

static int to_minutes(time value)
{
    return value.hour * 60 + value.minute;
}

static time from_minutes(int total_minutes)
{
    time result;

    result.hour = total_minutes / 60;
    result.minute = total_minutes % 60;
    return result;
}

static void append_node(Queue *que, Node *node)
{
    node->next = NULL;

    if (que->tail == NULL)
    {
        que->front = node;
        que->tail = node;
        return;
    }

    que->tail->next = node;
    que->tail = node;
}

static Node *detach_node(Queue *que, Node *target_prev, Node *target)
// 作用：把目标进程结点从当前队列里摘下来，但不释放内存
{
    if (target_prev == NULL)
    {
        que->front = target->next;
    }
    else
    {
        target_prev->next = target->next;
    }

    if (que->tail == target)
    {
        que->tail = target_prev;
    }

    target->next = NULL;
    return target;
}

Queue *init(void) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue == NULL) {
        return NULL;
    }

    queue->front = NULL;
    queue->tail = NULL;
    return queue;
}

bool has_arrived(time current_time, time arrive_time) {
    /* TODO:
     * 1. 把两个时间统一转换为分钟数。
     * 2. 按实验要求判断 current_time >= arrive_time 是否成立。
     */
    return to_minutes(current_time) >= to_minutes(arrive_time);
    //主要是判断是否到达
}

bool is_latter_than(time current_time, time arrive_time) {
    /* TODO:
     * 1. 同样先转换为分钟数。
     * 2. 判断 current_time > arrive_time，用于区分“刚好到达”和“已经等待”。
     */
    //严格早于
    return to_minutes(current_time) > to_minutes(arrive_time);
}

bool Levelcompare(Node *lhs, Node *rhs) {
    /* TODO:
     * 1. 先比较优先级 good，数字大的优先。
     * 2. 如果优先级相同，再比较到达时间。
     * 3. 如果仍相同，可以继续比较输入顺序或编号，保证结果稳定。
     */
    int lhs_arrive;
    int rhs_arrive;

    if (lhs == NULL)
    {
        return false;
    }

    if (rhs == NULL)
    {
        return true;
    }

    if (lhs->good != rhs->good)
    {
        return lhs->good > rhs->good;
    }

    lhs_arrive = to_minutes(lhs->arrive);
    rhs_arrive = to_minutes(rhs->arrive);
    if (lhs_arrive != rhs_arrive)
    {
        return lhs_arrive < rhs_arrive;
    }
    //同优先级且同arrive，不打乱顺序
    return false;
}

void LevelSorted(Queue *que) {
    /* TODO:
     * 按到达时间对初始队列做一次排序，保证最早到达的进程先出现在队首。
     * 建议边画链表边实现，确认 front/tail 是否一起更新。
     */
    //只负责粗排到达时间
    Node *sorted_front = NULL;
    Node *sorted_tail = NULL;
    Node *current;

    if (que == NULL || que->front == NULL)
    {
        return;
    }

    current = que->front;
    while (current != NULL)
    {
        Node *next = current->next;

        if (sorted_front == NULL ||
            to_minutes(current->arrive) < to_minutes(sorted_front->arrive))
        {
            current->next = sorted_front;
            sorted_front = current;
            if (sorted_tail == NULL)
            {
                sorted_tail = current;
            }
        }
        else
        {
            Node *scan = sorted_front;

            while (scan->next != NULL &&
                   to_minutes(scan->next->arrive) <= to_minutes(current->arrive))
            {
                scan = scan->next;
            }

            current->next = scan->next;
            scan->next = current;
            if (current->next == NULL)
            {
                sorted_tail = current;
            }
        }

        current = next;
    }

    que->front = sorted_front;
    que->tail = sorted_tail;
}

time ComputeTime(time *current_time, Node *current_process) {
    time zero_time = {0, 0};

    /* TODO:
     * 1. 计算开始时间：当前 CPU 空闲则取到达时间，否则取 current_time。
     * 2. 根据执行时间 zx 计算完成时间。
     * 3. 回填 zz 和 zzxs。
     * 4. 别忘了同步更新 *current_time。
     */
    int current_minutes = to_minutes(*current_time);
    int arrive_minutes = to_minutes(current_process->arrive);
    int start_minutes;
    int finish_minutes;

    if (current_minutes < arrive_minutes)
    {
        current_minutes = arrive_minutes;
    }

    start_minutes = current_minutes;
    finish_minutes = start_minutes + current_process->zx;

    current_process->start = from_minutes(start_minutes);
    current_process->finish = from_minutes(finish_minutes);
    current_process->zz = finish_minutes - arrive_minutes;
    if (current_process->zx > 0)
    {
        current_process->zzxs = (float)current_process->zz / (float)current_process->zx;
    }
    else
    {
        current_process->zzxs = 0.0f;
    }

    *current_time = current_process->finish;
    return current_process->finish;
}

Queue *priority(Queue *que, time current_time, int process_count) {
    /* TODO:
     * 1. 从已按到达时间排好的队列中，循环挑选“已经到达且优先级最高”的进程。
     * 2. 如果当前没有任何进程到达，应把 current_time 跳到下一进程到达时刻。
     * 3. 每调度一个进程，都要调用 ComputeTime 更新其时间信息。
     * 4. 返回按实际执行顺序重组后的结果队列。
     */
    Queue *result;
    int finished_count = 0;

    if (que == NULL)
    {
        return NULL;
    }

    result = init();
    if (result == NULL)
    {
        FreeQueue(que);
        return NULL;
    }

    while (finished_count < process_count && que->front != NULL)
    {
        Node *best = NULL;
        Node *best_prev = NULL;
        Node *prev = NULL;
        Node *current = que->front;

        while (current != NULL && has_arrived(current_time, current->arrive))
        {
            if (best == NULL || Levelcompare(current, best))
            {
                best = current;
                best_prev = prev;
            }

            prev = current;
            current = current->next;
        }

        if (best == NULL)
        {
            current_time = que->front->arrive;
            continue;
        }

        best = detach_node(que, best_prev, best);
        ComputeTime(&current_time, best);
        append_node(result, best);
        ++finished_count;
    }

    free(que);
    return result;
}

void Print(Queue *que, int process_count) {
    /* TODO:
     * 1. 参照截图打印表头和每个进程的调度结果。
     * 2. 遍历时累计平均周转时间和平均带权周转系数。
     * 3. 输出时注意时间格式补零，例如 09:40。
     */
    Node *current;
    double total_zz = 0.0;
    double total_zzxs = 0.0;

    if (que == NULL)
    {
        return;
    }

    printf("模拟进程优先调度过程输出结果\n");
    printf("id号  名字  优先级  到达时间  执行时间(分钟)  开始时间  完成时间  周转时间(分钟)  带权周转系数\n");

    current = que->front;
    while (current != NULL)
    {
        char turnaround_text[32];

        total_zz += current->zz;
        total_zzxs += current->zzxs;
        snprintf(turnaround_text, sizeof(turnaround_text), "%d(分钟)", current->zz);

        printf("%-5d %-5s %-7d %02d:%02d     %-15d %02d:%02d     %02d:%02d     %-17s %.2f\n",
               current->id,
               current->name,
               current->good,
               current->arrive.hour,
               current->arrive.minute,
               current->zx,
               current->start.hour,
               current->start.minute,
               current->finish.hour,
               current->finish.minute,
               turnaround_text,
               current->zzxs);

        current = current->next;
    }

    printf("系统平均周转时间为:\n");
    printf("%.2f\n", total_zz / (double)process_count);
    printf("系统平均带权周转系数为:\n");
    printf("%.2f\n", total_zzxs / (double)process_count);
}

time ScanIn(Queue *wait, int process_count) {
    time early_time = {0, 0};

    /* TODO:
     * 1. 读取 id、name、good、arrive、zx。
     * 2. 为每个进程分配结点并挂到 wait 队尾。
     * 3. 在读入过程中记录最早到达时间，作为初始 current_time。
     */
    printf("请输入进程的参数:\n");
    printf("id号  名字  优先级  到达时间  执行时间(分钟):\n");

    for (int i = 0; i < process_count; ++i)
    {
        Node *node = (Node *)malloc(sizeof(Node));

        if (node == NULL)
        {
            return early_time;
        }

        if (scanf("%d %19s %d %d:%d %d",
                  &node->id,
                  node->name,
                  &node->good,
                  &node->arrive.hour,
                  &node->arrive.minute,
                  &node->zx) != 6)
        {
            free(node);
            return early_time;
        }

        node->start = node->arrive;
        node->finish = node->arrive;
        node->zz = 0;
        node->zzxs = 0.0f;
        node->next = NULL;

        if (i == 0 || is_latter_than(early_time, node->arrive))
        {
            early_time = node->arrive;
        }

        append_node(wait, node);
    }

    LevelSorted(wait);
    return early_time;
}

void FreeQueue(Queue *que) {
    Node *current;

    if (que == NULL) {
        return;
    }

    current = que->front;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(que);
}
