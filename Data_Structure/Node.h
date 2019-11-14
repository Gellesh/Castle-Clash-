#pragma once
#include"..\Enemies\Enemy.h"
using namespace std;

class Node
{
	Enemy* item;
	Node*Nextptr;
public:
	Node();
	Node(Enemy* data);
	Node(Enemy* data, Node*nextptr);
	// setters for the item of the node and the node that it's next points to
	void setItem(Enemy*  newItem); 
	void setNext(Node* nextNodePtr);
	// getters for the item of the node and the node that it's next points to
	Enemy* getItem() const;
	Node* getNext() const;
	~Node();
};
