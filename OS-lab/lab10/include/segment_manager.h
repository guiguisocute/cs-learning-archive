#ifndef SEGMENT_MANAGER_H
#define SEGMENT_MANAGER_H

#include <stdbool.h>

#define FLAG_LEN 20
#define JOB_NAME_LEN 20
#define MAX_SEGMENTS 10

typedef struct memory_node
{
    int size;
    int address;
} memoryNode;

typedef struct link_node
{
    int id;
    int size;
    int address;
    char flag[FLAG_LEN];
    struct link_node *next;
} node;

typedef struct segment_node
{
    int segment_count;
    char job_name[JOB_NAME_LEN];
    int a[MAX_SEGMENTS][3];
    struct segment_node *next;
} segmentNode;

node *initMemory(void);
int operation(node *head);
void allocate(node *head);
void firstAllocation(node *head, int size, char c[10]);
void reorder(node *head);
void recycle(node *head);
void print(node *head);

void destroy_all(node *head);

#endif
