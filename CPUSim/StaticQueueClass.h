/*
	Author:			Luke Musto
	Modifications:	Gregory Hughes
	Date:			04/15/2015
	Purpose:		Specification file for StaticQueueClass. Class contains one default constructor, and 7 public methods.
					Queue can contain 5 elements and is held in the named constant MAX_ELEMENTS.
	Project:		CPU Simulation
	Filename:		StaticQueueClass.h
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


// Item the is to be used in the queue
#include "ItemType.h"

// size of queue 
const int MAX_ELEMENTS = 5; 

class StaticQueueClass 
{
public: 

		StaticQueueClass();
		//Purpose:	default constructor initializes private members
		//Pre:		object has been instantiated
		//Post:		object has been initialized
		
		bool IsEmpty() const;	
		//Purpose:	determines whether the queue is empty
		//Pre:		queue exists
		//Post:		returns true if queue is empty and false otherwise

		bool IsFull() const;
		//Purpose:	determines whether the queue is full
		//Pre:		queue exists
		//Post:		returns true if queue is full and false otherwise

		void EnQ(ItemType/*in*/ newItem); // item to enqueue 
					
		//Purpose:	adds newItem to the rear(back) of the queue
		//Pre:		queue is not full
		//Post:		newItem is added to the rear of the queue
		//Exceptions Thrown : FullQueue Exception

		void DeQ();				
		//Purpose:	removes the item at the front of the queue
		//Pre:		queue is not empty
		//Post:		the item at the front of the queue has been removed

		ItemType Retrieve() const;
		//Purpose:	returns the copy of the item at the front of the queue
		//Pre:		queue is not empty
		//Post:		the copy of the item at the front is returned
		//Exceptions Thrown : RetrieveOnEmpty  Exception

		void Clear();
		//Purpose:	makes the queue empty
		//Pre:		queue exists
		//Post:		queue has been cleared

		void operator=(/*in*/ const StaticQueueClass& orig); // queue to copy
		//Purpose:	performs deep copy of orig to applying queue object
		//Pre:		orig exists
		//Post:		contents of orig are copied into applying queue object

private: 
		ItemType queue[MAX_ELEMENTS+1];	// array of JobRec items
		int front;						// front of queue 
		int back;						// back of queue 
};
