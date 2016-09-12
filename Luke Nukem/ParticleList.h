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
// Insert(ItemType item)							-- Inserts the speicifed item at the end of the list
// Find(ItemType item)								-- Finds specified item (sets currPos) returns true if 
//														found false otherwise
// Delete()											-- Deletes the item specified by currPos
// FirstPosition()									-- moves currpos to the beginning of the list
// NextPosition()									-- moves currPos to the next postion in the list
// EndOfList()										-- determines if currPos is at the tend of the list
// Retrieve()										-- returns the list element specified by currPos
// operator =										-- allows aggregate assignment of list objects
// ReturnLength()									-- provides the number of items in the list
// SetParticleID(short partID)						-- Sets the current list class item's ID
// GetParticleID()									-- Gets the current list class item's ID
// SetParticleEnergy(short energy)					-- Sets the current list class item's energy
// GetParticleEnergy()								-- Gets the current list class item's energy
// SetCurrentPosition(LocationRec loc)				-- Sets the  current list class item's Location
// GetCurrLoc()										-- Gets the  current list class item's current Location
// GetPrevLoc()										-- Gets the  current list class item's previous Location
// DetermineMultipleVisitSites(Locations& visits)	-- Fills an array with positions that a particle have traveled more than once


#include "Location.h"	// for list record
#include "Particle.h"

//Specification file:  list.h
const int MAX_LENGTH = 125;		//maximum # of slots in the list

//typedef LocationRec ItemType;	//type of item stored in the list	

typedef ParticleRec ItemType;	//simple data teyp for testing of methods

class ListClass
{

public:
	ListClass();			//default constructor 
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

	void Insert(ItemType item);	//item to be added
	//Purpose:	Inserts item into the list
	//Pre:		List is not full
	//Post:		item has been inserted at the end of the current list


	//	PLEASE NOTE::: THIS MOST LIKELY UST BE MODIFIED TO WORK CORRECTLY WITH A LOCATIONREC
	bool Find(ItemType item);// item to be found
	//Purpose:	Determines whether or not item is in the list
	//Pre:		item is assigned a value
	//Post:		If item is in the list then true is returned  and currPos contains
	//				the index of the 1st occurence of item in the list, otherwise, 
	//				false is returned and currPos is at length.

	void  Delete();
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

	ItemType Retrieve() const;
	//Purpose:	Returns the current item in the list
	//Pre:		EndOfList is false
	//Post:		Returns the item at currPos

	virtual ListClass operator = (const ListClass& orig);	//list to be copied
	//Purpose: overloads the = operator so that aggregate assignment is possible
	//Pre: Orig contain the list to be copied
	//Post: The applying operator contains a copy of the original list 

	int ReturnLength() const;
	//Purpose: provides the number of items in the list
	//Pre: List has been instantiated
	//Post: The number of items in the list has been returned

	
	
	void SetParticleID(short partID);
	//Pre: List has been instantiated	
	//Post: A particle's ID is set
	
	short GetParticleID();
	//Pre: List has been instantiated
	//Post:	PArticle ID is returned to client
	
	void SetParticleEnergy(short energy);
	//Pre: List has been instantiated
	//Post: A particles energy is set
	
	short GetParticleEnergy();
	//Pre: List has been instantiated
	//Post: A particle's energy is returned to caller
	
	void SetCurrentPosition(LocationRec loc);
	//Pre: List has been instantiated
	//Post: A particles current and previous position is updated
	
	LocationRec GetCurrLoc();
	//Pre: List has been instantiated
	//Post: The particles current position is returned to caller
	
	LocationRec GetPrevLoc();
	//Pre: List has been instantiated
	//Post: The particles previous position is returned to caller
	
	void DetermineMultipleVisitSites(Locations& visits);
	//Pre: List has been instantiated and the simulation run
	//Post: An array containing a list of locations that a particle has traveled to more than once is returned to caller


private:
	ItemType list[MAX_LENGTH];		//stores the items in the list
	int length;						//# of values currently in the list
	int currPos;					//position of current element

};
