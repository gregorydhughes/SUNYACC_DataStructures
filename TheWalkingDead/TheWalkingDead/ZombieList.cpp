//******************************************************************
// IMPLEMENTATION FILE (ZombieList.cpp)
// This file implements the ZList class member functions
// List representation: a one-dimensional array and a length
//                      variable
//******************************************************************

#include "ZombieList.h"

/*
Private members of class:

ZombieArr list;		//stores the items in the list
int length;			//# of values currently in the list
int currPos;		//position of current element
int numZombies;		//active number of zombies

*/

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

ZListClass::ZListClass()		//default constructor 
{
	length = 0;
	currPos = 0;
	numZombies = 0;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool ZListClass::IsFull() const
{

	if (length == MAX_LENGTH)  // is the list full?
		return true;
	else
		return false;

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::Insert(/*in*/ ZombieRec item)// Item to be inserted
{

	if (length < MAX_LENGTH)	// if there is room?
	{
		list[length] = item;  // insert it

		length++;
		if (item.livingDead)
			numZombies++;
	}

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool ZListClass::Find(/*in*/ZombieRec zom)//Zombie to be found by znum
{

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		// if found 
		if (list[ind].zombieNum == zom.zombieNum && list[ind].livingDead)	
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}
	
	currPos = 0;
	return false;				//not found

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool ZListClass::Find(/*in*/LocationRec loc)//zombie to be found @ location
{

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		if (list[ind].loc.col == loc.col && list[ind].loc.row == loc.row)	// if found 
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	currPos = 0;
	return false;				//not found

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool ZListClass::FindNext(/*in*/LocationRec loc)//zombie to be found @ location
{
	int ind = currPos + 1;

	while (ind < length)			// while more items to look at
	{
		if (list[ind].loc.col == loc.col && list[ind].loc.row == loc.row && list[ind].livingDead)	// if found 
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	currPos = 0;

	return false;				//not found

}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::Delete()
{
	length--;

	numZombies--;

	list[currPos] = list[length];


	/*for(int ind = currPos; ind < length - 1; ind++)     //shuffle up to delete
	list[ind] = list[ind+1];

	length--;*/
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::FirstPosition()
{
	currPos = 0;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::NextPosition()
{
	currPos++;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool ZListClass::EndOfList() const
{
	return (currPos == length - 1);
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

ZombieRec ZListClass::Retrieve() const
{
	return list[currPos];
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

bool ZListClass::IsZombieLivingDead() const
{
	return list[currPos].livingDead;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::SetZombieStrength(/*in*/int newStrength,	// new Strength
								/*in*/int battleRound)		// Round if killed
{
	if (newStrength > 0)
	{
		list[currPos].strength = newStrength;
	}
	else
	{
		list[currPos].strength = 0;
		list[currPos].roundKilled = battleRound;
		list[currPos].livingDead = false;
		numZombies--;
	}
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

//Never used in client - Omitted
//void ZListClass::KillZombie(int battleRound)
//{
//	list[currPos].livingDead = false;
//	list[currPos].roundKilled = battleRound;
//	numZombies--;
//}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

int ZListClass::GetNumZombies() const
{
	return numZombies;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::AddDeadHuman(int playerID)		// PlayerID of dead human to add
{
	list[currPos].killsList[list[currPos].killCount] = playerID;
	list[currPos].killCount++;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

int ZListClass::GetHumanKillCount() const
{
	return list[currPos].killCount;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

void ZListClass::AddBitenHuman(int playerID)	// PlayerID of dead human to add
{
	list[currPos].bitenList[list[currPos].biteCount] = playerID;
	list[currPos].biteCount++;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

int ZListClass::GetHumanBiteCount() const
{
	return list[currPos].biteCount;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

ZListClass ZListClass:: operator = (
							/*in*/ const ZListClass& orig) // list to be copied
{
	length = orig.length;					//copy length

	for (int ind = 0; ind < length; ind++)	//iterate thru original
		list[ind] = orig.list[ind];			//copy item

	currPos = orig.currPos;					//copy currpos

	return *this;
}

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

int ZListClass::ReturnLength() const
{
	return length;
}
