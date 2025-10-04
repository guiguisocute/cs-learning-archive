#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生信息结构体
typedef struct Student {
    int id;                                 // 学号
    char name[20];               // 姓名
    int math;                           // 数学成绩
    int chinese;                        // 语文成绩
    int english;                        // 英语成绩
    int total;                              // 总分
    struct Student *next;       // 下一节点指针
} Node;
typedef Node * linklist;

// 创建新节点
linklist createNode(int id, char *name, int math, int chinese, int english)
{
    linklist newNode = (linklist)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->math = math;
    newNode->chinese = chinese;
    newNode->english = english;
    newNode->total = 0;
    newNode->next = NULL;
    return newNode;
}

// 插入节点到链表头部
void insertNode(linklist head, linklist newNode)
{
     if (newNode)
       {
            newNode->next=head->next;
            head->next=newNode;
       }
}


linklist inputData(char *f)
{
    int id, math, chinese, english;
    char name[20];
    // 创建头结点
    linklist  head = (linklist)malloc(sizeof(Node));
    head->next = NULL;

    // 从文件读取数据
    FILE *file = fopen(f, "r");
    if (!file) {
        printf("无法打开文件!\n");
        return head;
    }
    while (fscanf(file, "%d %s %d %d %d", &id, name, &math, &chinese, &english) == 5)
        {
                linklist  newNode = createNode(id, name, math, chinese, english);
                insertNode(head, newNode);
       }
   fclose(file);
   return head;
}
// 打印链表内容
void printList(linklist  head) {
    printf("学号\t姓名\t数学\t语文\t英语\t总分\n");
    printf("---------------------------------------------\n");
    linklist cur = head->next;
    while (cur != NULL) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\n",
               cur->id, cur->name, cur->math,
               cur->chinese, cur->english, cur->total);
        cur = cur->next;
    }
}

