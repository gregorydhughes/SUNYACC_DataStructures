/*
	Author:			Luke Musto
	Modifications:	Gregory Hughes
	Date:			04/15/2015
	Purpose:		Specification file for StaticQueueClass. Class contains one default constructor, and 7 public methods.
					Queue can contain 5 elements and is held in the named constant MAX_ELEMENTS.
	Project:		CPU Simulation
	Filename:		StaticQueueClass.cpp
*/

///////////////////////////////////////////////////////////////Summary of Methods///////////////////////////////////////////////////////////////
//CLLQueueClass(); - default constructor initializes private members
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


//Header file for implementation
#include "StaticQueueClass.h"


StaticQueueClass::StaticQueueClass()
//Purpose:	default constructor initializes private members
//Pre:		object has been instantiated
//Post:		object has been initialized
{
	front = 0;
	back = front + 1;
}

bool StaticQueueClass::IsEmpty() const
//Purpose:	determines whether the queue is empty
//Pre:		queue exists
//Post:		returns true if queue is empty and false otherwise
{
	return (((front + 1) % (MAX_ELEMENTS + 1)) == back);
}

bool StaticQueueClass::IsFull() const
//Purpose:	determines whether the queue is full
//Pre:		queue exists
//Post:		returns true if queue is full and false otherwise
{
	return (front == back);
}

void StaticQueueClass::EnQ(ItemType/*in*/ newItem) // item to enqueue 

//Purpose:	adds newItem to the rear(back) of the queue
//Pre:		queue is not full
//Post:		newItem is added to the rear of the queue
//Exceptions Thrown : FullQueueException
{
	if (!IsFull())
	{
		queue[back] = newItem;
		back = (back + 1) % (MAX_ELEMENTS + 1);
	}
	else
		throw FullQueueException();
}

void StaticQueueClass::DeQ()
//Purpose:	removes the item at the front of the queue
//Pre:		queue is not empty
//Post:		the item at the front of the queue has been removed
{
	if (!IsEmpty())
		front = (front + 1) % (MAX_ELEMENTS + 1);
}

ItemType StaticQueueClass::Retrieve() const
//Purpose:	returns the copy of the item at the front of the queue
//Pre:		queue is not empty
//Post:		the copy of the item at the front is returned
//Exceptions Thrown : RetrieveOnEmptyException
{
	if (!IsEmpty())
		return queue[(front + 1) % (MAX_ELEMENTS + 1)];
	else
		throw RetreiveOnEmptyException();
}

void StaticQueueClass::Clear()
//Purpose:	makes the queue empty
//Pre:		queue exists
//Post:		queue has been cleared
{
	front = 0;
	back = front + 1;
}

void StaticQueueClass::operator = (/*in*/ const StaticQueueClass& orig) // queue to copy
//Purpose:	performs deep copy of orig to applying queue object
//Pre:		orig exists
//Post:		contents of orig are copied into applying queue object
{
	front = orig.front;
	back = orig.back;

	for (int i = 0; i < MAX_ELEMENTS + 1; i++)
	{
		queue[i] = orig.queue[i];
	}
}