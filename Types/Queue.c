#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Queue.h"

typedef struct Node_rec Node;
typedef struct Queue_rec queue;

Queue * queueCreate()
{
	Queue * queue = malloc(sizeof(Queue));
	if (queue == NULL)
		return EXIT_FAILURE;
	queue->first = NULL;
	queue->last = NULL;
	queue->counter = 0;
	return queue;
}

void queueDestroy(Queue * queue)
{
	Node * pos = queue->first;
	while (pos != NULL)
	{
		Node * temp = pos;
		pos = pos->next;
		free(temp);
	}
	free(queue);
}

int queuePush(Queue * queue, void * value)
{
	Node * newNode = malloc(sizeof(Node));
	if (newNode == NULL)
		return EXIT_FAILURE;
	newNode->value = value;
	newNode->next = NULL;
	queue->first;
	if (queue->counter == 0)
	{
		queue->first = newNode;
		queue->last = newNode;
	}
	else
	{
		queue->last->next = newNode;
		queue->last = newNode;
	}
	queue->counter++;
	return EXIT_SUCCESS;
}

int queuePop(Queue * queue)
{
	Node * firstNode = queue->first;
	
	queue->first = firstNode->next;
	queue->counter--;
	int value = (int)firstNode->value;
	
	free(firstNode);
	return value;
}

int queueTop(Queue * queue)
{
	Node * firstNode = queue->first;
	return (int)firstNode->value;
}

int queueGetLength(Queue * queue)
{
	return queue->counter;
}