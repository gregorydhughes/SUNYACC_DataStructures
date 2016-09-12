//******************************************************************
// IMPLEMENTATION FILE (HumanList.cpp)
// This file implements the HList class member functions
// List representation: a one-dimensional array and a length
//                      variable
//******************************************************************

#include "HumanList.h"

/*
Private members of class:

HumanArr list;			// stores the items in the list
int length;				// # of values currently in the list
int currPos;			// position of current element
int humansAlive;		// The number of lving players
int posInKillList;		// The position in the killed zombie array

*/

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

HListClass::HListClass()		//default constructor 
{

	length = 0;
	currPos = 0;
	humansAlive = 0;

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool HListClass::IsFull() const
{

	if (length == MAX_LENGTH)  // is the list full?
		return true;
	else
		return false;

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::Insert(/*in*/ HumanRec person)// Item to be inserted
{

	if (length < MAX_LENGTH)	// if there is room?
	{
		list[length] = person;  // insert it

		length++;
		if (person.alive)
			humansAlive++;
	}

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool HListClass::Find(/*in*/HumanRec person)//Item to be found
{

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		if (list[ind].ID == person.ID)	// if found 
		{
			currPos = ind;		//set currpos and return

			return true;
		}
		ind++;
	}

	return false;				//not found

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool HListClass::Find(/*in*/LocationRec loc)//Item to be found @ location
{
	// only one living player can be at a location

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		if (list[ind].loc.row == loc.row && list[ind].loc.col == loc.col)	// if found 
		{
			currPos = ind;		//set currpos and return

			return true;
		}
		ind++;
	}

	return false;				//not found

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool HListClass::Find(playerID ID)// search by player ID
{
	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		if (list[ind].ID == ID)	// if found 
		{
			currPos = ind;		//set currpos and return

			return true;
		}
		ind++;
	}

	return false;				//not found
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::Delete()
{
	length--;
	humansAlive--;

	list[currPos] = list[length];
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::FirstPosition()
{
	currPos = 0;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::NextPosition()
{
	currPos++;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool HListClass::EndOfList() const
{
	return (currPos == length - 1);
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

HumanRec HListClass::Retrieve() const
{
	return list[currPos];
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::SetHumanLocation(LocationRec loc)
{
	list[currPos].loc = loc;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool HListClass::IsHumanAlive()
{
	return list[currPos].alive;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::SetHumanLifeUnits(int lifeUnits, int battleRound)
{
	if (lifeUnits > 0)
	{
		list[currPos].lifeUnits = lifeUnits;
	}
	else
	{
		list[currPos].lifeUnits = 0;
		list[currPos].alive = false;
		list[currPos].roundKilled = battleRound;
		humansAlive--;
	}
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::SetKillerID(int zombieNum)
{
	list[currPos].killerID = zombieNum;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void HListClass::IncreaseBiteCount(int battleRound)
{
	list[currPos].biteCount++;

	if (list[currPos].biteCount == 10)
	{
		list[currPos].alive = false;
		list[currPos].lifeUnits = 0;
		list[currPos].roundKilled = battleRound;
		humansAlive--;
	}

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

int HListClass::HumansRemaining() const
{
	return humansAlive;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\


void HListClass::AddDeadZombie(int zNum)
{
	list[currPos].killList[list[currPos].kills] = zNum;
	list[currPos].kills++;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

HListClass HListClass:: operator = (/*in*/ const HListClass& orig) // list to be copied
{
	length = orig.length;					//copy length

	for (int ind = 0; ind < length; ind++)	//iterate thru original
		list[ind] = orig.list[ind];			//copy item

	currPos = orig.currPos;					//copy currpos

	return *this;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

int HListClass::ReturnLength() const
{
	return length;
}