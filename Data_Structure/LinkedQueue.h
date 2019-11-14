#pragma once
#include"Node.h"
#include"..\Enemies\Enemy.h"
class LinkedQueue
{
	Node* backPtr;
	Node* frontPtr;
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& aQueue); // copy constructor
	bool isEmpty() const; // check if the Queue is empty or not
	bool enqueue(Enemy* newEntry); // add new element to the Queue
	bool dequeue(); // remove the first element in the Queue
	Enemy* peekFront(); // returns the value that the frontPtr points to
	Node* getFront()const; // return the frontPtr
	~LinkedQueue();
};

