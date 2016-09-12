/*
	Author:			Gregory D Hughes
	Date:			April 15th 2015
	Project:		CPU Simulation
	Filename:		CLLTestClient.cpp
	Purpose:		To test hte methods that are used in the CLL queue class
	Input:			None
	Processing:		Use a dynamic queue to test all methods of class
	Output:			Prints use of class to screen
	Assumptions:	None
	Exceptions
	Thrown:			None
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>				// For testing only
#include "CLLQueueClass.h"		// Data structure for wait queue

using namespace std;

//////////////////////////////////////////////////////////////////Declarations//////////////////////////////////////////////////////////////////

const int ITEMS_IN_QUEUE = 25;

///////////////////////////////////////////////////////////////////Prototypes//////////////////////////////////////////////////////////////////
//Test the constructor and operator equals for class
CLLQueueClass TestEnQConstructorsAndEquals();

// Fills the queue with numbers in order up to ITEMS_IN_QUEUE
void FillQueue(CLLQueueClass& theQ,					// Queue to be filled
				bool print);						// predicates if the inserts are printed to screen

// Test the deQ nd the Retreive  methods of class
void TestDeQAndRetreive(CLLQueueClass& theQ);		// Queue to be modified

// Test the observer predicators of class
void TestPredicators(CLLQueueClass& theQ);			// Queue to be modified

// Tests the clear method of class
void TestClear(CLLQueueClass& theQ);				// Queue to be modified

// Prints a line to seperate data in file
void PrintLine();

void main()
{
	// Test the first
	CLLQueueClass theQ = TestEnQConstructorsAndEquals();

	cout << "Copy constructor and operator equals work successfully!" << endl;

	PrintLine();

	// Test the second
	TestDeQAndRetreive(theQ);
	
	PrintLine();

	// Test the third
	TestPredicators(theQ);

	PrintLine();

	// Test the Fourth and final
	TestClear(theQ);

	PrintLine();

	cout << "All tests completed! ";
}

CLLQueueClass TestEnQConstructorsAndEquals()
{
	CLLQueueClass theQ;

	cout << "Class instantiated successfully!" << endl;

	FillQueue(theQ, true);

	return theQ;
}

void FillQueue(CLLQueueClass& theQ,					// Queue to be filled
				bool print)							// predicates if the inserts are printed to screen
// Pre:		The queue is initialized
// Post:	The queue is filled
{
	ItemType temp;

	// Fill the queue
	for (int i = 1; i <= ITEMS_IN_QUEUE; i++)
	{
		temp.key = i;

		// if the print bool is selected print the number that is to be inserted
		if (print)
			cout << "Inserting item with key " << i << endl;

		theQ.EnQ(temp);
	}
}

void TestDeQAndRetreive(CLLQueueClass& theQ)		// Queue to be modified
// Pre:		The queue is filled
// Post:	The queue is emptied
{
	int num = 1;

	// while there is items in the queue deQ
	while (!theQ.IsEmpty())
	{
		cout << "Position " << num << " in queue:\t " << theQ.Retrieve().key << endl;

		theQ.DeQ();

		num++;
	}
}

void TestPredicators(CLLQueueClass& theQ)			// Queue to be modified
// Pre:		The Queue is emptied
// Post:	The queue is filled
{
	// Test ISEmpty
	if (theQ.IsEmpty())
		cout << "Is empty method works!" << endl;
	else
		cout << "Is empty method fails..." << endl;

	FillQueue(theQ, false);

	// test ISFull
	if (!theQ.IsFull())
		cout << "Is full method works!" << endl;
	else
		cout << "Is full method fails..." << endl;
}

void TestClear(CLLQueueClass& theQ)					// Queue to be modified
// Pre: The queue is filled
// Post:	The queued is emptied
{
	// Test Clear method
	theQ.Clear();

	if (theQ.IsEmpty())
		cout << "Clear method works!" << endl;
	else
		cout << "Clear method fails!" << endl;
}

void PrintLine()
// Pre:		None
// Post:	A line is printed to screen seperating data
{
	// width of console
	int width = 80;

	// Enter line above
	cout << endl;

	// use hyphens for line
	for (int i = 0; i < width; i++)
		cout << "-";

	// Enter line below
	cout << endl;
}

/*
Class instantiated successfully!
Inserting item with key 1
Inserting item with key 2
Inserting item with key 3
Inserting item with key 4
Inserting item with key 5
Inserting item with key 6
Inserting item with key 7
Inserting item with key 8
Inserting item with key 9
Inserting item with key 10
Inserting item with key 11
Inserting item with key 12
Inserting item with key 13
Inserting item with key 14
Inserting item with key 15
Inserting item with key 16
Inserting item with key 17
Inserting item with key 18
Inserting item with key 19
Inserting item with key 20
Inserting item with key 21
Inserting item with key 22
Inserting item with key 23
Inserting item with key 24
Inserting item with key 25
Copy constructor and operator equals work successfully!

--------------------------------------------------------------------------------

Position 1 in queue:     1
Position 2 in queue:     2
Position 3 in queue:     3
Position 4 in queue:     4
Position 5 in queue:     5
Position 6 in queue:     6
Position 7 in queue:     7
Position 8 in queue:     8
Position 9 in queue:     9
Position 10 in queue:    10
Position 11 in queue:    11
Position 12 in queue:    12
Position 13 in queue:    13
Position 14 in queue:    14
Position 15 in queue:    15
Position 16 in queue:    16
Position 17 in queue:    17
Position 18 in queue:    18
Position 19 in queue:    19
Position 20 in queue:    20
Position 21 in queue:    21
Position 22 in queue:    22
Position 23 in queue:    23
Position 24 in queue:    24
Position 25 in queue:    25

--------------------------------------------------------------------------------

Is empty method works!
Is full method works!

--------------------------------------------------------------------------------

Clear method works!

--------------------------------------------------------------------------------

All tests completed! Press any key to continue . . .

*/