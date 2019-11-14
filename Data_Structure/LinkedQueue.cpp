#include "LinkedQueue.h"

LinkedQueue::LinkedQueue()
{
	frontPtr = backPtr = NULL;
}

LinkedQueue::LinkedQueue(const LinkedQueue & aList)
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
		backPtr=newChainPtr;                                
	}

}

Node* LinkedQueue::getFront()const
{
	return frontPtr;
}

bool LinkedQueue::isEmpty() const
{
	return (frontPtr==nullptr);
}

bool LinkedQueue::enqueue(Enemy* newEntry)
{
	Node* newNodePtr = new Node(newEntry);
	Node* prev = NULL;
	Node* ptr = frontPtr;
	// Insert the new node
	if (isEmpty()) // if queue is empty frontPtr and backPtr will point the element
	{
		frontPtr=backPtr = newNodePtr;
	    backPtr->setNext(NULL);
	}                                      // The queue was empty
	else
	{
		bool IsInserted = false;
		while((ptr) && (!IsInserted))
		{
			if(ptr->getItem()->GetArrivalTime() > newEntry->GetArrivalTime()) 
			{
				if((backPtr == frontPtr) ||  (ptr->getItem()==peekFront())) // (if the backPtr == frontPtr) means that that Queue contains one element or the Queueu contains more than one element and the ptr's element == frontPtr's element
				{
					newNodePtr->setNext(frontPtr);
					frontPtr = newNodePtr;
					IsInserted = true;
					break;
				}
				if(prev)  //General case
				{
					newNodePtr->setNext(ptr);
					prev->setNext(newNodePtr);
					IsInserted=true;
				}
				
			}
				prev = ptr; // points to the old value (previous value) of the ptr
				ptr = ptr->getNext();
		}
		if(!IsInserted) // if the the newEntry's arrival time is greater than all the Queue's element
		{
			backPtr->setNext(newNodePtr); // The queue was not empty
			backPtr = newNodePtr; // New node is at back
		}

	}
	return true;
} // end enqueue


bool LinkedQueue::dequeue()
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

Enemy* LinkedQueue::peekFront()
{
	if (!isEmpty())
		return frontPtr->getItem();
}




LinkedQueue::~LinkedQueue()
{
}
