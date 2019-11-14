#include"Node.h"

Node::Node() :Nextptr(nullptr)
{
}

Node::Node(Enemy* data) : item(data), Nextptr(nullptr)
{

}

Node::Node(Enemy* data, Node * nextptr) : item(data), Nextptr(nextptr)
{
}

void Node::setItem(Enemy* newItem)
{
	item = newItem;
} // end setItem

void Node::setNext(Node* nextNodePtr)
{
	Nextptr = nextNodePtr;
} // end setNext

Enemy* Node::getItem() const
{
	return item;
} // end getItem

Node* Node::getNext() const
{
	return Nextptr;
} // end getNext

Node::~Node()
{
}
