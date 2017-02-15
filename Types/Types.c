#include <stdio.h>
#include "Node.h"
#include "List.h"
#include "Queue.h"

int main()
{
	Queue * queue = queueCreate();
	queuePush(queue, 5);
	queuePush(queue, 10);
	queueDestroy(queue);
    return 0;
}
