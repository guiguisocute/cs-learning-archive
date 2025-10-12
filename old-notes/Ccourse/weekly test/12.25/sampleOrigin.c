#include <iostream>
#include "malloc.h"

typedef struct Node{
	int data;
	Node* pre;
	Node* next;
}Node;
typedef struct NodeList{
	Node* head;
	Node* tail;
}NodeList;
Node* createNode(int i){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = i;
	newNode->next = NULL;
	return newNode;
}
NodeList createNodeList(int length){
	Node* head = NULL;
	Node* tail = NULL;
	for(int i=0;i<length;i++){
		Node* newNode = createNode(i);
//		if(head == NULL){
//			head = tail = newNode;
//		}
//		else{
//			newNode->next = head;
//			head = newNode;
//		}
		if(tail == NULL){
			head = tail = newNode;
		}
		else{
			tail->next = newNode;
			tail = tail->next;
		}
	}
	return {head, tail};
}
void printNodeList(NodeList list){
	Node* p = list.head;
	while(p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n"); 
}

void headInsert(NodeList* list, int newValue){
	Node* newNode = createNode(newValue);
	newNode->next = list->head;
	list->head = newNode;
}
void midInsert(NodeList list, int value, int newValue){
	Node* newNode = createNode(newValue);
	Node* p = list.head;
	while(p != NULL && p->data != value){
		p = p->next;
	}
	if(p!=NULL){
		newNode->next = p->next;
		p->next = newNode;
	}
	else{
		printf("no"); 
	}
}
void tailInsert(NodeList* list, int value){
	Node* newNode = createNode(value);
	list->tail->next = newNode;
	list->tail=newNode;
}

void headDel(NodeList* list){
	Node* p = list->head;
	list->head = list->head->next;
	free(p);	
}
void midDel(NodeList list, int value){
	Node* p = list.head;
	Node* q = NULL;
	while(p != NULL && p->data != value){
		q = p;
		p = p->next;
	}
	if(p!=NULL){
		q->next = p->next;
		free(p);
	}
	else{
		printf("no"); 
	}
}
void tailDel(NodeList list, int value){
	Node* p = list.head;
	Node* q = NULL;
	while(p != NULL && p->data != value){
		q = p;
		p = p->next;
	}
	if(p!=NULL){
		q->next = NULL;
		list.tail = q;
		free(p);
	}
	else{
		printf("no"); 
	}
}
int main(int argc, char** argv) {
	NodeList list = createNodeList(10);
	printNodeList(list);

//	headInsert(&list,10); 
//	midInsert(list,2,10);
//	tailInsert(&list, 10);

//	headDel(&list);
//	midDel(list,2);
//	tailDel(list,9);

	printNodeList(list);
	return 0;
}