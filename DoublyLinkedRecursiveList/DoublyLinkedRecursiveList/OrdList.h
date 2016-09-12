//*************************************************************************************************
//										SPECIFICATION FILE
/*
Date: 04/10/2015
Author: Luke Musto
Project: Doubly Linked Recursive List
Filename: OrdList.h
Purpose: This file contains the specification for an ascending Ordered List Class. The list is implemented 
		 with a  doubly linked structure, and uses recursion to access and modify elements in the list.
		 Insert, Delete, Clear, Retrieve, Print, and PrintReverse, are wrapper methods for their
		 recursive counterparts. The class containts 8 public methods, 3 overloaded operators, 7 protected methods, 
		 copy constructor and destructor.
		 
Assumptions: 1) KeyType is defined as the a programmer defined data type and is used to order the list. 
			 2) Relational operators are defined on the primitive datatype that is typedefined as KeyType
		 	 3) ItemType is defined to contain a field named key which is defined of type KeyType
			 4) The list cannot hold elements with duplicate keys.
			 5) The list is sorted in ascending order.
			 
Exceptions Thrown: DuplicateKeyException -- Thrown when client tries to insert an already existing key.
				   OutOfMemoryException -- Thrown when client tries to insert and there is no
										  memory remaining.
				   KeyNotThereException -- Thrown when client tries to delete or retrieve a non-existent key.

//*************************************************************************************************
//										Summary of Methods
public:
	OrdListClass() -- Default Constructor. Points tail to nullptr.
	~OrdListClass() -- Destructor. Calls Clear().
	OrdListClass(const OrdListClass& orig) -- Copy Constructor. Instantiates an OrdList object as a
			deep copy of orig.
	bool IsFull() -- Determines if the list is full.
	bool IsEmpty() -- Determines if the list is empty
	void Insert(ItemType newItem) -- Wrapper method for rInsert().
	void Delete(KeyType target) -- Wrapper method for rDelete().
	void Clear() -- Wrapper method for rClear().
	ItemType Retrieve(KeyType target) -- Wrapper method for rRetrieve().
	void Print() -- Wrapper method for rPrint().
	void PrintReverse() -- Wrapper method for rPrintRev().
	virtual void operator =(const OrdListClass& orig) -- Performs a deep copy of orig.
	virtual OrdListClass operator +(const OrdListClass& rtOp) -- Returns an OrdList object containing 
			the union of rtOp and the applying object. 
	virtual OrdListClass operator -(const OrdListClass& rtOp) -- Returns an OrdList object containing
			all elements in the applying object that are not in rtOp.
	
protected:
	node* Allocate() -- Allocates memory for a new node in the list.
	void rPrint(const node* trav) -- Recursively prints the list in ascending order.
	void rPrintRev(const node* trav) -- Recursively prints the list in descending order.
	void rClear(node* trav) -- Uses recursion to remove every element from the list.
	void rDelete(node* trav, KeyType target) -- Recursively finds target, deleting it from the list.
	void rInsert(node* trav, ItemType newItem) -- Recursively finds the position to place new item and
			inserts it in the list.
	void rRetrieve(node* trav, ItemType tbr) -- Recursively finds the requested item and copies it into tbr.
*/
//*************************************************************************************************
// Included Libraries
#include "ItemType.h"	// Struct for element data.
#include "Exceptions.h" // Exceptions encountered in OrdList methods.
#include <iostream>		// For Print and PrintRev.
using namespace std;



// Forward declaration of node struct
struct node;



class OrdListClass
{
	public: 
	
// ------------------------------------------------------------------------------------------------
// |																							  |
// |								Constructors & Destructors									  |
// |																							  |
// ------------------------------------------------------------------------------------------------
		
		// O(1)			Default Constructor
		OrdListClass();
		/*
		Purpose: Instantiates a new class object.
		Pre: n/a
		Post: Object has been instantiated and tail points to nullptr.
		*/

		// O(N)			Destructor
		~OrdListClass();
		/*
		Purpose: Frees the dynamic memory allocated during the life of the object.
		Pre: Object exists.
		Post: All nodes have been deleted and tail points to nullptr.
		*/

		// O(N)			Copy Constructor
		OrdListClass(/*in*/ const OrdListClass& orig); // List to be copied.
		/*
		Purpose: Instantiates a new class object as a deep copy of orig.
		Pre: Both orig and applying object exist.
		Post: Applying object contains copies of all elements in orig.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Predicators									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(1)
		bool IsFull() const;
		/*
		Purpose: Determines if the list is full.
		Pre: Object exists.
		Post: Returns false, as list will only be full if memory has filled.
		*/

		// O(1)
		bool IsEmpty() const;
		/*
		Purpose: Determines if list is empty.
		Pre: Object exists.
		Post: Returns true if tail == nullptr, false otherwise.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |										Mutators											  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		void Insert(/*in*/ ItemType newItem); // Item to be inserted.
		/*
		Purpose: Wrapper method for rInsert().
		Pre: List object exists.
		Post: rInsert() has been called.
		*/

		// O(N)
		void Delete(/*in*/ KeyType target); // Key of item to delete.
		/*
		Purpose: Wrapper method for rDelete().
		Pre: List Object exists.
		Post: if list is not empty, rDelete() is called. Otherwise, KeyNotThereException is thrown.
		Exceptions Thrown: KeyNotThereException.
		*/

		// O(N)
		void Clear();
		/*
		Purpose: Wrapper method for rClear().
		Pre: List object exists.
		Post: rClear() has been called.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Accessor										  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		ItemType Retrieve(/*in*/ KeyType target) const; // Key of item to be returned.
		/*
		Purpose: Wrapper method for rRetrieve().
		Pre: List object exists.
		Post: rRetrieve() has been called if list is not empty. Otherwise, KeyNotThereException is thrown.
		Exceptions Thrown: KeyNotThereException.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Summarizers									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		void Print() const;       
		/*
		Purpose: Wrapper method for rPrint().
		Pre: List object exists
		Post: rPrint() has been called.
		*/

		// O(N)
		void PrintReverse() const;
		/*
		Purpose: Wrapper method for rPrintRev().
		Pre: List object exists
		Post: rPrintRev() has been called.
		*/

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Overloaded Operators									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		virtual void operator =(/*in*/ const OrdListClass& orig);	// List to be copied.
		/*
		Purpose: Performs a deep copy of orig, storing it in the applying object.
		Pre: Both objects have been instantiated.
		Post: the applying object will contain copies of all the elements in orig.
		*/

		// O(N + M)
		virtual OrdListClass operator +(/*in*/ const OrdListClass& rtOp) const; // List to be added to applying object.
		/*
		Purpose: Combines rtOp and the applying object. Any items that appear in both lists
				 only appear once in the returned list.
		Pre: Both objects exist.
		Post: The union of the two ordered lists will be returned. If the union of the two lists exceeds available memory,
			  an exception will be thrown.
		*/

		// O(N + M)
		virtual OrdListClass operator -(/*in*/ const OrdListClass& rtOp) const; // List to be subtracted from applying object.
		/*
		Purpose: Subtracts rtOp from applying object, removing all elements that appear
				 in both lists from the applying object.
		Pre: Both objects exist.
		Post: A list containing the result of the subtraction will be returned.
		*/

		

	private:	
		// PDM's
		node* head;
		node* tail;	



	protected:  
// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Recursive (Wrapped) Methods								  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		// O(N)
		node* Allocate();
		/*
		Purpose: Allocates a new node for the list.
		Pre: Object exists.
		Post: If memory is available, a newly allocated node will be returned. If not,
			  InsertFullException will be thrown.
		Exceptions Thrown: InsertFullException.
		*/
		
		// O(N)
		void rPrint(/*in*/ const node* trav) const; // Pointer to travent node in ordList
		/*
		Purpose: Prints the list in ascending order, from head to tail.
		Pre: OrdList object exists.
		Post: List has been printed to the screen.
		*/

		// O(N)
		void rPrintRev(/*in*/ const node* trav) const; // Pointer to travent node in ordList
		/*
		Purpose: Prints the list in reverse order, from tail to head.
		Pre: OrdList object exists.
		Post: List has been printed to the screen.
		*/

		// O(N)
		void rClear(/*in*/ node* trav); // Pointer to travent node in ordList
		/*
		Purpose: Clears the list.
		Pre: OrdList object exists.
		Post: All elements have been deleted and tail points to nullptr.
		*/

		// O(N)
		void rDelete(/*in*/ node* trav,			// Pointer to travent node in ordList
				 	 /*in*/ KeyType target);	// Target key to be deleted.
		/*
		Purpose: Deletes an item from the list.
		Pre: OrdList object exists.
		Post: If target item is found, it will be deleted. Otherwise, KeyNotThereException
			  will be thrown.
		Exceptions Thrown: KeyNotThereException
		*/

		// O(N)
		void rInsert(/*in*/ node* trav,			// Pointer to travent node in ordList
					 /*in*/ ItemType newItem);	// Item to be inserted.
		/*
		Purpose: Inserts an item to the list object, maintaining order.
		Pre: OrdList object exists.
		Post: If item is not already in the list, it will be inserted in the correct position.
			  If it is already in the list, DuplicateKeyException will be thrown.
		Exceptions Thrown: DuplicateKeyException
		*/

		// O(N)
		void rRetrieve(/*in*/ node* trav,				// Pointer to travent node in ordList
					   /*in/out*/ ItemType& tbr,		// Item to be returned.
					   /*in*/ KeyType target) const;	// Requested key to be retrieved.
		/*
		Purpose: Retrieves the requested element, specified by target.
		Pre: Object exists.
		Post: If the key is in the list, the item will be returned. Otherwise, KeyNotThereException
			  will be thrown. 
		Exceptions Thrown: KeyNotThereException
		*/

};

