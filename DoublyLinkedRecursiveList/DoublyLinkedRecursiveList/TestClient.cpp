/**************************************************************************************************
											TEST CLIENT
Author: Gregory Hughes
Date:	April 26th 2015
Project: Doubly Linked Recursive List
Filename: TestClient.cpp
Purpose: To test all methodas created in the OrdList Class

Input: Input from keyboard to confirm if two of the three operators work correctly

Processing: Using the OrdList class object we process several lists by testing methods with each list.

Output: Output results to screen

Assumptions:  No more than 11 items will be generated for each list object 

Exception Handling: Exceptions are thrown in the event of a duplicate key entering list, 
	if a key is not contained in the list or in the event the program runs out of memory

***************************************************************************************************/

// Included libraries
#include "OrdList.h"		// For the OrdListClass object.
//#include "ItemType.h"		// For the ItemType struct and KeyType definition.			Included in OrdList.h
//#include <iostream>		// For outputting the results of operations to the screen.	Included in OrdList.h

using namespace std;

//*************************************************************************************************

////////////////////////////////////////////////////////// Prototypes //////////////////////////////////////////////////////////

// Will test the Default Constructor, Copy Constructor and the destructor
OrdListClass TestConstructorsAndDestructor();

// Tests the clear methods of class
void TestClear(/*in/out*/OrdListClass& list);					// List to be tested

// Tests the retrieve method of class
void TestRetreive(/*in*/OrdListClass& list);					// List to be tested

// Tests the Mutators of class
void TestModifiers(/*in/out*/OrdListClass& list);				// List to be tested

// Tests the Insert method of class
bool TestInsert(/*in/out*/OrdListClass& list);					// List to be tested

// Tests the deletion method of class
bool TestDelete(/*in/out*/OrdListClass& list);					// List to be tested

// Tests the overloaded operators of class
void TestOperators(/*in/out*/OrdListClass& listA,				// Lists to test
					/*in/out*/OrdListClass& listB);				// operators

// Tests the addition method of class
bool TestAddition(/*in/out*/OrdListClass& listA,				// Lists to test
					/*in/out*/OrdListClass& listB);				// operator

// Tests the Subtraction method of class
bool TestSubtraction(/*in/out*/OrdListClass& listA,				// Lists to test
					/*in/out*/OrdListClass& listB);				// operator

// Attempts to insert item in to class object, throws exception in cases of duplicate keys.
void TryInsert(/*in/out*/OrdListClass& list,					// List to be modified
				/*in*/ItemType item);							// Item to insert into list

// Attempts to delete item from class object, throws exception in cases of missing keys.
void TryDelete(/*in/out*/OrdListClass& list,					// List to be modified
				/*in*/KeyType key);								// Key of item to delete

// Attempts to retrieve item from class object, throws exception in cases of missing keys.
bool TryRetrieve(/*in/out*/OrdListClass& list,					// List to retrieve item from
					/*in*/KeyType key);							// key of item to be returned

// Prints a line accross the command line to break up tests.
void PrintLine();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	// Test the Construcotr, the Copy constructor and the Destructor
	OrdListClass listOne = TestConstructorsAndDestructor();

	cout << "Default Constructor, Copy Constructor and Destructor successful!" << endl;

	// Test Clear method
	TestClear(listOne);

	// Test Mutators
	TestModifiers(listOne);

	// Add list for operations
	OrdListClass listTwo;

	// Test operations
	TestOperators(listOne, listTwo);

	// Test Retrieve
	TestRetreive(listOne);

	// End tests
	cout << "All Tests complete. ";
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OrdListClass TestConstructorsAndDestructor()
// Pre:		None
// Post:	Class objects are initialized, and then destructed and deep copied back to caller.
{
	// Test default constructor
	OrdListClass aList;

	// Creat list to be destructed
	OrdListClass listToDestruct;

	// Temporary variable for insertion
	ItemType stuff;

	// fill in list to be destructed
	for (int i = 25; i > 0; i--)
	{
		stuff.key = i;

		listToDestruct.Insert(stuff);
	}

	// fill in list with random values
	for (int i = 0; i < 10; i++)
	{
		stuff.key = rand();
		aList.Insert(stuff);
	}

	// Test copy constructor as object is copied to caller
	return aList;

	// Test destructor as object leaves scope.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestClear(/*in/out*/OrdListClass& list)					// List to be Cleared
// Pre:		A list is initialized and has been filled with values
// Post:	A list with values is cleared
{
	// Print spacer
	PrintLine();
	
	// Print list pre-clear
	list.Print();

	// Print Space
	PrintLine();

	// Clear List
	list.Clear();

	// Don't print list
	list.Print();

	// Show list is cleared above, print fun statment.
	cout << "List cleared" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestModifiers(/*in/out*/OrdListClass& list)				// List to be tested
// Pre:		A List has been instantiated and cleared of all values
// Post:	A List will have items placed into the list and then have an item will be removed.
{
	// Print spacer
	PrintLine();

	// Test insertion
	// print statement accordingly representing if test succeeded or failed.
	if (TestInsert(list))
		cout << "Insert tested successfully" << endl;
	else
		cout << "Insert tested unsuccessfully" << endl;

	// Print spacer
	PrintLine();

	// Test Deletion
	// print statement accordingly representing if test succeeded or failed.
	if (TestDelete(list))
		cout << "Delete tested successfully" << endl;
	else
		cout << "Delete tested unsuccessfully" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TestInsert(/*in/out*/OrdListClass& list)					// List to be tested
// Pre:		A list is instantiated and is free of elements.
// Post:	List is filled with several items and returns true
{
	// Item to be inserted into list
	ItemType stuff;
	
	// set temporary item.
	stuff.key = 76;

	// Atempt the insert
	TryInsert(list, stuff);

	// set temporary item.
	stuff.key = 43;

	// Atempt the insert
	TryInsert(list, stuff);

	// set temporary item.
	stuff.key = 26;

	// Atempt the insert
	TryInsert(list, stuff);

	// set temporary item.
	stuff.key = 50;

	// Atempt the insert
	TryInsert(list, stuff);
	
	// Print list to show items are in order
	list.Print();

	// and a space
	cout << endl;

	// and again in reverse, testing both print methods.
	list.PrintReverse();

	// Return true, because I didn't quite think this through
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TestDelete(/*in/out*/OrdListClass& list)					// List to be tested
// Pre:		A List is instantiated and is filled with elements, of which one is to be deleted.
// Post:	List has the element removed from the list. True is returned
{
	// Key to be inserted into list
	KeyType stuff;

	// Set temp Key
	stuff = 50;
		
	// Attempt to delete the key
	TryDelete(list, stuff);

	// Print list to show items are in order
	list.Print();

	// and a space
	cout << endl;

	// and again in reverse, testing both print methods.
	list.PrintReverse();

	// Return true - See above
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestOperators(/*in/out*/OrdListClass& listA,				// Lists to test
					/*in/out*/OrdListClass& listB)				// operators
// Pre:		ListA and listB are instantiated and listA contains elements and ListB contains no elements.
// Post:	The two lists are added and subtracted from one another.
{
	// Print space
	PrintLine();

	// Creat temporary element for insertion
	ItemType stuff;

	// Add values to temporary item
	stuff.key = 10;

	// Attempt to insert
	TryInsert(listB, stuff);

	// Test the addition of two list an output accordingly
	if (TestAddition(listA, listB))
		cout << "Test of addition successful" << endl;
	else
		cout << "Test of addition successful" << endl;

	// Print space
	PrintLine();

	// Test the subtraction of two list an output accordingly
	if (TestSubtraction(listA, listB))
		cout << "Test of subtraction successful" << endl;
	else
		cout << "Test of subtraction successful" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TestAddition(/*in/out*/OrdListClass& listA,				// Lists to test
					/*in/out*/OrdListClass& listB)				// operator
// Pre:		ListA has been instantiated and contains no elements from listB
// Post:	All elements that are contained in listB are added to listA
{
	// Set char to enter loop
	char ans = '0';
	
	// Test method
	listA = listA + listB;
	
	// print the new list to screen
	listA.Print();

	// add space
	cout << endl;

	// Print list in reverse to test the method
	listA.PrintReverse();

	// Ask for user input
	while (ans != 'y' || ans != 'n')
	{
		cout << "Is 10 in the list and is the list in order?\ty/n\t";
		cin >> ans;

		// if yes return true, if no return false, all other repeat question.
		switch (ans)
		{
		case'y': return true; break;
		case'n': return false; break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TestSubtraction(/*in/out*/OrdListClass& listA,				// Lists to test 
						/*in/out*/OrdListClass& listB)			// operator
// Pre:		ListA has been instantiated and contains all elements in listB and other values
// Post:	All elements that are contained in listB removed from listA
{
	// Set char for loop entry
	char ans = '0';

	// Test subtraction
	listA = listA - listB;
	
	// print the new list to screen
	listA.Print();

	// add space
	cout << endl;

	// Print list in reverse to test the method
	listA.PrintReverse();

	// Ask for user input
	while (ans != 'y' || ans != 'n')
	{
		cout << "Was 10 removed from the list and is the list in order?\ty/n\t";
		cin >> ans;

		// if yes return true, if no return false, all other repeat question.
		switch (ans)
		{
		case'y': return true; break;
		case'n': return false; break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestRetreive(/*in/out*/OrdListClass& list)					// List to be tested
// Pre:		List Contains the original elements from the TestInsert function
// Post:	Display appropriate message if the element is or isnt found in list.
{
	// Print space
	PrintLine();

	// Set key to search for
	KeyType key = 76;

	// Attempt to find item, if found output message
	if (TryRetrieve(list, key))
		cout << "Key \"" << key << "\" found in list.\n";

	// print space
	PrintLine();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TryInsert(/*in/out*/OrdListClass& list,					// List to be modified
				/*in*/ItemType item)							// Item to insert into list
// Pre:		List is instantiated and item is defined be caller
// Post:	item is inserted into list, unless list contains item
// Exceptions 
// thrown:	DuplicateKeyException thrown in the event that item is already contained in list.
{
	try
	{
		// try the insert
		list.Insert(item);
	}
	catch (DuplicateKeyException)
	{
		// unless insert fails, display message
		cout << "List contains an item with the key field of \"" << item.key << "\"." << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TryDelete(/*in/out*/OrdListClass& list,					// List to be modified
				/*in*/KeyType key)								// Key of item to delete
// Pre:		List contains elements, and key is defined
// Post:	Item with key mathing in list is removed from list, unless item is missing
// Exceptions
// thrown:	KeyNotThereException thrown in the event a key is not found in the list.
{
	try
	{
		// Attempt deletion
		list.Delete(key);
	}
	catch (KeyNotThereException)
	{
		// Or throw missing key exception
		cout << "List does not contains an item with the key field of \"" << key << "\"." << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool TryRetrieve(/*in/out*/OrdListClass& list,					// List to retrieve from
					/*in*/KeyType key)							// Key of item to retrieve
// Pre:		List contains elements, and key is defined
// Post:	Item with key mathing in list is returned from list, unless item is missing
// Exceptions
// thrown:	KeyNotThereException thrown in the event a key is not found in the list.
{
	try
	{
		// Attempt ot retrieve from list, and return true
		list.Retrieve(key);
		return true;
	}
	catch (KeyNotThereException)
	{
		// Or show that the key was missing and return false
		cout << "Key \"" << key << "\" not contained within the list.\n";
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintLine()
// Pre:		None
// Post:	A line is printed in the command line to provide space between tests
{
	// width of command line
	int width = 80;

	// Add a space
	cout << endl;

	// Create line
	for (int i = 0; i < width; i++)
		cout << "-";

	// add more space.
	cout << endl;
}