#include "Queue.h"

Queue::Queue()
{
	frontPtr = backPtr = NULL;
}

Queue::Queue(const Queue & aList)
{

	Node* origChainPtr = aList.getFront();
	if (origChainPtr == nullptr)
		frontPtr = nullptr; // Original bag is empty; so is copy
	else
	{
		// Copy first node
		frontPtr = new Node();
		frontPtr->setItem(origChainPtr->getItem());
		// Copy remaining nodes
		Node* newChainPtr = frontPtr; // Last-node pointer
		while (origChainPtr->getNext() != nullptr)
		{
			Enemy* nextItem = origChainPtr->getItem();
			// Create a new node containing the next item
			Node* newNodePtr = new Node(nextItem);
			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext(); // Advance pointer
													// Get next item from original chain
		} // end while
		newChainPtr->setNext(nullptr); // Flag end of new chain
		backPtr = newChainPtr;
	}

}

Node* Queue::getFront()const
{
	return frontPtr;
}

bool Queue::isEmpty() const
{
	return (frontPtr == nullptr);
}

bool Queue::enqueue(Enemy* newEntry)
{
	Node* newNodePtr = new Node(newEntry);
	Node* prev = NULL;
	Node* ptr = frontPtr;
	// Insert the new node
	if (isEmpty()) // if queue is empty frontPtr and backPtr will point the element
	{
		frontPtr = backPtr = newNodePtr;
		backPtr->setNext(NULL);
	}                                      // The queue was empty
	else
	{
			backPtr->setNext(newNodePtr); // The queue was not empty
			backPtr = newNodePtr; // New node is at bac
	}
	return true;
} // end enqueue


bool Queue::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
		// Queue is not empty; remove front
		Node* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr)
		{ // Special case: one node in queue
			frontPtr = nullptr;
			backPtr = nullptr;
		}
		else
			frontPtr = frontPtr->getNext();
		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		result = true;
	} // end if
	return result;
} // end dequeue

Enemy* Queue::peekFront()
{
	if (!isEmpty())
		return frontPtr->getItem();
}




Queue::~Queue()
{
}
