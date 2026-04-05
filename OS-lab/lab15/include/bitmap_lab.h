#ifndef BITMAP_LAB_H
#define BITMAP_LAB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BITMAP_ROWS 4096
#define MAX_BITMAP_COLS 4096
#define MAX_JOB_BLOCKS 1000

typedef struct node {
    int size;
    int a[MAX_JOB_BLOCKS];
    int zihao[MAX_JOB_BLOCKS];
    int weihao[MAX_JOB_BLOCKS];
    int zhu[MAX_JOB_BLOCKS];
    int citou[MAX_JOB_BLOCKS];
    int shanqu[MAX_JOB_BLOCKS];
    char name[10];
    struct node *next;
} linklist;

extern linklist *work;

extern int disksize;
extern int word;
extern int blocksize;
extern int head;
extern int sector;
extern int cylinder;
extern int sum;
extern int available;
extern int map[MAX_BITMAP_ROWS][MAX_BITMAP_COLS];
extern int line;

void print(void);
void allocate(void);
void recycle(void);
void init(void);
int menu(void);

#endif
