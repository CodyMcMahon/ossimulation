#include <stdio.h>
#include <stdlib.h>
#include "FIFOqueue.h"
//constructs a single node and returns a pointer to it
node constuctorNode(ptr a){
  node temp = malloc(sizeof(struct FIFOnode));
  temp->data = a;
  temp->next = (node) 0;
  return temp;
}
//constucrts an array of Queues and returns an array of pointers to each Queue
queueArr constructorQueueArr(int size){
	int count;
	queueArr temp = (queueArr) calloc(sizeof(struct FIFOqueue),size);
	for(count = 0; count <= size; count++){
		temp[count] = constructorQueue();
	}
	return temp;
}
//constructs a queue and returns a pointer to the queue
queue constructorQueue(){
	queue temp = (queue) malloc(sizeof(struct FIFOqueue));
	temp->head = constuctorNode((ptr) NULL);
	temp->tail = temp->head;
	return temp;
}
//simply frees the queue does not check for elements not used in this porgram
void destructorQueue(queue temp){
	free(temp);
}

//does not delete ptr
void destructorNode(node a){
  free(a);
} 
//adds a pointer of any kind to the queue
void enqueue(queue myQueue, ptr a){
	node temp = constuctorNode(a);
  myQueue->tail->next = temp;
  myQueue->tail = temp;
}
//looks at the head of the queue without removing
ptr peak(queue myQueue){
	if(myQueue->head!=myQueue->tail){
		return myQueue->head->next->data;
	}
	return (ptr) 0;
}
//removes the first element from the queue
ptr dequeue(queue myQueue){
	ptr temp = (ptr) 0;
	ptr destroythis = (ptr) 0;
	if(myQueue->head!=myQueue->tail){
	if (myQueue->tail->data){
		temp = myQueue->head->next->data;
		destroythis = myQueue->head->next;
		// if(myQueue->head->next == myQueue->tail){
		// 	myQueue->head = myQueue->tail;
		// }
		// else{
			if(myQueue->head->next != myQueue->tail)
				myQueue->head->next = myQueue->head->next->next;
		// }
			else{
				myQueue->tail=myQueue->head;
				// printf("TEST");
				
			}
		destructorNode(destroythis);
	}}
	return temp;
}