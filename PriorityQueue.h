#pragma once
#include "PriorityNode.h"
using namespace std;
template <typename T>
class PriorityQueue
{
private:
	PriorityNode<T>* frontPtr;
	PriorityNode<T>* backPtr;

	int count;
public:
	int getCount() const//return the count of the list
	{
		return count;
	}
	
	PriorityQueue()//constructor
	{
		frontPtr = nullptr;
		backPtr = nullptr;
		count = 0;
	}
	bool isEmpty() const//return true when it is empty
	{
		return !count;
	}

	bool enqueue(const T& newEntry, int pr)//to add new item to the queue with its priority
	{
		PriorityNode<T>* newPtr = new PriorityNode<T>(newEntry, pr);//adding a new node and give it the item and its priority

		if (isEmpty() || pr < frontPtr->getPriority())//check if the queue is empty or the priority of new node is greater than the first node 
		{
			newPtr->setNext(frontPtr);//set the next of the new node with the first node if empty it contains nullptr
			frontPtr = newPtr;//set the frontptr to the new node ,so the new node is the front node in the queue
			count++;
			return true;
		}
		//if the queue is not empty and the priority of the new node is less than the first node in the queue
		PriorityNode<T>* ptr = frontPtr;
		while (ptr->getNext() && ptr->getNext()->getPriority() <= pr)//move in the queue from front and after each node check if the priority of the next node is smaller than or equle the priority of the new node
			ptr = ptr->getNext();
		//if i reach the end of the queue ptr contains nullptr or found a node with greater priority than the new node
		newPtr->setNext(ptr->getNext());
		ptr->setNext(newPtr);//adding the new node
		count++;
		return true;
	}
	bool dequeue(T& frontEntry)//to the first node in the queue
	{
		if (isEmpty())
			return false;
		 
		PriorityNode<T>* nodeToDeletePtr = frontPtr; 
		frontEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;


		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;

	}
	void printpq()
	{
		if (!frontPtr)//is empty
			return;
		PriorityNode<T>* p = frontPtr;
		while (p) {
			std::cout << p->getItem();
			p = p->getNext();
		}

	}

	void SetThePriority(int x)
	{
		frontPtr->setPriority(x);
	}


	int GetThePriority() // gets the priority of the first element in the queue
	{
		if (!frontPtr)//is empty
			return 0;
		else
			return frontPtr->getPriority();

	}

	
	bool peek(T& frontEntry) const
	{
		if (isEmpty())
			return false;

		frontEntry = frontPtr->getItem();
		return true;

	}
};
