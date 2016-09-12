/*
	Author:			Luke Musto
	Modifications:	Gregory Hughes
	Date:			04/15/2015
	Purpose:		Specification file for CLLQueueClass. Class contains one default constructor, a copy constructor, destructor and 7 public 
					methods. Queue is dynamic and can contain as many elements as needed.
	Project:		CPU Simulation
	Filename:		CLLQueueClass.h
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


#include "ItemType.h"	// for declaration of item's data type
#include <new>			// for bad_alloc

//forward declaration
struct node;

//Class Declarations

class CLLQueueClass
{
	public:
/******************* Constructors and Destructors********************************************/
		CLLQueueClass();
		//Purpose:	default constructor initializes private members
		//Pre:		object has been instantiated
		//Post:		object has been initialized
		
		~CLLQueueClass();		
		//Purpose:	destructor - deallocates all memory after the class 
		//			object is destroyed
		//Pre:		none
		//Post:		arrays created in the free store are no longer there

		CLLQueueClass(const CLLQueueClass& orig);
		//Purpose:	copy constructor - creates a deep copy of the original object
		//Pre:		object has been initialized
		//Pre:		a copy of the object has been created

/********************************************************************************************/

		bool IsEmpty() const;	
		//Purpose:	determines whether the queue is empty
		//Pre:		queue exists
		//Post:		returns true if queue is empty and false otherwise

		bool IsFull() const;
		//Purpose:	determines whether the queue is full
		//Pre:		queue exists
		//Post:		returns true if queue is full and false otherwise

		void EnQ(/*in*/ ItemType newItem);  //Item to be enqueued
		//Purpose:	adds newItem to the rear(back) of the queue
		//Pre:		queue is not full
		//Post:		newItem is added to the rear of the queue

		void DeQ();				
		//Purpose:	removes the item at the front of the queue
		//Pre:		queue is not empty
		//Post:		the item at the front of the queue has been removed

		ItemType Retrieve() const;
		//Purpose:	returns the copy of the item at the front of the queue
		//Pre:		queue is not empty
		//Post:		the copy of the item at the front is returned
		//Exceptions Thrown: RetrieveOnEmpty Exception

		void Clear();
		//Purpose:	makes the queue empty
		//Pre:		queue exists
		//Post:		queue has been cleared

		void operator=(/*in*/ const CLLQueueClass&  orig);
		//Purpose:	performs deep copy of orig to applying queue object
		//Pre:		orig exists
		//Post:		contents of orig are copied into applying queue object

	private:
		node* tail;			// Queue with dynamically allocated memory


		node* Allocate();
		//Purpose:	allocates a new node 
		//Pre:		queue exists.
		//Post:		a new node has been allocated and returned. 
		//Exceptions Thrown: OutofMemoryException is thrown if allocate is unsuccessful
		
};




