//******************************************************************
// IMPLEMENTATION FILE (list.cpp)
// This file implements the List class member functions
// List representation: a one-dimensional array and a length
//                      variable
//******************************************************************
#include "ParticleListClass.h"
/*
Private members of class:

ItemType values[MAX_LENGTH];	//stores the items in the list
int length;						//  of values currently in the list
int currPos;					//position of current element

*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ParticleListClass::ParticleListClass()		//default constructor 
{

	length = 0;
	currPos = 0;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool ParticleListClass::IsFull() const
{

	if (length == MAX_LIST_SIZE)  // is the list full?
		return true;
	else
		return false;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ParticleListClass::Insert(/*in*/ PartType item)// Item to be inserted
{

	if (length < MAX_LIST_SIZE)	// if there is room?
	{
		list[length] = item;  // insert it
		length++;
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ParticleListClass::Find(/*in*/LocationRec loc)//Item to be found
{

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		// If found
		if (list[ind].currLoc.row == loc.row && list[ind].currLoc.col == loc.col)
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	return false;				//not found

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ParticleListClass::FindNext(/*in*/LocationRec loc)//Item to be found
{
	int ind = currPos + 1;

	while (ind < length)			// while more items to look at
	{
		// If found
		if (list[ind].currLoc.row == loc.row && list[ind].currLoc.col == loc.col)
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	return false;				//not found

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ParticleListClass::Delete()
{
	length--;

	list[currPos] = list[length];

	/*for(int ind = currPos; ind < length - 1; ind++)     //shuffle up to delete
	list[ind] = list[ind+1];

	length--;*/
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ParticleListClass::FirstPosition()
{

	currPos = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ParticleListClass::NextPosition()
{

	currPos++;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ParticleListClass::EndOfList() const
{

	return (currPos == length - 1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PartType ParticleListClass::Retrieve() const
{

	return list[currPos];
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ParticleListClass ParticleListClass:: operator = (/*in*/ const ParticleListClass& orig) // list to be copied
{
	length = orig.length;					//copy length

	for (int ind = 0; ind < length; ind++)	//iterate thru original
		list[ind] = orig.list[ind];			//copy item

	currPos = orig.currPos;					//copy currpos

	return *this;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int ParticleListClass::ReturnLength() const
{
	return length;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ParticleListClass::UpdateItem(PartType item)	// updated item
{
	list[currPos] = item;
}
