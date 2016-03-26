//takes in pointers of any kind
typedef void* ptr;

//node of the queue
typedef struct FIFOnode{
  ptr data;
  struct FIFOnode *next;
} *node;

//scruct used to keep track of nodes
typedef struct FIFOqueue{
	node head;
	node tail;
} *queue;

typedef queue* queueArr;

//constructs a queue and returns a pointer to the queue
queue constructorQueue();
//constucrts an array of Queues and returns an array of pointers to each Queue
queueArr constructorQueueArr(int);
//simply frees the queue does not check for elements not used in this porgram
void destructorQueue(queue);
//constructs a single node and returns a pointer to it
node constructorNode(ptr);
//does not delete ptr
void destructorNode(node);
node startup();
//adds a pointer of any kind to the queue
void enqueue(queue,ptr);
//removes the first element from the queue
ptr dequeue(queue);
//looks at the head of the queue without removing
ptr peak(queue);