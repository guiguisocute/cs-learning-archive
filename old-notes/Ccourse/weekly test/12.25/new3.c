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
    node* newn = (node*)malloc(sizeof(node));
    newn->data = value;
    newn->next = NULL;
    return newn;
}

nodelist createnodelist_tailmove(int length){
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

void printnode(nodelist list){
    node* p = list.head;
    while(p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void headinsert(){

}

void midinsert(){

}

void tailinsert(){

}

void headdel(){

}

void middel(){

}

void taildel(){

}


int main(){
    nodelist a = createnodelist_headmove(10);
    // nodelist a = createnodelist_tailmove(10);
    printnode(a);
    return 0;

}