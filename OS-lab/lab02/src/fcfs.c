#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fcfs.h"
#include "logger.h"

static int to_minutes(TimePoint time_point)
{
    return time_point.hour * 60 + time_point.min;
}

static TimePoint from_minutes(int total_minutes)
{
    TimePoint result_time;
    result_time.hour = total_minutes / 60;
    result_time.min = total_minutes % 60;
    return result_time;
}

static int display_width(const char *text)
{
    int width = 0;
    const unsigned char *cursor = (const unsigned char *)text;

    while (*cursor != '\0')
    {
        if (*cursor < 128)
        {
            width += 1;
            cursor++;
        }
        else
        {
            width += 2;
            if ((*cursor & 0xE0) == 0xC0)
            {
                cursor += 2;
            }
            else if ((*cursor & 0xF0) == 0xE0)
            {
                cursor += 3;
            }
            else if ((*cursor & 0xF8) == 0xF0)
            {
                cursor += 4;
            }
            else
            {
                cursor++;
            }
        }
    }

    return width;
}

static void format_time_text(TimePoint time_point, char *buffer, size_t buffer_size)
{
    snprintf(buffer, buffer_size, "%02d:%02d", time_point.hour, time_point.min);
}

static void format_float_text(float value, char *buffer, size_t buffer_size)
{
    snprintf(buffer, buffer_size, "%.2f", value);
}

static void print_cell(const char *text, int target_width)
{
    int padding = target_width - display_width(text);
    int i;

    printf("%s", text);
    for (i = 0; i < padding; i++)
    {
        putchar(' ');
    }
}


int is_earlier_time(TimePoint first_time, TimePoint second_time) {
    // TODO: 比较两个时间先后。
    if (first_time.hour != second_time.hour) {
        return first_time.hour < second_time.hour;
    }
    return first_time.min < second_time.min;
}

void init_process_queue(ProcessQueue *queue) {
    // TODO: 初始化队列头尾指针。
    queue->front = NULL;
    queue->rear = NULL;
}

void insert_process_by_arrival(ProcessQueue *queue, ProcessNode process_node) {
    // TODO: 按到达时间顺序插入到单链表。
    ProcessNode *new_node = (ProcessNode *)malloc(sizeof(ProcessNode));
    ProcessNode *current_node;

    if (new_node == NULL)
    {
        return;
    }

    *new_node = process_node;
    new_node->next = NULL;

    if (queue->front == NULL)
    {
        queue->front = new_node;
        queue->rear = new_node;
        return;
    }

    if (is_earlier_time(new_node->arrival_time, queue->front->arrival_time))
    {
        new_node->next = queue->front;
        queue->front = new_node;
        return;
    }

    current_node = queue->front;
    while (current_node->next != NULL
           && !is_earlier_time(new_node->arrival_time, current_node->next->arrival_time))
    {
        current_node = current_node->next;
    }

    new_node->next = current_node->next;
    current_node->next = new_node;

    if (new_node->next == NULL)
    {
        queue->rear = new_node;
    }
}

void remove_front_process(ProcessQueue *queue) {
    // TODO: 删除队头结点。
    ProcessNode *removed_node;

    if (queue->front == NULL)
    {
        return;
    }

    removed_node = queue->front;
    queue->front = queue->front->next;
    free(removed_node);

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
}

void read_processes(ProcessQueue *queue) {
    // TODO: 输入进程信息，并调用 insert_process_by_arrival() 按到达时间组织就绪队列。
    //
    // 建议输入格式：
    // n
    // id name hour:min zx
    int process_count;
    int index;

    printf("请输入进程数量：");
    if (scanf("%d", &process_count) != 1)
    {
        return;
    }
    printf("请输入进程的参数：\n");
    printf("id号  名字  到达时间  执行时间(分钟)：\n");

    for (index = 0; index < process_count; index++)
    {
        ProcessNode process_node;
        char colon;

        if (scanf("%d %31s %d%c%d %d",
                  &process_node.process_id,
                  process_node.process_name,
                  &process_node.arrival_time.hour,
                  &colon,
                  &process_node.arrival_time.min,
                  &process_node.burst_time) != 6)
        {
            return;
        }

        process_node.start_time.hour = 0;
        process_node.start_time.min = 0;
        process_node.finish_time.hour = 0;
        process_node.finish_time.min = 0;
        process_node.turnaround_time = 0;
        process_node.weighted_turnaround_time = 0.0f;
        process_node.next = NULL;

        insert_process_by_arrival(queue, process_node);
    }
}

TimePoint add_minutes_to_time(TimePoint start_time, int duration_minutes) {
    // TODO: 计算结束时间 = 开始时间 + 执行时间。
    return from_minutes(to_minutes(start_time) + duration_minutes);
}

int calculate_time_difference(TimePoint earlier_time, TimePoint later_time) {
    // TODO: 计算两个时刻之间相差多少分钟。
    return to_minutes(later_time) - to_minutes(earlier_time);
}

void run_fcfs_schedule(ProcessQueue *queue) {
    // TODO: 实现 FCFS 调度。
    ProcessNode *current_process;
    TimePoint current_cpu_time;

    if (queue->front == NULL)
    {
        return;
    }

    current_process = queue->front;
    current_cpu_time = current_process->arrival_time;

    while (current_process != NULL)
    {
        if (to_minutes(current_cpu_time) < to_minutes(current_process->arrival_time))
        {
            current_process->start_time = current_process->arrival_time;
        }
        else
        {
            current_process->start_time = current_cpu_time;
        }

        current_process->finish_time =
            add_minutes_to_time(current_process->start_time, current_process->burst_time);
        current_process->turnaround_time =
            calculate_time_difference(current_process->arrival_time, current_process->finish_time);
        current_process->weighted_turnaround_time =
            (float)current_process->turnaround_time / (float)current_process->burst_time;

        current_cpu_time = current_process->finish_time;
        current_process = current_process->next;
    }
}

void print_schedule_results(ProcessQueue *queue) {
    // TODO: 输出最终结果表，并计算平均周转时间、平均带权周转时间。
    ProcessNode *current_process = queue->front;
    int process_count = 0;
    float total_turnaround_time = 0.0f;
    float total_weighted_turnaround_time = 0.0f;

    printf("\n模拟进程FCFS调度过程输出结果：\n");
    print_cell("id号", 8);
    print_cell("名字", 12);
    print_cell("到达时间", 10);
    print_cell("执行时间(分钟)", 16);
    print_cell("开始时间", 10);
    print_cell("完成时间", 10);
    print_cell("周转时间(分钟)", 16);
    print_cell("带权周转系数", 14);
    putchar('\n');

    while (current_process != NULL)
    {
        char arrival_text[16];
        char start_text[16];
        char finish_text[16];
        char value_text[16];
        char turnaround_text[16];
        char weighted_turnaround_text[16];

        format_time_text(current_process->arrival_time, arrival_text, sizeof(arrival_text));
        format_time_text(current_process->start_time, start_text, sizeof(start_text));
        format_time_text(current_process->finish_time, finish_text, sizeof(finish_text));
        snprintf(value_text, sizeof(value_text), "%d", current_process->process_id);
        print_cell(value_text, 8);
        print_cell(current_process->process_name, 12);
        print_cell(arrival_text, 10);

        snprintf(value_text, sizeof(value_text), "%d", current_process->burst_time);
        print_cell(value_text, 16);
        print_cell(start_text, 10);
        print_cell(finish_text, 10);

        snprintf(turnaround_text, sizeof(turnaround_text), "%d", current_process->turnaround_time);
        print_cell(turnaround_text, 16);

        format_float_text(current_process->weighted_turnaround_time,
                          weighted_turnaround_text,
                          sizeof(weighted_turnaround_text));
        print_cell(weighted_turnaround_text, 14);
        putchar('\n');

        total_turnaround_time += (float)current_process->turnaround_time;
        total_weighted_turnaround_time += current_process->weighted_turnaround_time;
        process_count++;
        current_process = current_process->next;
    }

    if (process_count > 0)
    {
        printf("\n");
        printf("系统平均周转时间为: %.2f\n", total_turnaround_time / (float)process_count);
        printf("系统平均带权周转系数为: %.2f\n",
               total_weighted_turnaround_time / (float)process_count);
    }
}
