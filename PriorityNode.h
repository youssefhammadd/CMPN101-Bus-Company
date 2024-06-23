#pragma once
#include"iostream"
template <typename T>
class PriorityNode
{
private:
	T  item;
	PriorityNode<T>* next;
	int priority;
public:

	PriorityNode(const  T& X, int k)//non-default constructor takes the item and its priority level
	{
		item = X;
		priority = k;
		next = nullptr;
	}

	void setPriority(int k)//setter to change the priority
	{
		priority = k;
	}
	int getPriority() const//getter for priority
	{
		return priority;
	}
	void setNext(PriorityNode<T>* j)//Takes the address of next PriorityNode and set it to the pointer of this node
	{
		next = j;
	}
	PriorityNode<T>* getNext() const//return the address of next node
	{
		return next;
	}
	void setItem(const T& a)//give item to the calling node
	{
		item = a;
	}
	T getItem() const//return the item of the calling node
	{
		return  item;
	}
};
