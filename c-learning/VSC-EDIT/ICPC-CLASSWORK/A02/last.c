#include <stdio.h>

#define MAX_N 100005
#define MAX_ADD 100000

typedef struct Node {
    int addr;
    int data;
    int next;
} Node;

Node nodes[MAX_N], result[MAX_N];
Node neg[MAX_N], zero_to_k[MAX_N], greater[MAX_N];
int map[MAX_ADD];


void readInput(int *head, int *n, int *k) {
    scanf("%d %d %d", head, n, k);
    
    for (int i = 0; i < *n; i++) {
        int addr, data, next;
        scanf("%d %d %d", &addr, &data, &next);
        nodes[i].addr = addr;
        nodes[i].data = data;
        nodes[i].next = next;
        map[addr] = i;
    }
}


int rearrangeList(int head, int k) {
    int neg_cnt = 0, mid_cnt = 0, great_cnt = 0;
    
    int curr = head;
    while (curr != -1) {
        Node* node = &nodes[map[curr]];
        if (node->data < 0) {
            neg[neg_cnt++] = *node;
        } else if (node->data <= k) {
            zero_to_k[mid_cnt++] = *node;
        } else {
            greater[great_cnt++] = *node;
        }
        curr = node->next;
    }
    
    int total = 0;
    for (int i = 0; i < neg_cnt; i++) {
        result[total++] = neg[i];
    }
    for (int i = 0; i < mid_cnt; i++) {
        result[total++] = zero_to_k[i];
    }
    for (int i = 0; i < great_cnt; i++) {
        result[total++] = greater[i];
    }
    
    for (int i = 0; i < total - 1; i++) {
        result[i].next = result[i + 1].addr;
    }
    if (total > 0) {
        result[total - 1].next = -1;
    }
    
    return total;
}

void printResult(int count) {
    for (int i = 0; i < count; i++) {
        printf("%05d %d ", result[i].addr, result[i].data);
        if (result[i].next == -1) {
            printf("-1\n");
        } else {
            printf("%05d\n", result[i].next);
        }
    }
}

int main() {
    int head, n, k;
    
    readInput(&head, &n, &k);
    int count = rearrangeList(head, k);
    printResult(count);
    
    return 0;
}