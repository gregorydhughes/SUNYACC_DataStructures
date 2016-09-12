//******************************************************************
// IMPLEMENTATION FILE (list.cpp)
// This file implements the List class member functions
// List representation: a one-dimensional array and a length
//                      variable
//******************************************************************
#include "PlayerListClass.h"
/*
Private members of class:

ItemType values[MAX_LENGTH];	//stores the items in the list
int length;						//  of values currently in the list
int currPos;					//position of current element

*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PlayerListClass::PlayerListClass()		//default constructor 
{

	length = 0;
	currPos = 0;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool PlayerListClass::IsFull() const
{

	if (length == MAX_LIST_SIZE)  // is the list full?
		return true;
	else
		return false;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PlayerListClass::Insert(/*in*/ PlayerType item)// Item to be inserted
{

	if (length < MAX_LIST_SIZE)	// if there is room?
	{
		list[length] = item;  // insert it
		length++;
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool PlayerListClass::Find(/*in*/PlayerType item)//Item to be found
{

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		if (list[ind].playerID == item.playerID)	// if found 
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	return false;				//not found

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PlayerListClass::Delete()
{
	//length--;

	//list[currPos] = list[length];
	
	//shuffle up to delete
	for(int ind = currPos; ind < length - 1; ind++)     
		list[ind] = list[ind + 1];

	length--;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PlayerListClass::FirstPosition()
{

	currPos = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PlayerListClass::NextPosition()
{

	currPos++;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool PlayerListClass::EndOfList() const
{

	return (currPos == length - 1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PlayerType PlayerListClass::Retrieve() const
{

	return list[currPos];
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PlayerListClass PlayerListClass:: operator = (/*in*/ const PlayerListClass& orig) // list to be copied
{
	length = orig.length;					//copy length

	for (int ind = 0; ind < length; ind++)	//iterate thru original
		list[ind] = orig.list[ind];			//copy item

	currPos = orig.currPos;					//copy currpos

	return *this;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int PlayerListClass::ReturnLength() const
{
	return length;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PlayerListClass::UpdateItem(PlayerType item)	// Item to update ay currPos
{
	list[currPos] = item;
}