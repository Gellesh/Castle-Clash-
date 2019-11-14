#pragma once
#include"Data_Structure\Node.h"
#include"Enemies\Enemy.h"
class Queue
{
	Node* backPtr;
	Node* frontPtr;
public:
	Queue();
	Queue(const Queue& aQueue); // copy constructor
	bool isEmpty() const; // check if the Queue is empty or not
	bool enqueue(Enemy* newEntry); // add new element to the Queue
	bool dequeue(); // remove the first element in the Queue
	Enemy* peekFront(); // returns the value that the frontPtr points to
	Node* getFront()const; // return the frontPtr
	~Queue();
};

