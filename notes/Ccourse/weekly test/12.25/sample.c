#include <stdio.h>
#include <stdlib.h>  // malloc, free 等都在这里声明

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct NodeList {
    Node* head;
    Node* tail;
} NodeList;

// 创建节点
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// 创建长度为 length 的链表，节点值从 0 ~ length-1
NodeList createNodeList(int length) {
    NodeList list;
    list.head = NULL;
    list.tail = NULL;

    for(int i = 0; i < length; i++) {
        Node* newNode = createNode(i);
        if(list.head == NULL) {
            // 第一个节点既是头又是尾
            list.head = newNode;
            list.tail = newNode;
        } else {
            // 后续节点插到尾部
            list.tail->next = newNode;
            list.tail = newNode;
        }
    }
    return list;
}

// 打印整个链表
void printNodeList(const NodeList* list) {
    Node* p = list->head;
    while(p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 头插
void headInsert(NodeList* list, int newValue) {
    Node* newNode = createNode(newValue);
    newNode->next = list->head;
    list->head = newNode;
    // 如果链表原本是空的，尾指针也要更新
    if(list->tail == NULL) {
        list->tail = newNode;
    }
}

// 中间插：找到第一个值为 value 的节点，在其后面插入
void midInsert(NodeList* list, int value, int newValue) {
    if(list->head == NULL) {
        printf("链表为空，无法进行中间插入。\n");
        return;
    }
    // 找到值为 value 的节点
    Node* p = list->head;
    while(p != NULL && p->data != value) {
        p = p->next;
    }
    // 如果找到了这个节点
    if(p != NULL) {
        Node* newNode = createNode(newValue);
        newNode->next = p->next;
        p->next = newNode;
        // 如果插在尾巴后面，需要更新 tail
        if(p == list->tail) {
            list->tail = newNode;
        }
    } else {
        printf("未找到节点值=%d，无法插入。\n", value);
    }
}

// 尾插
void tailInsert(NodeList* list, int value) {
    Node* newNode = createNode(value);
    // 如果链表为空
    if(list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// 头删
void headDel(NodeList* list) {
    if(list->head == NULL) {
        printf("链表为空，无法头删。\n");
        return;
    }
    Node* p = list->head;
    list->head = p->next;
    // 如果删除的是唯一节点，需要更新 tail
    if(list->head == NULL) {
        list->tail = NULL;
    }
    free(p);
}

// 中间删：删除第一个值为 value 的节点
void midDel(NodeList* list, int value) {
    if(list->head == NULL) {
        printf("链表为空，无法中间删除。\n");
        return;
    }
    // 如果需要删的就是头节点
    if(list->head->data == value) {
        headDel(list);
        return;
    }
    Node* p = list->head;
    Node* q = NULL;
    while(p != NULL && p->data != value) {
        q = p;
        p = p->next;
    }
    // p 找到要删的节点
    if(p != NULL) {
        q->next = p->next;
        // 如果删的是尾节点，需要更新 tail
        if(p == list->tail) {
            list->tail = q;
        }
        free(p);
    } else {
        printf("未找到节点值=%d，无法删除。\n", value);
    }
}

// 尾删：删除最后一个节点
void tailDel(NodeList* list) {
    if(list->head == NULL) {
        printf("链表为空，无法尾删。\n");
        return;
    }
    // 如果只有一个节点
    if(list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    // 否则找到倒数第二个节点
    Node* p = list->head;
    while(p->next != list->tail) {
        p = p->next;
    }
    // 此时 p->next 即是 tail
    free(list->tail);
    p->next = NULL;
    list->tail = p;
}

int main() {
    // 先创建一个含 10 个节点(0~9)的链表
    NodeList list = createNodeList(10);
    printf("初始链表：\n");
    printNodeList(&list);

    // 演示头插、中间插、尾插
    headInsert(&list, 100);
    midInsert(&list, 2, 200);
    tailInsert(&list, 300);
    printf("\n插入后：\n");
    printNodeList(&list);

    // 演示头删、中间删、尾删
    headDel(&list);
    midDel(&list, 5);
    tailDel(&list);
    printf("\n删除后：\n");
    printNodeList(&list);

    return 0;
}
