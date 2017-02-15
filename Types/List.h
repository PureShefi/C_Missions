#pragma once
typedef struct Node_rec Node;
typedef struct List_rec List;

/* struct that will demonstrate the list */
struct List_rec
{
	Node * first;
	Node * last;
	int counter;
	int sum;
};
struct Node_rec;

/* create a new list */
List * listCreate();

/* destroy current list */
void listDestroy(List * list);

/* add new item */
int listAdd(List * list, void * value);

/* remove current item */
void listRemove(List * list, Node * toRemove);

/* get list length */
int listGetLength(List * list);

/* gets first item */
Node * listGetFirst(List * list);

/* gets last item */
Node * listGetLast(List * list);

/* gets all items average */
float  listGetAverage(List * list);
