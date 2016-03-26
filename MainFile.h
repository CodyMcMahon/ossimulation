#include "FIFOqueue.h"
#include "pcbStruct.h"

//constants
#define SIZE_IOQUEUE 4
#define SIZE_MUTEXQUEUE 4
#define INITIAL_PCB_AMOUNT 9
#define REQUIRED_IOTIME 7
#define TOTAL_ITERATIONS_UNTIL_SIMULATION_ENDS 10000

#define WILLSLEEP 1 //bool
#define SLEEPLENGTH 1 //how long if sleep

static const long RUNTIME = 900000000;
static const long DUMMY_FUNCTION_THING_BIGGER_IS_SLOWER = 500000000;//50000000;//50000000;

typedef pcbptr* pcbptrArr;

//global variables
queue pQueue;
queueArr ioQueue;//use as array i.e. ioQueue[2]->enqueue()
queueArr mQueue;//use as array
pcbptrArr mutexFlags;//use as array
int timer;
int isRunning;


//initialized global variables
void initiateVariables();
//loads the pcbs at the start into the queue
void loadInitialPCBs();
//the program starts running
void runSimulation();
//a pcb asks for a mutex
int mutexRequest(int,pcbptr);
//a pcb asks to use an io device
void ioRequest(int);
//returns pcb to the queue
void putPCBback(pcbptr);
//checks if it is a mutex or io request
int checkNewISRorTRAP(pcbptr);
//checks how many times the pcb has ran
int checkAge(pcbptr);
//checks for if it owns a mutex currently
int checkMutexes(pcbptr);
//gets a pcb from the queue
pcbptr getPCB(long);
//decides if it should add a new pcb or not
void checkForNewPCBs();
//checks the io queues
void checkIOQueues();
//unused
void startTimer();
//unused
ptr timerInteruptER(ptr);