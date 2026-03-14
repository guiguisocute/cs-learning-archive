#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

typedef struct {
    ProcessNode *front;
    ProcessNode *rear;
} ProcessQueue;

#endif
