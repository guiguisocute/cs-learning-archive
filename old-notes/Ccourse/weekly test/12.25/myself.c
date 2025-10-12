#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct nodelist{
    node* head;
    node* tail;
}nodelist;

node* createNode(int value){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = value;
    newnode->next = NULL;

    return newnode;
}

nodelist createNodelist(int length){
    nodelist list;
    list.head = NULL;
    list.tail = NULL;

    for(int i = 0; i < length;i++){
        node* newnode = createNode(i);
        if(list.head == NULL){
            list.head = newnode;
            list.tail = newnode;
        }
        else{
            list.tail->next = newnode;
            list.tail = newnode;
        }
    }
    return list;
}

// nodelist createNodelist_headmove(int length){
//     nodelist list;
//     list.head = NULL;
//     list.tail = NULL;

//     for(int i = length - 1; i >= 0;i--){
//         node* newnode = createNode(i);
//         if(list.head == NULL){
//             list.head = newnode;
//             list.tail = newnode;
//         }
//         else{
//             newnode->next = list.head;
//             list.head = newnode;
//         }
//     }
//     return list;
// }

void printNodelist(const nodelist* list){
    node* p = list->head;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void headInsert(nodelist* list, int newv){
    node* newn = createNode(newv);
    newn->next = list->head;
    list->head = newn;
    if(list->tail == NULL){
        list->tail = newn;
    }
}

void midInsert(nodelist* list, int value,int newv){
    if(list->head == NULL){
        printf("猪鼻吧，空链表怎么插入？\n");
        return;
    }
    node* p = list->head;
    while(p->next != NULL && p->data != value){
        p = p->next;
    }
    if(p != NULL){
        node* newn = createNode(newv);
        newn->next = p->next;
        p->next = newn;
    }else{
        printf("猪鼻吧，给我个链表没有的值你插个毛啊\n");
        return;
    }
}

void tailInsert(nodelist* list, int newv){
    node* newn = createNode(newv);
    list->tail->next = newn;
    list->tail = newn;
    if(list->head == NULL){
        list->head = newn;
    }

}

void headDel(nodelist* list){
    if(list->head == NULL){
        printf("猪鼻吧，空列表删个毛\n");
        return;
    }
    node* p = list->head;
    list->head = p->next;
    if(list->head == NULL){
        list->tail = NULL;
    }
    free(p);
}

void middel(nodelist* list,int value){
    if(list->head == NULL){
        printf("猪鼻吧，空列表删个毛");
        return;
    }
    node* p = list->head;
    node* temp = NULL;
    if(p->data == value){
        headDel(list);
        return;
    }
    while(p != NULL && p->data != value){
        temp = p;
        p = p->next;
    }
    if(p != NULL){
        temp->next = p->next;
    }else{
        printf("猪鼻吧，都没有这个值删个毛\n");
    }
}

void taildel(nodelist* list){
    if(list->head == NULL){
        printf("猪鼻吧，空列表删个毛\n");
        return;
    }
    if(list->head == list->tail){
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    node* p = list->head;
    while(p->next != list->tail){
        p = p->next;
    }
    free(list->tail);
    p->next = NULL;
    list->tail = p;

}


int main(){
    nodelist a = createNodelist(10);
    printNodelist(&a);
    headInsert(&a,100);
    midInsert(&a,2,200);
    tailInsert(&a,300);
    printNodelist(&a);
    headDel(&a);
    middel(&a,5);
    taildel(&a);
    printNodelist(&a);

    return 0;
}