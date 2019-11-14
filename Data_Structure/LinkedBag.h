#pragma once
#include"Node.h"
#include "..\Enemies\Enemy.h"
#include<vector>
class LinkedBag
{
	Node * headPtr; // Pointer to first node
	int itemCount; // Current count of bag items
				   
	Node* getPointerTo( Enemy* target) const; // Returns either a pointer to the node containing a given entry
												   // or the null pointer if the entry is not in the bag.
public:
	LinkedBag();
	LinkedBag(const LinkedBag & aBag); // Copy constructor
	int getCurrentSize() const; // return the size of the Bag
	bool isEmpty() const; // check if bag is empty or not
	bool add( Enemy* newEntry); // add new element to the bag 
	bool remove( Enemy* anEntry); // remove element from the bag and check if it is empty or not
	void clear(); // remove all elements of the bag
	bool contains( Enemy* anEntry) const; // check if the bag contains this element or not
	int getFrequencyOf( Enemy*  anEntry) const; // get the frequency (no of times the an element appeared in the bag)
	vector<Enemy*> toVector() const; 
	Enemy* GetEnemyFromList(int) const; // return enemy from the activelist
	~LinkedBag();
};

