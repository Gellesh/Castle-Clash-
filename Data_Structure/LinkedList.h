#pragma once
#include"Node.h"
#include "..\Enemies\Enemy.h"
class LinkedList
{
	Node*Headptr;
	int itemcount;
	Node*getNodeAt(int postion)const;

public:
	LinkedList();
	LinkedList(const LinkedList& aList); // copy constructor
	bool IsEmpty()const; // check if the List is Empty or not
	int getLength() const; // get the length of the list
	bool insert(int newPosition,Enemy* newEntry); // insert new element given a specific index
	void append(Enemy*);// add new element
	bool remove(int position); // remove element given  specific index
	void clear(); // delete all the elements
	Enemy* getEntry(int position)const; // return an element given its index
	void SetEntry(int position,Enemy* newEntry); // assign a value to one of the list's element given its index
	Node* getHead()const; // return the head of the list
	~LinkedList();
};

