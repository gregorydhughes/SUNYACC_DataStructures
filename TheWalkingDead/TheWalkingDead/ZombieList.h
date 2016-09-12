// Author: Gregory D Hughes
// Date: September 30th 2014
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
//\\//\\//\\//\\//\\//\\//\\//\Summary of Methods\//\\//\\//\\//\\//\\//\\//\\//

// ListClass() 
//		-- initializes list object

// IsEmpty()   
//		-- indicates whether or not the list is empty

// IsFull()    
//		-- indicates whether or not the list is full

// Insert(ItemType item)  
//		-- Inserts the speicifed item at the end of the list

// Find(ZombieRec item)
//		-- Finds a record in the list that matches

// Find(LocationRec loc)
//		-- Find the first item in the list at location

// FindNext(LocationRec loc)
//		-- Finds the next item(s) in the list after Find(loc) has been called

// Delete()    
//		--Deletes the item specified by currPos

// FirstPosition() 
//		-- moves currpos to the beginning of the list

// NextPosition()  
//		-- moves currPos to the next postion in the list

// EndOfList()     
//		-- determines if currPos is at the tend of the list

// Retrieve()      
//		-- returns the list element specified by currPos

// IsZombieLivingDead() 
//		-- Returns whether a zombie is still active

// SetZombieStrength(int newStrength, int battleRound)
//		-- Sets the strength for a zombie, can also kill zombie if new strength 
//			is 0

// KillZombie(int battleRound) -- Never used in client - Omitted

// GetNumZombies()
//		-- Returns the number of active zombies

// AddDeadHuman(int playerID)
//		-- Adds a dead player to the dead player list

// GetHumanKillCount()
//		-- Returns the number of players a particular zombie has killed

// AddBitenHuman(int playerID)
//		-- Adds a player to the bite list

// GetHumanBiteCount()
//		-- Returns the number of bites a zombie has taken on the human populus

// operator =      
//		-- allows aggregate assignment of list objects

// ReturnLength()  
//		-- provides the number of items in the list

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

#ifndef ZOMBIELIST_H
#define ZOMBIELIST_H

#include "zombie.h"	// for list record

//const int MAX_LENGTH = 125;		//maximum # of slots in the list

//simple data type for testing of methods
typedef ZombieRec ZombieArr[MAX_LENGTH];	

class ZListClass
{

public:
	ZListClass();			//default constructor 
	//Pre:		List has been instantiated
	//Post:		list's length is 0

	bool IsEmpty() const;
	//Pre:		List has been instantiated
	//Post:		Returns true if list is empty and false, otherwise


	bool IsFull() const;
	//Pre:		List has been instantiated
	//Post:		Returns true if list is full and false, otherwise

	void Insert(ZombieRec item);	//item to be added
	//Pre:		List is not full
	//Post:		item has been inserted at the end of the current list
	
	bool Find(ZombieRec item);// item to be found
	//Pre:		item is assigned a value
	//Post:		If item is in the list at with a matching zombie Number then	\
					true is returned and currPos contains the index of the		\
					occurence of item in the list, otherwise, false is returned	\
					 and currPos is at zero.

	bool Find(LocationRec loc);// item to be found
	//Pre:		item is assigned a value
	//Post:		If item is in the list at the determined postion then true is	\
					returned and currPos contains the index of the 1st occurence\
					of item in the list, otherwise, false is returned and		\
					currPos is at zero.

	bool FindNext(LocationRec loc); // item to be found after find(loc) has been\
										called
	//Pre:		Find(loc) has been called
	//Post:		If item is in the list after an item at the same location has	\
					been found then true is returned and currPos contains the	\
					index of the 1st occurence of item in the list, otherwise,	\
					false is returned and currPos is at zero.


	void  Delete();
	//Pre:		Method Find has been called to find the item to delete, and the	\
					that item is in the list.CurrPos now points at the item to	\
					be deleted
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

	ZombieRec Retrieve() const;
	//Pre:		EndOfList is false
	//Post:		Returns the item at currPos

	bool IsZombieLivingDead() const;
	//Pre:		Correct zombie in list is found
	//Post:		Zombie boolean expression of living-dead status is returned to	\
				caller

	void SetZombieStrength(int newStrength, int battleRound);
	//Pre:		Correct zombie in list is found
	//Post:		Number of strenghth a zombie has is set

	//Never used in client - Omitted
	//void KillZombie(int battleRound);
	////
	////

	int GetNumZombies() const;
	//Pre:		Correct zombie in list is found	
	//Post:		The number of active zombies is returned to client

	void AddDeadHuman(int playerID);
	//Pre:		Correct zombie in list is found
	//Post:		The player a zombie kills is added to list

	int GetHumanKillCount() const; 
	//Pre:		Correct zombie in list is found
	//Post:		the number of humans killed is returned

	void AddBitenHuman(int playerID);
	//Pre:		Correct zombie in list is found
	//Post:		Player is added to biten human list

	int GetHumanBiteCount() const;
	//Pre:		Correct zombie in list is found
	//Post:		THe number of biten humans is returned to caller

	virtual ZListClass operator = (const ZListClass& orig);	//list to be copied
	//Pre: Orig contain the list to be copied
	//Post: The applying operator contains a copy of the original list 

	int ReturnLength() const;
	//Pre: List has been instantiates
	//Post: The number of items in the list has been returned


private:
	ZombieArr list;		//stores the items in the list
	int length;			//# of values currently in the list
	int currPos;		//position of current element
	int numZombies;		//active number of zombies
};

#endif