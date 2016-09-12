/*
	Author:			Luke Musto
	Modifications:	Gregory Hughes
	Date:			04/15/2015
	Purpose:		Specification file for CLLQueueClass. Class contains one default constructor, a copy constructor, destructor and 7 public
					methods. Queue is dynamic and can contain as many elements as needed.
	Project:		CPU Simulation
	Filename:		CLLQueueClass.cpp
*/

///////////////////////////////////////////////////////////////Summary of Methods///////////////////////////////////////////////////////////////
//CLLQueueClass(); - default constructor initializes private members
//
//~CLLQueueClass(); - destructor - deallocates all memory after the class object is destroyed
//
//CLLQueueClass(const CLLQueueClass& orig); - copy constructor - creates a deep copy of the original object
//
//bool IsEmpty() const; - determines whether the queue is empty
//
//bool IsFull() const; - determines whether the queue is full
//
//void EnQ( ItemType newItem); - adds newItem to the rear(back) of the queue
//
//void DeQ(); - removes the item at the front of the queue
//
//ItemType Retrieve() const; - returns the copy of the item at the front of the queue
//	//Exceptions Thrown: RetrieveOnEmpty Exception
//
//void Clear(); - makes the queue empty
//
//void operator=( const CLLQueueClass&  orig); - performs deep copy of orig to applying queue object
//
//node* Allocate(); - llocates a new node 
//	//Exceptions Thrown: OutofMemoryException is thrown if allocate is unsuccessful


//Header file for implementation
#include "CLLQueueClass.h"

struct node
{
	ItemType data;
	node* next;
};

CLLQueueClass::CLLQueueClass()
//Purpose:	default constructor initializes private members
//Pre:		object has been instantiated
//Post:		object has been initialized
{
	tail = nullptr;
}

CLLQueueClass::~CLLQueueClass()
//Purpose:	destructor - deallocates all memory after the class 
//			object is destroyed
//Pre:		none
//Post:		arrays created in the free store are no longer there
{
	Clear();
}

CLLQueueClass::CLLQueueClass(const CLLQueueClass& orig)
//Purpose:	copy constructor - creates a deep copy of the original object
//Pre:		object has been initialized
//Pre:		a copy of the object has been created
{
	tail = nullptr;

	operator=(orig);
}

bool CLLQueueClass::IsEmpty() const
//Purpose:	determines whether the queue is empty
//Pre:		queue exists
//Post:		returns true if queue is empty and false otherwise
{
	return (tail == nullptr);
}

bool CLLQueueClass::IsFull() const
//Purpose:	determines whether the queue is full
//Pre:		queue exists
//Post:		returns true if queue is full and false otherwise
{
	return false;
}

void CLLQueueClass::EnQ(/*in*/ ItemType newItem)  //Item to be enqueued
//Purpose:	adds newItem to the rear(back) of the queue
//Pre:		queue is not full
//Post:		newItem is added to the rear of the queue
{
	// Handle the general case:
	// insertion of element into list with other elements
	if (!IsEmpty())
	{
		node* temp = tail->next;
		tail->next = Allocate();
		tail->next->data = newItem;
		tail = tail->next;
		tail->next = temp;
	}
	// Handle special case:
	// The list is empty and an element is to be enqueued
	else
	{
		node* temp = Allocate();
		temp->data = newItem;

		temp->next = temp;
		tail = temp;

	}
}

void CLLQueueClass::DeQ()
//Purpose:	removes the item at the front of the queue
//Pre:		queue is not empty
//Post:		the item at the front of the queue has been removed
{
	// Only deQ on an non-empty list
	if (!IsEmpty())
	{
		// get the item at the begining of the list
		node* temp = tail->next;

		// if there is only one item in the Queue
		if (tail == temp)
		{
			delete tail;

			tail = nullptr;
		}
		// if there is more than one item in the queue
		else
		{
			tail->next = temp->next;

			delete temp;
		}
		
	}
}

ItemType CLLQueueClass::Retrieve() const
//Purpose:	returns the copy of the item at the front of the queue
//Pre:		queue is not empty
//Post:		the copy of the item at the front is returned
//Exceptions Thrown: RetrieveOnEmpty Exception
{
	// only return the item at the top of the list if the list is not empty
	if (!IsEmpty())
		return tail->next->data;
	else
		throw RetreiveOnEmptyException();
}

void CLLQueueClass::Clear()
//Purpose:	makes the queue empty
//Pre:		queue exists
//Post:		queue has been cleared
{
	// empty list while the list contains elements
	while (!IsEmpty())
		DeQ();
}

void CLLQueueClass::operator = (/*in*/ const CLLQueueClass&  orig)
//Purpose:	performs deep copy of orig to applying queue object
//Pre:		orig exists
//Post:		contents of orig are copied into applying queue object
{
	Clear();

	// get original list
	node* tempO = orig.tail;

	// move to first position
	tempO = tempO->next;

	// traverse the queueadding each element in order
	while (tempO != orig.tail)
	{
		EnQ(tempO->data);
		tempO = tempO->next;
	}

	// Enqueue the last element into queue
	EnQ(tempO->data);
}

node* CLLQueueClass::Allocate()
//Purpose:	allocates a new node 
//Pre:		queue exists.
//Post:		a new node has been allocated and returned. 
//Exceptions Thrown: OutofMemoryException is thrown if allocate is unsuccessful
{
	// Attempt to allocate new memory
	try
	{
		node* ans = new node;
		ans->next = nullptr;
		return ans;
	}
	// If no memory is allocatable throw exception
	catch (std::bad_alloc)
	{
		throw OutOfMemoryException();
	}
}