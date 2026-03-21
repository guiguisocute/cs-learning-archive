#include "sjf_lab.h"

#include <stdio.h>
#include <stdlib.h>



//类型工具类
typedef struct {
    process_node **nodes;
    int count; // 当前已经存了多少个进程指针（已使用长度）
    int capacity;     // nodes 这块内存最多还能容纳多少个元素（总容量）
} process_node_array; // 把链表节点临时放进动态数组，方便 qsort 排序
//算是用这种方式实现了一种类似于对象数组的数据结构？非常神奇的做法，不愧是claude，

static process_node *create_process_node(void) {
    process_node *new_process = (process_node *)calloc(1, sizeof(process_node));

    if (new_process == NULL) {
        fprintf(stderr, "内存分配失败。\n");
        exit(EXIT_FAILURE);
    }

    return new_process;
}

static int queue_length(const process_queue *proc_queue) {
    int node_count = 0;
    process_node *current_process = NULL;

    if (proc_queue == NULL) {
        return 0;
    }

    for (current_process = proc_queue->head; current_process != NULL;
         current_process = current_process->next) {
        node_count++;
    }

    return node_count;
}//统计这个队列的长度

static void append_process(process_node_array *node_array, process_node *proc)
    // 输入：一个动态数组 node_array，一个要加入的进程指针 proc。
    //输出：把 proc 放到数组末尾。 保证：追加后仍满足不越界,主要是为了这个保证
    {
    process_node **new_nodes = NULL;

    if (node_array->count == node_array->capacity) {
        int new_capacity = node_array->capacity == 0 ? 8 : node_array->capacity * 2;
//一个手动扩容的过程
        new_nodes = (process_node **)realloc(node_array->nodes,
                                             (size_t)new_capacity * sizeof(process_node *));
        if (new_nodes == NULL) {
            fprintf(stderr, "内存扩容失败。\n");
            free(node_array->nodes);
            exit(EXIT_FAILURE);
        }

        node_array->nodes = new_nodes;
        node_array->capacity = new_capacity;
    }

    node_array->nodes[node_array->count++] = proc;
}

/*
 * 先按到达时间排序。
 * 如果到达时间相同，再按 process_id 排序，保证结果稳定。
 */
static int compare_arrival_then_id(const void *lhs,
                                   const void *rhs) { // 这个传参是为了qsort的固定函数签名
    // qsort(数组首地址, 元素个数, 每个元素字节数, 比较函数);草啊学到这个操作系统了才明白qsort的传参为什么要这么复杂，因为C还真有手搓复杂结构体数组的需求必须得这样
    const process_node *left_process = *(const process_node *const *)lhs;
    const process_node *right_process = *(const process_node *const *)rhs;
    int left_arrival_minutes = sched_time_to_minutes(left_process->arrival_time);
    int right_arrival_minutes = sched_time_to_minutes(right_process->arrival_time);

    if (left_arrival_minutes != right_arrival_minutes) {
        return left_arrival_minutes - right_arrival_minutes;
    }

    return left_process->process_id - right_process->process_id;
}

/*
 * 就绪集合里的选择规则：
 * 先比执行时间，再比到达时间，最后比 process_id。
 */
static int compare_runtime_then_arrival_then_id(const void *lhs, const void *rhs) {
    const process_node *left_process = *(const process_node *const *)lhs;
    const process_node *right_process = *(const process_node *const *)rhs;
    int left_arrival_minutes = sched_time_to_minutes(left_process->arrival_time);
    int right_arrival_minutes = sched_time_to_minutes(right_process->arrival_time);

    if (left_process->cpu_burst_minutes != right_process->cpu_burst_minutes) {
        return left_process->cpu_burst_minutes - right_process->cpu_burst_minutes;
    }

    if (left_arrival_minutes != right_arrival_minutes) {
        return left_arrival_minutes - right_arrival_minutes;
    }

    return left_process->process_id - right_process->process_id;
}

static void print_input_list(const process_queue *proc_queue)
{
    process_node *current_process = NULL;

    printf("id号  名字  到达时间  执行时间\n");
    for (current_process = proc_queue->head; current_process != NULL;
         current_process = current_process->next) {
        printf("%-5d %-5s %02d:%02d     %-3d\n", current_process->process_id,
               current_process->process_name, current_process->arrival_time.hour,
               current_process->arrival_time.minute,
               current_process->cpu_burst_minutes);
    }
}

static void print_result_header(void)
{
    printf("模拟短进程优先调度过程输出结果\n");
    printf("id号  名字  到达时间  执行时间(分钟)  开始时间  完成时间  周转时间(分钟)  带权周转系数\n");
}

static void print_result_row(const process_node *proc) {
    printf("%-5d %-5s %02d:%02d     %-12d %02d:%02d     %02d:%02d     %-14d %.2f\n",
           proc->process_id, proc->process_name, proc->arrival_time.hour, proc->arrival_time.minute,
           proc->cpu_burst_minutes, proc->start_time.hour, proc->start_time.minute,
           proc->finish_time.hour, proc->finish_time.minute, proc->turnaround_minutes,
           proc->weighted_turnaround);
}//一些格式化的函数，不谈

static void free_process_array(process_node_array *node_array) {
    free(node_array->nodes);
    node_array->nodes = NULL;
    node_array->count = 0;
    node_array->capacity = 0;
}


process_queue *queue_create(void)
{

    /*
     * TODO:
     * 1. 为队列结构分配内存。
     * 2. 将 head 和 tail 初始化为空。
     * 3. 处理内存分配失败的情况。
     */
    process_queue *proc_queue = (process_queue *)calloc(1, sizeof(process_queue));

    if (proc_queue == NULL) {
        fprintf(stderr, "队列初始化失败。\n");
        exit(EXIT_FAILURE);
    }

    return proc_queue;
}

void enqueue_process(process_queue *proc_queue, process_node *new_process)
{
    /*
     * TODO:
     * 1. 判空：队列指针、结点指针是否有效。
     * 2. 将新结点的 next 置空。
     * 3. 若队列为空，让 head 和 tail 同时指向新结点。
     * 4. 若队列非空，将新结点接到队尾，并更新 tail。
     */
    process_node *copy = NULL;

    if (proc_queue == NULL || new_process == NULL) {
        return;
    }

    copy = (process_node *)calloc(1, sizeof(process_node));
    if (copy == NULL) {
        fprintf(stderr, "入队结点分配失败。\n");
        exit(EXIT_FAILURE);
    }

    *copy = *new_process;
    copy->next = NULL;

    if (proc_queue->tail == NULL) {
        proc_queue->head = copy;
        proc_queue->tail = copy;
        return;
    }

    proc_queue->tail->next = copy;
    proc_queue->tail = copy;
}

void dequeue_process(process_queue *proc_queue)
{
    /*
     * TODO:
     * 1. 判空：队列为空时直接返回。
     * 2. 保存队首结点指针。
     * 3. head 后移。
     * 4. 如果删除后队列为空，要同步把 tail 置空。
     * 5. 释放原队首结点。
     */
    process_node *head_process = NULL;

    if (proc_queue == NULL || proc_queue->head == NULL) {
        return;
    }

    head_process = proc_queue->head;
    proc_queue->head = head_process->next;
    if (proc_queue->head == NULL) {
        proc_queue->tail = NULL;
    }

    free(head_process);
}

bool scan_sched_time(sched_time *out_time)
{
    return scanf("%d:%d", &out_time->hour, &out_time->minute) == 2;
}

void schedule_input(process_queue *proc_queue)
{
    /*
     * TODO:
     * 1. 读取进程数，并检查输入是否合法。
     * 2. 循环为每个进程分配结点空间。
     * 3. 读取 process_id、process_name、arrival_time、cpu_burst_minutes。
     * 4. 调用 enqueue_process() 将结点尾插入队。
     * 5. 输入完成后，输出输入进程表。
     *
     * 建议：
     * - 先独立完成一个结点的读取，再放进循环。
     * - 输入时间时复用 scan_sched_time()。
     */
    int process_count = 0;
    int index = 0;

    if (proc_queue == NULL) {
        return;
    }

    printf("请输入进程数：");
    fflush(stdout);
    if (scanf("%d", &process_count) != 1 || process_count <= 0) {
        printf("进程数无效。\n");
        return;
    }

    for (index = 0; index < process_count; ++index) {
        process_node *new_process = create_process_node();

        if (scanf("%d %19s", &new_process->process_id, new_process->process_name) != 2 ||
            !scan_sched_time(&new_process->arrival_time) ||
            scanf("%d", &new_process->cpu_burst_minutes) != 1) {
            fprintf(stderr, "进程输入格式错误。\n");
            free(new_process);
            exit(EXIT_FAILURE);
        }

        enqueue_process(proc_queue, new_process);
        free(new_process);
    }

    print_input_list(proc_queue);
}

void sort_by_arrival_time(process_queue *proc_queue)
{
    int node_count = 0;
    int index = 0;
    process_node_array node_array = {0};
    process_node *current_process = NULL;

    if (proc_queue == NULL || proc_queue->head == NULL) {
        return;
    }

    node_count = queue_length(proc_queue);
    node_array.nodes = (process_node **)calloc((size_t)node_count, sizeof(process_node *));
    if (node_array.nodes == NULL) {
        fprintf(stderr, "排序缓存分配失败。\n");
        exit(EXIT_FAILURE);
    }

    node_array.count = node_count;
    node_array.capacity = node_count;

    for (current_process = proc_queue->head, index = 0; current_process != NULL;
         current_process = current_process->next, ++index) {
        node_array.nodes[index] = current_process;
    }

    qsort(node_array.nodes, (size_t)node_array.count, sizeof(process_node *),
          compare_arrival_then_id);

    proc_queue->head = node_array.nodes[0];
    for (index = 0; index < node_array.count - 1; ++index) {
        node_array.nodes[index]->next = node_array.nodes[index + 1];
    }
    node_array.nodes[node_array.count - 1]->next = NULL;
    proc_queue->tail = node_array.nodes[node_array.count - 1];

    free_process_array(&node_array);
}

void run_sjf_schedule(process_queue *proc_queue)
/*
 * TODO:
 * 1. 先调用 sort_by_arrival_time()，保证作业队列按到达时间有序。
 * 2. 维护“当前时刻”和“就绪队列”。
 * 3. 每次从已经到达的进程中挑选执行时间最短者运行。
 * 4. 计算开始时间、完成时间、周转时间和带权周转系数。
 * 5. 输出每个进程结果，并统计系统平均周转时间与平均带权周转系数。
 */
{
    int total_processes = 0;
    int finished_processes = 0;
    int arrival_cursor = 0;
    int current_time = 0;
    double total_turnaround_time = 0.0;
    double total_weighted_turnaround = 0.0;
    process_node_array all_processes = {0};
    process_node_array ready_processes = {0};
    process_node *current_process = NULL;

    if (proc_queue == NULL || proc_queue->head == NULL) {
        printf("没有可调度的进程。\n");
        return;
    }

    sort_by_arrival_time(proc_queue);
    total_processes = queue_length(proc_queue);

    for (current_process = proc_queue->head; current_process != NULL;
         current_process = current_process->next) {
        append_process(&all_processes, current_process);
    }

    current_time = sched_time_to_minutes(all_processes.nodes[0]->arrival_time);

    print_result_header();
    while (finished_processes < total_processes) {
        while (arrival_cursor < total_processes &&
               sched_time_to_minutes(all_processes.nodes[arrival_cursor]->arrival_time) <=
                   current_time) {
            append_process(&ready_processes, all_processes.nodes[arrival_cursor]);
            arrival_cursor++;
        }

        if (ready_processes.count == 0) {
            current_time = sched_time_to_minutes(all_processes.nodes[arrival_cursor]->arrival_time);
            continue;
        }

        qsort(ready_processes.nodes, (size_t)ready_processes.count, sizeof(process_node *),
              compare_runtime_then_arrival_then_id);

        {
            process_node *selected_process = ready_processes.nodes[0];
            int finish_minutes = 0;
            int index = 0;

            selected_process->start_time = minutes_to_sched_time(current_time);
            finish_minutes = current_time + selected_process->cpu_burst_minutes;
            selected_process->finish_time = minutes_to_sched_time(finish_minutes);
            selected_process->turnaround_minutes =
                finish_minutes - sched_time_to_minutes(selected_process->arrival_time);
            selected_process->weighted_turnaround = (double)selected_process->turnaround_minutes /
                                                    (double)selected_process->cpu_burst_minutes;

            print_result_row(selected_process);

            total_turnaround_time += selected_process->turnaround_minutes;
            total_weighted_turnaround += selected_process->weighted_turnaround;
            current_time = finish_minutes;
            finished_processes++;

            for (index = 1; index < ready_processes.count; ++index) {
                ready_processes.nodes[index - 1] = ready_processes.nodes[index];
            }
            ready_processes.count--;
        }
    }

    printf("\n系统平均周转时间为：%.2f\n", total_turnaround_time / (double)total_processes);
    printf("系统平均带权周转系数为：%.2f\n", total_weighted_turnaround / (double)total_processes);

    free_process_array(&all_processes);
    free_process_array(&ready_processes);
}

void queue_destroy(process_queue *proc_queue)
{
    /*
     * 这里暂时保留释放逻辑，避免 starter 在多轮运行后出现明显内存泄漏。
     * 释放不是本实验的核心学习目标，因此不再额外抽成 TODO。
     */
    if (proc_queue == NULL) {
        return;
    }

    while (proc_queue->head != NULL) {
        dequeue_process(proc_queue);
    }
    free(proc_queue);
}




//数学工具类
int sched_time_to_minutes(sched_time time_value)
{
    return time_value.hour * 60 + time_value.minute;
}

sched_time minutes_to_sched_time(int total_minutes)
{
    sched_time converted_time;

    if (total_minutes < 0) {
        total_minutes = 0;
    }

    converted_time.hour = total_minutes / 60;
    converted_time.minute = total_minutes % 60;
    return converted_time;
}

int compare_sched_time(sched_time left_time, sched_time right_time)
{
    return sched_time_to_minutes(left_time) - sched_time_to_minutes(right_time);
}
