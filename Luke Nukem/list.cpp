//******************************************************************
// IMPLEMENTATION FILE (list.cpp)
// This file implements the List class member functions
// List representation: a one-dimensional array and a length
//                      variable
//******************************************************************
#include "list.h"
/*
Private members of class:

ItemType values[MAX_LENGTH];	//stores the items in the list
int length;						//  of values currently in the list
int currPos;					//position of current element

*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ListClass::ListClass()		//default constructor 
{

	length = 0;
	currPos = 0;

}
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

bool ListClass:: IsFull() const
{
	
	if(length == MAX_LENGTH)  // is the list full?
		return true;
	else
		return false;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass:: Insert(/*in*/ ItemType item)// Item to be inserted
{
	
	if(length < MAX_LENGTH)	// if there is room?
	{
		list[length] = item;  // insert it
		length++;
	}

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass::Find(/*in*/ItemType item)//Item to be found
{
	
	int ind = 0;


	while(ind < length)			// while more items to look at
	{
		if(list[ind] == item)	// if found 
		{
			currPos = ind;		//set currpos and return 
			return true;
		}
		ind++;
	}

	return false;				//not found

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::Delete()
{
	length--;
		
	list[currPos] = list[length];

	/*for(int ind = currPos; ind < length - 1; ind++)     //shuffle up to delete
		list[ind] = list[ind+1];
	
	length--;*/
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::FirstPosition()
{
	
	currPos = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ListClass::NextPosition()
{
	
	currPos++;

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool ListClass::EndOfList() const
{
	
	return (currPos == length-1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ItemType ListClass::Retrieve() const
{
	
	return list[currPos];
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ListClass ListClass:: operator = (/*in*/ const ListClass& orig) // list to be copied
{	
	length = orig.length;					//copy length

	for(int ind = 0; ind < length; ind++)	//iterate thru original
		list[ind] = orig.list[ind];			//copy item

	currPos = orig.currPos;					//copy currpos

	return *this;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int ListClass::ReturnLength() const
{
	return length;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~