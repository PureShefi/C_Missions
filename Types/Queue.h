#pragma once
typedef struct Node_rec Node;
typedef struct Queue_rec Queue;

/* struct that will demonstrate the list */
struct Queue_rec
{
	Node * first;
	Node * last;
	int counter;
};
struct Node_rec;

/* create a new list */
Queue * queueCreate();

/* destroy current list */
void queueDestroy(Queue * queue);

/* pushes value to back of queue */
int queuePush(Queue * queue, void * value);

/* removes first item of queue */
int queuePop(Queue * queue);

/* returns first item of queue with*/
int queueTop(Queue * queue);

/* returns queue length */
int queueGetLength(Queue * queue);