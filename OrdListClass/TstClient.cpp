/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Author:			Gregory Hughes
	Project:		OrdListClass
	Filename:		TstClient.cpp
	Date:			March 18th 2015
	Input:			None
	Processing:		Using the OrdListClass we test the methods to order a list and add methods to expand
					and contract the object as needed
	Output:			Out put test results to screen
	Assumptions:	The list will never be full
	Error
	Checking:		The test client error checks the methods found in OrdListClass
*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OrdList.h"		// includes all members and libraries needed for testing purposes

using namespace std;

///////////////////////////////////////////////////////////////////Constants///////////////////////////////////////////////////////////////////

// Keys to be inserted, searched for and deleted from an OrdListClass object
const KeyType KEY_A = 1;	
const KeyType KEY_B = 2;
const KeyType KEY_C = 3;
const KeyType KEY_D = 4;
const KeyType KEY_E = 5;

///////////////////////////////////////////////////////////////////Prototypes//////////////////////////////////////////////////////////////////

// Groups multiple methods that were coded for the decendant class into a related function for testing
void TestMethods(/*in/out*/ OrdListClass& myList);					// List to be modified in each test

// Tests the IsFull method
void TestIsFull(/*in/out*/ OrdListClass& myList);					// List to be modified in each test

// Test the Insert method
void TestInsert(/*in/out*/ OrdListClass& myList);					// List to be modified in each test

// Tests the Find Method
void TestFind(/*in/out*/ OrdListClass& myList);						// List to be modified in each test

// Tests the Delete Method
void TestDelete(/*in/out*/ OrdListClass& myList);					// List to be modified in each test

// Groups multiple protected (impliied) methods into a related function for testing
void TestProtectedMethods(/*in/out*/ OrdListClass& myList);			// List to be modified in each test

// Test the Expand method that is implied with the insert function
void TestExpand(/*in/out*/ OrdListClass& myList);					// List to be modified in each test

// test the Contract method that is implied with the delete function
void TestContract(/*in/out*/ OrdListClass& myList);					// List to be modified in each test

// Groups multiple operator methods into a related function for testing
void TestOperators(	/*in/out*/ OrdListClass& myList,				// Applying class object for operand
					/*in/out*/ OrdListClass& yourList,				// Left operand class object for operand
					/*in/out*/ OrdListClass& theirList);			// Right operand class object for operand

// Tests the operator= method
void TestOperatorEquals(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList);			// Right operand class object for operand

// Tests the operator== and the operator!= methods
void TestPredicatingOps(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList);				// Right operand class object for operand

// tests the operator* (join) method
void TestJoinOperator(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList,			// Left operand class object for operand
						/*in/out*/ OrdListClass& theirList);		// Right operand class object for operand

// Tests the operator+ (merge) operator
void TestMergeOperator(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList,			// Left operand class object for operand
						/*in/out*/ OrdListClass& theirList);		// Right operand class object for operand

void TryInsert(/*in/out*/ OrdListClass& anyList,					// List to insert itemType into
				/*in*/ ItemType insertable);						// object to insert into list

// Prints any ordListClass object to screen
void PrintAnyList(/*in*/ OrdListClass& anyList);					// The list to be printed

// Prints two lists to screen respectively
void PrintMineAndYours(/*in/out*/ OrdListClass& myList,				// First list to be printed
						/*in/out*/ OrdListClass& yourList);			// Second list to be printed

// Prints a line to seperate output
void PrintLine();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	//Testing constructor
	OrdListClass myList, yourList, theirList;
	cout << "Classes instantiated successfully\n\nBeginning tests... ";

	system("pause");
	system("cls");

	// test the methods of the class
	TestMethods(myList);

	// Test the implied protected methods by using the insert and delete functionalty of OrdListClass
	TestProtectedMethods(myList);

	// Test the operators to the OrdListClass
	TestOperators(myList, yourList, myList);

	cout << endl;

	// Print some seperation and exit
	PrintLine();

	// Done!
	cout << endl << "All Tests Complete" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestMethods(/*in/out*/ OrdListClass& myList)					// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	All new access modifier methods are tested
{
	PrintLine();

	cout << "Beginning to test general methods" << endl;

	PrintLine();

	cout << endl;

	// Test public methods of class to make sure they work appropriately
	
	TestIsFull(myList);

	PrintLine();

	TestInsert(myList);

	PrintLine();

	TestFind(myList);

	PrintLine();

	TestDelete(myList);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestIsFull(/*in/out*/ OrdListClass& myList)					// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The IsFull method is tested
{
	// If the list is not full( which it can not be) output appropriate message
	if (myList.IsFull())
		cout << "Test failed. List can not be full." << endl;
	// There was a simple coding error and you should re-think your major
	else
		cout << "Test succeeded! List can not be full." << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestInsert(/*in/out*/ OrdListClass& myList)					// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The Insert method is tested and objects are inserted into the list
{
	ItemType tempItem;		// temporary item to be inserted and modified to insert more items into list

	// Initialize tempItem
	tempItem.key = KEY_A;

	// Insert into empty list
	TryInsert(myList, tempItem);

	PrintAnyList(myList);

	cout << " == " << KEY_A << endl;


	// if the insertion was a success add more members to the list for further operations
	if (KEY_A == myList.Retrieve().key)
	{
		cout << "Insertion successful... Inserting three more elements into list(2,3,4)\n";

		// add 3 more keys to list for further operations
		tempItem.key = KEY_B;
		TryInsert(myList, tempItem);
		myList.Print();
		cout << " == " << KEY_B << endl;

		tempItem.key = KEY_C;
		TryInsert(myList, tempItem);
		myList.Print();
		cout << " == " << KEY_C << endl;

		tempItem.key = KEY_D;
		TryInsert(myList, tempItem);
		myList.Print();
		cout << " == " << KEY_D << endl;
	}
	// if the test was unsucsessful output message and exit
	else
	{
		cout << "Insertion failed\n";
		exit(0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestFind(/*in/out*/ OrdListClass& myList)						// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The Find method is tested
{
	// show the key to be find
	cout << KEY_C;

	// If the key is found report appropriately
	if (myList.Find(KEY_C))
		cout << " found in list, find successful";
	// If the key is not found report appropriately
	else
		cout << " not found in list, find unsuccessful";

	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestDelete(/*in/out*/ OrdListClass& myList)					// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The Delete method is tested and objects are removed from the list
{
	// Delete only if found in the list
	if (myList.Find(KEY_C))
		myList.Delete();

	// if the key is not found the delete function works properly
	if (!myList.Find(KEY_C))
		cout << "Delete successful. " << KEY_C << " removed.";
	else
		cout << "Delete unsuccessful.\n";

	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestProtectedMethods(/*in/out*/ OrdListClass& myList)			// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The protected methods that are including in other methods are tested
{
	PrintLine();

	cout << "Beginning to test protected methods that are implied in public methods of class" << endl;

	PrintLine();

	cout << endl;

	// Test the protected methods by calling functions that will use public methods that imply the use of protected methods

	TestExpand(myList);

	PrintLine();

	TestContract(myList);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestExpand(/*in/out*/ OrdListClass& myList)					// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The expand method is tested and the original object doubles in size
{
	ItemType tempItem;			// temporary item to be altered and inserted into list

	// Only insert into list if the key is not found
	tempItem.key = KEY_C;
	TryInsert(myList, tempItem);
	cout << KEY_C << " re-inserted into list" << endl;

	// keep track of the old size to determine if the list did indeed expand
	int oldSize = myList.GetLength();

	cout << "Current length = " << myList.GetLength() << endl;

	// Only insert into list if the key is not found
	tempItem.key = KEY_E;
	TryInsert(myList, tempItem);
	cout << KEY_E << " inserted into list" << endl;

	cout << "\tNew length = " << myList.GetLength() << endl;

	// The test is successful if the length of the new list surpasses the size of the old list
	if (myList.GetLength() > oldSize)
		cout << "Expand list successful";
	else
		cout << "Expand list unsuccesful";

	cout << endl;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestContract(/*in/out*/ OrdListClass& myList)					// List to be modified in each test
// Pre:		An OrdListClass object has been instantiated
// Post:	The contract method is tested and the object is shrunk in half
{
	cout << "List has " << myList.GetLength() << " elements." << endl;

	// Delete key only if found
	if (myList.Find(KEY_E))
		myList.Delete();

	// Delete key only if found
	if (myList.Find(KEY_D))
		myList.Delete();

	// Delete key only if found
	if (myList.Find(KEY_C))
		myList.Delete();			
	
	// this does work, the size is private and the way to access it is protected from client
	cout << "3 keys removed. List has " << myList.GetLength() << " elements." << endl;

	cout << "List shrunk succcessfully" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestOperators(	/*in/out*/ OrdListClass& myList,				// Applying class object for operand
					/*in/out*/ OrdListClass& yourList,				// Left operand class object for operand
					/*in/out*/ OrdListClass& theirList)				// Right operand class object for operand
// Pre:		Three OrdListClass objects are intitialized
// Post:	All operators of an OrdListClass Object are tested
{
	cout << "Begin to test operators" << endl;

	PrintLine();

	cout << endl;
	
	// call functions to test each of the operators

	TestOperatorEquals(myList, yourList);

	PrintLine();

	TestPredicatingOps(myList, yourList);

	PrintLine();

	TestJoinOperator(myList, yourList, theirList);

	PrintLine();

	TestMergeOperator(myList, yourList, theirList);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestOperatorEquals(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList)				// Right operand class object for operand
// Pre:		myList is initialized and contains elements
// Post:	myList is copied into yourList
{
	// new list gets the old list (that is filled)
	yourList = myList;

	// Print the new list to show they are equivalent
	PrintMineAndYours(myList, yourList);

	cout << "\nIf above numbers match, test of Operator= successful.\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestPredicatingOps(/*in/out*/ OrdListClass& myList,			// Applying class object for operand
						/*in/out*/ OrdListClass& yourList)			// Right operand class object for operand
// Pre:		myList and yourList are initialized and match
// Post:	The == and != operators are tested
{
	ItemType tempItem;		// temporary item to be inserted

	// print the list to screen for testing purposes
	PrintMineAndYours(myList, yourList);

	// the lists are the same due to last operation
	// output result
	if (myList == yourList)
		cout << "Operator== tested successfully.\n";
	else
		cout << "Operator== tested unsuccessfully.\n";

	cout << endl;

	PrintLine();


	// Make yourList contain key B (2) and C (3)
		// Find the key to change the contents of list
		if (yourList.Find(KEY_A))
			yourList.Delete();
		
		//Create a temporary key with the value of 3 and insert it into list
		tempItem.key = KEY_C;
		TryInsert(yourList, tempItem);

	// yourList now contains key B and C


	// Make myList contain key A (1) and D (4)
		// Find the key to change the contents of list
		if (myList.Find(KEY_B))
			myList.Delete();

		//Create a temporary key with the value of 4 and insert it into list
		tempItem.key = KEY_D;
		TryInsert(myList, tempItem);
	// myList now contains key A and D

	// Print the outcome of the operand
	PrintMineAndYours(myList, yourList);

	// show results
	if (myList != yourList)
		cout << "Operator!= tested successfully.\n";
	else
		cout << "Operator!= tested unsuccessfully.\n";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestJoinOperator(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList,			// Left operand class object for operand
						/*in/out*/ OrdListClass& theirList)			// Right operand class object for operand
// Pre:		myList and yourList are occupied
// Post:	theirList is the join of the above mentioned lists
{
	ItemType tempItem;			// Temporary temporary item to insert into list

	// Assign key number 4 to temporary item
	tempItem.key = KEY_D;

	// attempt to insert item into list
	TryInsert(yourList, tempItem);
	
	// Print the list to screen for testing purposes
	cout << "The two lists to join are as follows:\n";
	PrintMineAndYours(myList, yourList);

	cout << endl;

	// Create new list, a join of the two previous lists
	theirList = myList * yourList;

	// Print information regarding test for user
	cout << "The only key in the new list should be " << KEY_D << endl;

	PrintAnyList(theirList);

	cout << "If the above key matches, Operator* successful.";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestMergeOperator(/*in/out*/ OrdListClass& myList,				// Applying class object for operand
						/*in/out*/ OrdListClass& yourList,			// Left operand class object for operand
						/*in/out*/ OrdListClass& theirList)			// Right operand class object for operand
// Pre:		myList and yourList are occupied
// Post:	theirList is the merge of the above mentioned list
{
	ItemType tempItem;		// Temporary item to be inserted into list

	// Initialize temp item with key 5
	tempItem.key = KEY_E;
	// and insert into list
	TryInsert(myList, tempItem);

	// print the lists for test
	cout << "The two lists to merge are as follows:\n";
	PrintMineAndYours(myList, yourList);

	cout << endl;

	// get the result of merging lists
	theirList = myList + yourList;

	// Print to screen
	PrintAnyList(theirList);

	cout << "If the above key matches, Operator+ successful.";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TryInsert(/*in/out*/ OrdListClass& anyList,					// List to insert itemType into
				/*in*/ ItemType insertable)							// object to insert into list
// Pre:		A list has been initialized
// Post:	An Itemtype record may be inserted into list
// Exceptions
// Thrown:	DuplicartKeyException thrown in the event that the key already exists in the OrdListClass object
{
	try
	{
		// Attempt to insert the item into list
		anyList.Insert(insertable);
	}
	catch (DuplicateKeyException)
	{
		// if there is a duplicate key output message
		cout << "There is already a key \""<< insertable.key << "\" inside of the list class object" << endl;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintAnyList(/*in*/ OrdListClass& anyList)						// The list to be printed
// Pre:		anyList contains elements
// Post:	anyList is printed to screen for testing purposes
{
	// Prime loop
	anyList.FirstPosition();

	// Print all members of the class
	while (!anyList.EndOfList())
	{
		// Print each member of list
		anyList.Print();

		cout << endl;

		// Modify LCV
		anyList.NextPosition();
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMineAndYours(/*in/out*/ OrdListClass& myList,				// First list to be printed
						/*in/out*/ OrdListClass& yourList)			// Second list to be printed
// Pre:		myList and YourList contain elements
// Post:	myList and YourList are printed to screen
{
	// Prime loop
	myList.FirstPosition();
	yourList.FirstPosition();
	
	cout << "List 1\t\t\tList2" << endl;

	// Print contents of list until the list of shorter length is done printing
	while (!myList.EndOfList() && !yourList.EndOfList())
	{
		myList.Print();
		cout << "\t= ";
		yourList.Print();

		cout << endl;

		// Modify LCV
		myList.NextPosition();
		yourList.NextPosition();
	}

	// If the first list is not done printing
	if (!myList.EndOfList())
	{
		// print members until the end of list
		while (!myList.EndOfList())
		{
			myList.Print();
			cout << "\t= " << endl;

			// Modify LCV
			myList.NextPosition();
		}
	}
	// If the second list is not done printing
	else if (!yourList.EndOfList())
	{
		// print members until the end of list
		while (!yourList.EndOfList())
		{
			cout << "\t\t\t= ";
			yourList.Print();
			cout << endl;

			// Modify LCV
			yourList.NextPosition();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintLine()
// Pre:		None
// Post:	A line is printed accross the console window
{
	int pageWidth = 80;		// Width of the console. Kept variable to allow for platform changes

	cout << endl;

	for (int i = 0; i < pageWidth; i++)
		cout << "-";

	cout << endl;
}

/*
Classes instantiated successfully

Beginning tests... Press any key to continue . . .

--------------------------------------------------------------------------------

Beginning to test general methods

--------------------------------------------------------------------------------


Test succeeded! List can not be full.

--------------------------------------------------------------------------------

Item 0 contains key 1 == 1
Insertion successful... Inserting three more elements into list(2,3,4)
Item 1 contains key 2 == 2
Item 2 contains key 3 == 3
Item 3 contains key 4 == 4

--------------------------------------------------------------------------------

3 found in list, find successful

--------------------------------------------------------------------------------

Delete successful. 3 removed.

--------------------------------------------------------------------------------

Beginning to test protected methods that are implied in public methods of class

--------------------------------------------------------------------------------


3 re-inserted into list
Current length = 4
5 inserted into list
New length = 5
Expand list successful

--------------------------------------------------------------------------------

List has 5 elements.
3 keys removed. List has 2 elements.
List shrunk succcessfully
Begin to test operators

--------------------------------------------------------------------------------


List 1                  List2
Item 0 contains key 1   = Item 0 contains key 1
Item 1 contains key 2   = Item 1 contains key 2

If above numbers match, test of Operator= successful.

--------------------------------------------------------------------------------

List 1                  List2
Item 0 contains key 1   = Item 0 contains key 1
Item 1 contains key 2   = Item 1 contains key 2
Operator== tested successfully.


--------------------------------------------------------------------------------

List 1                  List2
Item 0 contains key 1   = Item 0 contains key 2
Item 1 contains key 4   = Item 1 contains key 3
Operator!= tested successfully.

--------------------------------------------------------------------------------

The two lists to join are as follows:
List 1                  List2
Item 0 contains key 1   = Item 0 contains key 2
Item 1 contains key 4   = Item 1 contains key 3
= Item 2 contains key 4

The only key in the new list should be 4
Item 0 contains key 4
If the above key matches, Operator* successful.
--------------------------------------------------------------------------------

The two lists to merge are as follows:
List 1                  List2
Item 0 contains key 4   = Item 0 contains key 2
Item 1 contains key 5   = Item 1 contains key 3
= Item 2 contains key 4

Item 0 contains key 2
Item 1 contains key 3
Item 2 contains key 4
Item 3 contains key 5
If the above key matches, Operator+ successful.

--------------------------------------------------------------------------------


All Tests Complete
Press any key to continue . . .
*/