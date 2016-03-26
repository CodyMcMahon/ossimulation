#include <pthread.h>
static int pcb_counter_num = 0;
//structure for a process control block
typedef struct pcb{
	int cyclesRan;//quantum count
	int ID;
	long lifeTime;
	int request[4];
	int io_or_mutex;
	int age;
	int ioTime;
	int isStopped;
	pthread_t *thread;
} *pcbptr;
//makes a new pcb
pcbptr newPCB();
// pcbptr constuctorPCB(int x,int y);
void destructorPCB(pcbptr);
//makes a new pcb that will soon be seleted
pcbptr newTempPCB();

// ptr dummyFunction(ptr);


