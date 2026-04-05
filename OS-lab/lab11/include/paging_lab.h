#ifndef PAGING_LAB_H
#define PAGING_LAB_H

#define MAX_PAGES 1010
#define MAX_NAME_LEN 64
#define MAX_FRAMES 64

typedef struct {
    int cnt;
    int val;
} Y;

void out(void);
void input(void);
void print(void);
void solve1(void);
void solve2(void);

#endif
