#ifndef LOCATIONLISTCLASS_H
#define LOCATIONLISTCLASS_H
#include "Location.h"

//Author: Luke Musto
//Date: 9/19/2012
//Purpose: This specification contains the basis for an unordered list class. 
//It currently contains a maximum of 125 elements. It allows for list
//insertions, deletions, and looks ups. It contains 12 public methods and 
//3 private data members. A summary of the public methods appears below.
// 
//Assumptions:
//	List can contain a maximum of 125 elements
//
//Error Handling: None
//
//************************************************************Summary of Methods**************************************************************
// ListClass()										-- initializes list object
// IsEmpty()										-- indicates whether or not the list is empty
// IsFull()											-- indicates whether or not the list is full
// Insert(LocType item)								-- Inserts the speicifed item at the end of the list, 
//														or increases the count of a location traveled
// Find(LocType item)								-- Finds specified item (sets currPos) returns true if 
//														found false otherwise
// Delete()											-- Deletes the item specified by currPos
// FirstPosition()									-- moves currpos to the beginning of the list
// NextPosition()									-- moves currPos to the next postion in the list
// EndOfList()										-- determines if currPos is at the tend of the list
// Retrieve()										-- returns the list element specified by currPos
// operator =										-- allows aggregate assignment of list objects
// ReturnLength()									-- provides the number of items in the list
// DetermineMultipleVisitSites(Locations& visits)	-- Fills an array with positions that a particle have traveled more than once
// InsertTrue(LocType item)							-- Inserts the specified item at the end of a list

#include "Location.h"	// for list record

//Specification file:  list.h

typedef LocationRec LocType;	//simple data teyp for testing of methods

class LocationListClass
{

public:
	LocationListClass();			//default constructor 
	//Purpose:  Initializes a list object to an empty list
	//Pre:		List has been instantiated
	//Post:		list's length is 0

	bool IsEmpty() const;
	//Purpose:	Indicates whether or not the list is empty
	//Pre:		List has been instantiated
	//Post:		Returns true if list is empty and false, otherwise


	bool IsFull() const;
	//Purpose:	Indicates whether or not the list is full
	//Pre:		List has been instantiated
	//Post:		Returns true if list is full and false, otherwise

	void Insert(LocType item);	//item to be added
	//Purpose:	Inserts item into the list
	//Pre:		List is not full
	//Post:		item has been inserted at the end of the current list or 
	//			the count of a location a particle has traveled to has been increased


	//	PLEASE NOTE::: THIS MOST LIKELY UST BE MODIFIED TO WORK CORRECTLY WITH A LOCATIONREC
	bool Find(LocType item);// item to be found
	//Purpose:	Determines whether or not item is in the list
	//Pre:		item is assigned a value
	//Post:		If item is in the list then true is returned  and currPos contains
	//				the index of the 1st occurence of item in the list, otherwise, 
	//				false is returned and currPos is at length.

	void Delete();
	//Purpose:  Deletes an item from the list
	//Pre:		Method Find has been called to find the item to delete, and the 
	//				that item is in the list.CurrPos now points at the item to be deleted
	//Post:		The 1st occurrence of item has been deleted from the list

	void FirstPosition();
	//Purpose:  Moves to the beginning of the list
	//Pre:		List has been instantiated
	//Post:		currPos is 0

	void NextPosition();
	//Purpose:	Moves to the next element in the list
	//Pre:		List has been instantiated
	//Post:		currPos has been incremented by 1

	bool EndOfList() const;
	//Purpose:	Determines if at the end of the list
	//Pre:		List has been instantiated
	//Post:		Returns true if at the end of the list, and false, otherwise

	LocType Retrieve() const;
	//Purpose:	Returns the current item in the list
	//Pre:		EndOfList is false
	//Post:		Returns the item at currPos

	virtual LocationListClass operator = (const LocationListClass& orig);	//list to be copied
	//Purpose: overloads the = operator so that aggregate assignment is possible
	//Pre: Orig contain the list to be copied
	//Post: The applying operator contains a copy of the original list 

	int ReturnLength() const;
	//Purpose: provides the number of items in the list
	//Pre: List has been instantiated
	//Post: The number of items in the list has been returned

	LocationListClass DetermineMultipleVisitSites();
	//Pre: List has been instantiated and the simulation run
	//Post: An array containing a list of locations that a particle has traveled to more than once is returned to caller

private:
	void InsertTrue(LocType item);	//item to be added
	//Purpose:	Inserts item into the list
	//Pre:		List is not full
	//Post:		item has been inserted at the end of the current list

	LocType list[MAX_LIST_SIZE];		//stores the items in the list
	int length;						//# of values currently in the list
	int currPos;					//position of current element

};
#endif