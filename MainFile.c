/* MainFile.c
 * Cody McMahon
 * Matthew Cles
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MainFile.h"

int main(){

	srand (time(NULL));
	initiateVariables();
	loadInitialPCBs();
	// startTimer();
	runSimulation();
}
//the program starts running
void runSimulation(){
	pcbptr mypcb;
	long iterations = 0;
	timer =  0;
	for(iterations = 1; iterations < TOTAL_ITERATIONS_UNTIL_SIMULATION_ENDS + 1; iterations++){
		isRunning = 1;
		checkIOQueues();
		checkForNewPCBs();
		mypcb = getPCB(iterations);
		
		if (checkMutexes(mypcb))
			continue;
		if (checkAge(mypcb))
			continue;
			
		if (checkNewISRorTRAP(mypcb))
			continue;
			timer = 1;
			// mypcb->isStopped = 0;
			// while(timer);
			// mypcb->isStopped = 1;
		putPCBback(mypcb);
	}
	// pthread_join(timerInteruptER, NULL);
	isRunning = 0;
}

// void startTimer(){
// 	pthread_t *thread = malloc(sizeof(pthread_t));
// 	pthread_create(thread,NULL,timerInteruptER, malloc(1));
	
// }
//returns pcb to the queue
void putPCBback(pcbptr mypcb){
	printf("\n");
	enqueue(pQueue,mypcb);
}
//checks if it is a mutex or io request
int checkNewISRorTRAP(pcbptr mypcb){
	int i,o;
	if(mypcb->io_or_mutex)
		o = SIZE_IOQUEUE;
	else
		o = SIZE_MUTEXQUEUE;
	for(i = 0;i < o; i++){
		if(mypcb->age % mypcb->request[i] == 0){
			if(mypcb->io_or_mutex){
				enqueue(ioQueue[i], mypcb);
				printf(" doing io request on device #%d\n",i);
				mypcb->ioTime = REQUIRED_IOTIME;
				return 1;
			}
			else{
				if(mutexRequest(i, mypcb)){
					printf(" process is now the proud owner of mutex #%d\n",i);
					enqueue(pQueue,mypcb);
					return 1;
				}
				else{
					printf(" process blocked waiting for mutex #%d\n",i);
					return 1;
				}
			}
		}

	}
	return 0;
}
//checks how many times the pcb has ran
int checkAge(pcbptr mypcb){
	if(mypcb->lifeTime == 0){
		printf(" TERMINATED\n");
		destructorPCB(mypcb);
		return 1;
	}
	mypcb->lifeTime--;
	return 0;
}
//checks for if it owns a mutex currently
int checkMutexes(pcbptr mypcb){
	int i;
	for(i = 0; i < SIZE_MUTEXQUEUE; i++){
		if(mypcb == mutexFlags[i]){
			if((rand()%25)/20){
				mutexFlags[i] = dequeue(mQueue[i]);
				printf(" releasing mutex #%d", i);
				if (mutexFlags[i]){
					printf(" to process #%d\n",mutexFlags[i]->ID);
					enqueue(pQueue, mutexFlags[i]);
				}
				else{
					printf(" mutex is up for grabs\n");
				}
			}
			else{
				printf(" working on mutex #%d\n",i);
			}
			enqueue(pQueue,mypcb);
			return 1;
		}
	}
	return 0;
}
//gets a pcb from the queue
pcbptr getPCB(long iterations){
	pcbptr mypcb = (pcbptr) NULL;
	if (mypcb = dequeue(pQueue)){
		printf(" %8ld | [%2d]", iterations, mypcb->ID);
		mypcb->age++;
		
	}
	else{
		printf("\n\n NO PROCESS FOUND\n");
	}
	return mypcb;
}
//decides if it should add a new pcb or not
void checkForNewPCBs(){
	if((rand() % 1005) / 1000){//arbitrary random chance
			pcbptr a = newTempPCB();
			printf("IMPORTANT| NEW PROCESS CREATED ID = %d\n",a->ID);
			enqueue(pQueue,a);
	}
}
//checks the io queues
void checkIOQueues(){
	int i;
	for(i = 0;i < SIZE_IOQUEUE; i++){
		pcbptr temp = peak(ioQueue[i]);
		if (temp){
			temp->ioTime--;
			if (temp->ioTime){
				break;
			}
			printf("   EVENT | process #%d is done with io device #%d and has been returned to ready queue\n",temp->ID,i);
			enqueue(pQueue,temp);
			dequeue(ioQueue[i]);
		}
	}
}
//a pcb asks for a mutex
int mutexRequest(int x,pcbptr mypcb){
	if (mutexFlags[x]){
		enqueue(mQueue[x],mypcb);
		return 0;
	}
	else{
		mutexFlags[x] = mypcb;
		return 1;
	}
}
//loads the pcbs at the start into the queue
void loadInitialPCBs(){
	int count;
	for(count = 0; count < INITIAL_PCB_AMOUNT; count++){
		enqueue(pQueue, newPCB());
	}
}
//initialized global variables
void initiateVariables(){
	pQueue = constructorQueue();
	ioQueue = constructorQueueArr(SIZE_IOQUEUE);
	mQueue = constructorQueueArr(SIZE_MUTEXQUEUE);
	mutexFlags = calloc(sizeof(pcbptr),SIZE_MUTEXQUEUE);
}

