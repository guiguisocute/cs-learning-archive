#ifndef SCHEDULER_API_H
#define SCHEDULER_API_H

#define N 1010
#define MAX_CYLINDER 199

extern int length;
extern int sequence[N];
extern int result[N];
extern int now;

void FCFS(void);
void SSTF(void);
void Elevator(void);
void Oneway_scan(void);
void Twoway_scan(void);

#endif
