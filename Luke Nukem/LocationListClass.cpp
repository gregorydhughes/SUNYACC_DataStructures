#include "LocationListClass.h"

/*
Private members of class:

ItemType values[MAX_LENGTH];	//stores the items in the list
int length;						//  of values currently in the list
int currPos;					//position of current element

*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LocationListClass::LocationListClass()		//default constructor 
{

	length = 0;
	currPos = 0;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool LocationListClass::IsEmpty() const
{

	if (length == 0)  // is the list full?
		return true;
	else
		return false;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool LocationListClass::IsFull() const
{

	if (length == MAX_LIST_SIZE)  // is the list full?
		return true;
	else
		return false;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LocationListClass::Insert(/*in*/ LocType item)// Item to be inserted
{

	if (length < MAX_LIST_SIZE)	// if there is room?
	{
		if (Find(item))			// Does the item already exist in the list?
			list[currPos].timesVisited++;
		else
		{
			list[length] = item;  // if not insert it
			list[length].timesVisited = 1;
			length++;
		}
	}
	// else there is no room

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool LocationListClass::Find(/*in*/LocType item)//Item to be found
{

	int ind = 0;


	while (ind < length)			// while more items to look at
	{
		if (list[ind].row == item.row && list[ind].col == item.col)	// if found 
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	return false;				//not found

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LocationListClass::Delete()
{
	//length--;

	//list[currPos] = list[length];

	for (int ind = currPos; ind < length - 1; ind++)     //shuffle up to delete
	{
		list[ind] = list[ind + 1];
	}

	length--;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LocationListClass::FirstPosition()
{

	currPos = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LocationListClass::NextPosition()
{

	currPos++;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool LocationListClass::EndOfList() const
{

	return (currPos == length - 1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LocType LocationListClass::Retrieve() const
{

	return list[currPos];
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LocationListClass LocationListClass:: operator = (/*in*/ const LocationListClass& orig) // list to be copied
{
	length = orig.length;					//copy length

	for (int ind = 0; ind < length; ind++)	//iterate thru original
		list[ind] = orig.list[ind];			//copy item

	currPos = orig.currPos;					//copy currpos

	return *this;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int LocationListClass::ReturnLength() const
{
	return length;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

LocationListClass LocationListClass::DetermineMultipleVisitSites()
{
	// List to return
	LocationListClass ans;

	// for all items in the list determine locations of multiple visits
	for (int i = 0; i < length; i++)
	{
		if (list[i].timesVisited > 1)
			ans.InsertTrue(list[i]);
	}

	return ans;
}

void LocationListClass::InsertTrue(/*in*/ LocType item)// Item to be inserted
{

	if (length < MAX_LIST_SIZE)	// if there is room?
	{
		list[length] = item;  // insert it
		length++;
	}

}