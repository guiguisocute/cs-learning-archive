#ifndef PAGING_LAB_H
#define PAGING_LAB_H

#include <stddef.h>

#define MAX 128
#define PAGE_TABLE_COLS 4
#define JOB_NAME_LEN 10

extern int sc[MAX][MAX];
extern int MemorySize;
extern int WordLength;
extern int WordNum;
extern int BlockSize;
extern int BlockNum;
extern int UsingBolckNum;
extern int AvailableBlockNum;

typedef struct link_node {
    char name[JOB_NAME_LEN];
    int size[MAX][MAX];
    int page_count;
    int job_size;
    struct link_node *next;
} node;

int OperationChoice(void);
void print(void);
node *allocate(node *head);
node *recycle(node *head);
void initMemory(void);
void Apply(void);

#endif
