#pragma once
typedef struct Node_rec Node;

/* struct that will demonstrate the Node */
struct Node_rec
{
	void * value;
	Node * next;
	Node * previous;
};

/* gets next item */
Node * nodeGetNext(Node * node);

/* gets previous item */
Node * nodeGetPrevious(Node * node);

/* returns current item value */
void * nodeGetValue(Node * node);
