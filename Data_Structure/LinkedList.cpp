#include "LinkedList.h"

Node * LinkedList::getNodeAt(int position)const
{
	Node*curPtr = Headptr;
	for (int skip = 0; skip < position; skip++)
		curPtr = curPtr->getNext();
	return curPtr;
}

LinkedList::LinkedList() :Headptr(nullptr), itemcount(0)
{

}

LinkedList::LinkedList(const LinkedList & aList)
{
	itemcount = aList.itemcount;
	Node* origChainPtr = aList.getHead();
	if (origChainPtr == nullptr)
		Headptr = nullptr; // Original bag is empty; so is copy
	else
	{
		// Copy first node
		Headptr = new Node();
		Headptr->setItem(origChainPtr->getItem());
		// Copy remaining nodes
		Node* newChainPtr = Headptr; // Last-node pointer
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
	}

}

Node* LinkedList::getHead()const
{
	return Headptr;
}

bool LinkedList::IsEmpty() const
{
	return (itemcount == 0);
}

int LinkedList::getLength() const
{
	return itemcount;
}

bool LinkedList::insert(int newPosition, Enemy*  newEntry)
{
	if(newPosition<0  &&  newPosition>itemcount)
		return false;
	if(newPosition==0)
	{
		if(IsEmpty())
		{
			append(newEntry);
		    itemcount++;
			return true;
		}
		else
		{
		    Node*inserted=new Node(newEntry);
			inserted->setNext(Headptr);
			Headptr=inserted;
			itemcount++;
			return true;
		}
	}
	else
	{
		Node*inserted=new Node(newEntry);
		Node*tmp=Headptr;
		for(int i=0; i<newPosition; i++)
			tmp=tmp->getNext();

		inserted->setNext(tmp->getNext());
		tmp->setNext(inserted);
		itemcount++;
		return true;
	}
	
}

void LinkedList::append(Enemy* newEntery)
{
	Node*inserted=new Node (newEntery);
	if(IsEmpty())
	{
		Headptr=inserted;
	}
	else
	{
		Node*tmp=Headptr;
		while(tmp->getNext()!=NULL)
			tmp=tmp->getNext();
		tmp->setNext(inserted);
		inserted->setNext(NULL);
	}
	itemcount++;
}

bool LinkedList::remove(int position)
{
	bool ableToRemove = (position >= 0) && (position < itemcount);
	if (ableToRemove)
	{
		Node*curptr = nullptr;
		if (position == 0)
		{
			curptr = Headptr;
			Headptr = Headptr->getNext();
		}
		else
		{
			Node*prev = getNodeAt(position - 1);
			curptr = prev->getNext();
			prev->setNext(curptr->getNext());

		}
		curptr->setNext(nullptr);
		delete curptr;
		itemcount--;
	}
	return ableToRemove;
}

void LinkedList::clear()
{
	while (!IsEmpty())
	{
		remove(1);
	}
	Headptr = nullptr;
}

Enemy* LinkedList::getEntry(int position)const
{
	bool ableToGet = (position >= 0) && (position < itemcount);
	if (ableToGet)
	{
		Node* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
}

void LinkedList::SetEntry(int position,Enemy* newEntry)
{
	bool ableToSet = (position >= 0) && (position < itemcount);
	if (ableToSet)
	{
		Node*curPtr = getNodeAt(position);
		curPtr->setItem(newEntry);
	}
}

LinkedList::~LinkedList()
{
	clear();
}

