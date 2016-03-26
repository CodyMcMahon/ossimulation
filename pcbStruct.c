#include <stdio.h>
#include <stdlib.h>

#include "MainFile.h"


// ptr dummyFunction(ptr useless){
// 	struct timespec spec;
//   clock_gettime(CLOCK_REALTIME, &spec);
// 	long long unsigned int timeLocked = spec.tv_nsec + (spec.tv_sec * 1000000000);
// 	long long unsigned int temp;
// 	long *x = malloc(sizeof(long));
// 	*x = 0;
// 	while(++(*x)){
// 		FIXTHISLATER: while(*((int*) useless));
// 		BADPROGRAMMING: if(*((int*) useless)) goto FIXTHISLATER;
// 		clock_gettime(CLOCK_REALTIME, &spec);
// 		temp = (spec.tv_nsec + (spec.tv_sec * 1000000000));
// 		if(temp - timeLocked >= DUMMY_FUNCTION_THING_BIGGER_IS_SLOWER){
// 			timeLocked = spec.tv_nsec + (spec.tv_sec * 1000000000);
// 			printf("-%ld",(*x));
// 		}
// 		else
// 			goto BADPROGRAMMING;
// 	}
// }
// pcbptr constuctorPCB(int x,int y){
//   pcbptr a = malloc(sizeof(struct pcb));
//   a->x = x;
//   a->y = y;
//   return a;
// }
//random numbers
pcbptr newPCB(){// makes some random PCB
  int count,o;
	pcbptr a = malloc(sizeof(struct pcb));
  a->cyclesRan = 0;//quantum count
	a->ID = ++pcb_counter_num;
	a->io_or_mutex = rand() % 2;
	if(a->io_or_mutex){
		o=SIZE_IOQUEUE;
	}
	else{
		o=SIZE_MUTEXQUEUE;
	}
	for(count = 0; count < o;count++){
		a->request[count] = (rand() % 350) + 1;
	}
	a->lifeTime = (rand() % 1000) - 950;
	
	a->age = 0;
	a->ioTime = 0;
	a->isStopped = 1;
	a->thread = malloc(sizeof(pthread_t));
	// pthread_create(a->thread,NULL,dummyFunction, &a->isStopped);
  return a;
	
}

pcbptr newTempPCB(){// makes some random PCB that will expire
  int count,o;
	pcbptr a = malloc(sizeof(struct pcb));
  a->cyclesRan = 0;//quantum count
	a->ID = ++pcb_counter_num;
	a->io_or_mutex = rand() % 2;
	if(a->io_or_mutex){
		o=SIZE_IOQUEUE;
	}
	else{
		o=SIZE_MUTEXQUEUE;
	}
	for(count = 0; count < o;count++){
		a->request[count] = (rand() % 350) + 1;
	}
	a->lifeTime = rand() % 50 + 20;
	a->isStopped = 1;
	a->thread = malloc(sizeof(pthread_t));
	// pthread_create(a->thread,NULL,dummyFunction, &a->isStopped);
	a->ioTime = 0;
  return a;
	
}

//just frees the pcb nothing else
void destructorPCB(pcbptr a){
  free(a);
}
