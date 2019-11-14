#include "LinkedBag.h"

Node * LinkedBag::getPointerTo( Enemy*  target) const
{
	Node*tmp=headPtr;
	for(int i=0; i<itemCount; i++)
	{
		if(tmp->getItem()==target)
			return tmp;
		tmp=tmp->getNext();
	}
	return NULL;
} // end getPointerTo

LinkedBag::LinkedBag()
{
	headPtr = NULL;
	itemCount = 0;
}

LinkedBag::LinkedBag(const LinkedBag & aBag)
{
	itemCount = aBag.itemCount;
	Node* origChainPtr = aBag.headPtr;
		if (origChainPtr == nullptr)
			headPtr = nullptr; // Original bag is empty; so is copy
		else
		{
			// Copy first node
			headPtr = new Node();
			headPtr->setItem(origChainPtr->getItem());
			// Copy remaining nodes
			Node* newChainPtr = headPtr; // Last-node pointer
			while (origChainPtr->getNext() != nullptr)
			{
				origChainPtr = origChainPtr->getNext(); // Advance pointer
														// Get next item from original chain
				Enemy* nextItem = origChainPtr->getItem();
				// Create a new node containing the next item
				Node* newNodePtr = new Node(nextItem);
				// Link new node to end of new chain
				newChainPtr->setNext(newNodePtr);
				// Advance pointer to new last node
				newChainPtr = newChainPtr->getNext();
			} // end while
			newChainPtr->setNext(nullptr); // Flag end of new chain
		} // end if
} // end copy constructo

int LinkedBag::getCurrentSize() const
{
	return itemCount;
}

bool LinkedBag::isEmpty() const
{
	return itemCount==0;
}

bool LinkedBag::add( Enemy*  newEntry)
{
	Node* newNodePtr = new Node();
	newNodePtr->setItem(newEntry);
	newNodePtr->setNext(headPtr); // New node points to chain
	headPtr = newNodePtr; // New node is now first node
	itemCount++;
	return true;
} 

bool LinkedBag::remove( Enemy * anEntry)
{
	Node* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if(canRemoveItem)
	{
		// Copy data from first node to located node
		entryNodePtr->setItem(headPtr->getItem());
		// Delete first node
		Node* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();
		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		itemCount--;
	} // end if
	return canRemoveItem;
} // end remove

void LinkedBag::clear()
{
	while (headPtr != nullptr)
	{
		Node* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();
		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
	} // end while
	  // headPtr is nullptr
	itemCount = 0;
}

bool LinkedBag::contains(Enemy* anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}

int LinkedBag::getFrequencyOf(Enemy * anEntry) const
{
	int frequency = 0;
	int counter = 0;
	Node* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (curPtr->getItem() == anEntry)
		{
			frequency++;
		} // end if
		counter++;
		curPtr = curPtr->getNext();
	} // end while
	return frequency;
} 

vector<Enemy*> LinkedBag::toVector() const
{
	vector<Enemy*> bagContents;
	Node* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	return bagContents;
} // end toVector

Enemy* LinkedBag::GetEnemyFromList(int k) const
{
	Node* curPtr = headPtr;
	for(int i = 0; i < k;i++)
	{
		curPtr = curPtr->getNext();
	}
	return (curPtr->getItem());
}

LinkedBag::~LinkedBag()
{
	clear();
}
