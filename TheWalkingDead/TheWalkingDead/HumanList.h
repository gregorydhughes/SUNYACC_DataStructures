// Author: Gregory D Hughes
// Date: October 14th 2014
//Purpose: This specification contains the basis for an unordered list class. 
//It currently contains a maximum of 125 elements. It allows for list
//insertions, deletions, and looks ups. It contains 20 public methods and 
//5 private data members. A summary of the public methods appears below.
// 
//Assumptions:
//	List can contain a maximum of 125 elements
//
//Error Handling: None


//\\//\\//\\//\\//\\//\\//\\//\Summary of Methods\//\\//\\//\\//\\//\\//\\//\\//

// ListClass()
//		-- initializes list object

// IsEmpty()				
//		-- indicates whether or not the list is empty

// IsFull()					
//		-- indicates whether or not the list is full

// Insert(ItemType item)	
//		-- Inserts the speicifed item at the end of the list

// Find(humanRec person)	
//		-- Finds specified player (sets currPos) returns true if found false	\
			otherwise

//Find(PlayerID ID)			
//		-- Finds specified player by playerID (sets currPos) returns true if	\
			found false otherwise

//Find(LocationRec Loc)		
//		-- Finds specified player at a Location (sets currPos) returns true	if	\
			found false otherwise

//Delete()					
//		--Deletes the item specified by currPos

//FirstPosition()			
//		-- moves currpos to the beginning of the list

//NextPosition()			
//		-- moves currPos to the next postion in the list

//EndOfList()				
//		-- determines if currPos is at the tend of the list

//Retrieve()				
//		-- returns the list element specified by currPos

//SetHumanLocation(LocationRec loc)		
//		-- Sets the Location for a player

//IncreaseBiteCount(int battleRound)	
//		-- Increses the number of bites a human has sustained

//IsHumanAlive()						
//		-- Returns a boolean expression based on whether player is alive

//SetHumanLifeUnits(int lifeUnits, int battleRound)
//		-- Sets the number of life units a player has remaining

//SetKillerID(int zombieNum)
//		-- Sets the Is of the zombie which kills the current player

//HumansRemaining()
//		-- Returns the number of humans that are alive

//operator =      
//		-- allows aggregate assignment of list objects

// ReturnLength()  
//		-- provides the number of items in the list

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

#ifndef HUMANLIST_H
#define HUMANLIST_H

#include "human.h"	// for list record

//const int MAX_LENGTH = 125;		//maximum # of slots in the list

//simple data type for testing of methods
typedef	HumanRec HumanArr[MAX_LENGTH];

class HListClass
{

public:
	HListClass();			//default constructor 
	//Pre:		List has been instantiated
	//Post:		list's length is 0

	bool IsEmpty() const;
	//Pre:		List has been instantiated
	//Post:		Returns true if list is empty and false, otherwise


	bool IsFull() const;
	//Pre:		List has been instantiated
	//Post:		Returns true if list is full and false, otherwise

	void Insert(HumanRec person);	//item to be added
	//Pre:		List is not full
	//Post:		item has been inserted at the end of the current list

	bool Find(HumanRec person);// item to be found
	//Pre:		item is assigned a value
	//Post:		If item is in the list then true is returned  and currPos 
	//				contains the index of the 1st occurence of item in the list, 
	//				otherwise, false is returned and currPos is at it's original
	//				position.

	bool Find(LocationRec loc);
	//Pre:		Location has been defined a value
	//Post:		If player found at location true is returned and currPos is set 
	//				to the index of the player on location, otherwise false is 
	//				returned and currPos remains at its original position

	bool Find(playerID ID);
	//Pre:		ID has been defined a playerID(int)
	//Post:		If player found in the list true is reutrned and currPos contains
	//				the index of the player, otherwise false is returned and currPos
	//				remains in its original position

	void  Delete();
	//Pre:		Method Find has been called to find the item to delete, and the 
	//				that item is in the list.CurrPos now points at the item to be 
	//				deleted
	//Post:		The 1st occurrence of item has been deleted from the list

	void FirstPosition();
	//Pre:		List has been instantiated
	//Post:		currPos is 0

	void NextPosition();
	//Pre:		List has been instantiated
	//Post:		currPos has been incremented by 1

	bool EndOfList() const;
	//Pre:		List has been instantiated
	//Post:		Returns true if at the end of the list, and false, otherwise

	HumanRec Retrieve() const;
	//Pre:		EndOfList is false
	//Post:		Returns the item at currPos

	void SetHumanLocation(LocationRec loc);
	//Pre:		Correct player in list is found
	//Post:		Player location is set

	void IncreaseBiteCount(int battleRound);
	//Pre:		Correct player in list is found		
	//Post:		Player number of bites ins incremented

	bool IsHumanAlive();
	//Pre:		Correct player in list is found
	//Post:		Player boolean expression of life is returned to caller

	void SetHumanLifeUnits(int lifeUnits, int battleRound);
	//Pre:		Correct player in list is found
	//Post:		Number of life units a player has is set

	void SetKillerID(int zombieNum);
	//Pre:		Correct player in list is found
	//Post:		Player Killer is set

	int HumansRemaining() const;
	//Pre:		List has been instantiated
	//Post:		Returns the nubmber of living players to client

	void HListClass::AddDeadZombie(int zNum);
	//Pre:		Correct player in list is found
	//Post:		The number of living players is returned to caller

	virtual HListClass operator = (const HListClass& orig);	//list to be copied
	//Pre:		Orig contain the list to be copied
	//Post:		The applying operator contains a copy of the original list 

	int ReturnLength() const;
	//Pre:		List has been instantiates
	//Post:		The number of items in the list has been returned


private:
	HumanArr list;			// stores the items in the list
	int length;				// # of values currently in the list
	int currPos;			// position of current element
	int humansAlive;		// The number of lving players
};

#endif