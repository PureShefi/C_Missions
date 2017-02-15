typedef struct Node_rec Node;

extern struct Node_rec
{
	void * value;
	Node * next;
	Node * previous;
};

Node * nodeGetNext(Node * node)
{
	return (*node).next;
}

Node * nodeGetPrevious(Node * node)
{
	return (*node).previous;
}

 void * nodeGetValue(Node * node)
{
	return (*node).value;
}
