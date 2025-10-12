#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct nodelist{
    node* head;
    node* tail;
}nodelist;

node* createnode(int value){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data =value;
    newnode->next = NULL;

    return newnode;
}

nodelist cratenodelist_tailmove(int length){
    nodelist list;
    list.head = NULL;
    list.tail = NULL;
    
    for(int i = 0; i < length; i++){
        node* newn = createnode(i);
        if(list.head == NULL){
            list.head = newn;
            list.tail = newn;
        }else{
            list.tail->next = newn;
            list.tail = newn;
        }
    }
    return list;
}

nodelist createnodelist_headmove(int length){
    nodelist list;
    list.head = NULL;
    list.tail = NULL;
    
    for(int i = length - 1; i >= 0; i--){
        node* newn = createnode(i);
        if(list.head == NULL){
            list.head = newn;
            list.tail = newn;
        }else{
            newn->next = list.head;
            list.head = newn;
        }
    }
    return list;
}

void printnodelist(nodelist list){
    node* p = list.head;
    while(p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void headinsert(nodelist* list, int newvalue){
    node* newn = createnode(newvalue);
    newn->next = list->head;
    list->head = newn;
}

void midinsert(nodelist* list, int v,int newvalue){
    node* p = list->head;
    while(p->data != v && p->next != NULL){
        p = p->next;
    }
    if(p != NULL){
        node* newn = createnode(newvalue);
        newn->next = p->next;
        p->next = newn;
    }else{
        printf("no\n");
    }
    
}

void tailinsert(nodelist* list, int newvalue){
    node* newn = createnode(newvalue);
    list->tail->next = newn;
    list->tail = newn;
}

void headdel(nodelist* list){
    list->head = list->head->next;
    if(list->head == NULL){
        list->tail = NULL;
    }
}

void middel(nodelist* list, int v){
    node* p = list->head;
    node* q = NULL;
    if(p->data == v){
        headdel(list);
        return;
    }
    while(p->data != v && p->next != NULL){
        q = p;
        p = p->next;
    }
    if(p != NULL){
        q->next = p->next;
        free(p);
    }else{
        printf("no\n");
    }
}

void taildel(nodelist* list){
    if(list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    node* p = list->head;
    while(p->next != list->tail){
        p = p->next;
    }
    p->next = NULL;
    list->tail = p;
    

}

int main(){
    // nodelist a = cratenodelist_tailmove(10);
    nodelist a = createnodelist_headmove(10);
    printnodelist(a);
    headinsert(&a,100);
    midinsert(&a,2,200);
    tailinsert(&a,300);
    printnodelist(a);
    headdel(&a);
    middel(&a,5);
    taildel(&a);
    printnodelist(a);


    return 0;
}