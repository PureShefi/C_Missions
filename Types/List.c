#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Node.h"
#include "List.h"

List * listCreate() {
	List * list = malloc(sizeof(List));
	if (list == NULL)
		return EXIT_FAILURE;
	(*list).first = NULL;
	(*list).last = NULL;
	(*list).counter = 0;
	(*list).sum = 0;
	return list;
}

void listDestroy(List * list)
{
	Node * current = list->last;
	Node * temp;
	while (current != list->first)
	{
		temp = current;
		current = (*current).previous;
		free(temp);
	}
	free(current);
	free(list);
}

int listAdd(List * list, void * value) {
	Node * newNode = malloc(sizeof(Node));
	if (newNode == NULL)
		return EXIT_FAILURE;
	(*newNode).value = value;
	(*newNode).previous = (*list).last;
	(*newNode).next = NULL;
	if ((*list).counter == 0)
	{
		(*list).first = newNode;
		(*list).last = newNode;
	}
	else
	{
		(*(*list).last).next = newNode;
		(*list).last = newNode;
	}
	(*list).counter++;
	(*list).sum += (int)value;
	return EXIT_SUCCESS;
}

void listRemove(List * list, Node * toRemove) {
	if (toRemove == NULL)
		return EXIT_FAILURE;
	if (toRemove == list->first)
	{
		if (toRemove->next != NULL)
			list->first = toRemove->next;
		else
			list->first = NULL;
	}
	if (toRemove == list->last)
	{
		if (toRemove->previous != NULL)
			list->last = toRemove->previous;
		else
			list->last = NULL;
	}
	if(toRemove->previous != NULL)
		toRemove->previous->next = toRemove->next;
	if (toRemove->next != NULL)
		toRemove->next->previous = toRemove->previous;
	list->counter--;
	list->sum -= (int)(toRemove->value);
	free(toRemove);
	return EXIT_SUCCESS;
}

int listGetLength(List * list)
{
	return (*list).counter;
}

Node * listGetFirst(List * list)
{
	return (*list).first;
}

Node * listGetLast(List * list)
{
	return (*list).last;
}

float listGetAverage(List * list)
{
	return (float)list->sum / list->counter;
}