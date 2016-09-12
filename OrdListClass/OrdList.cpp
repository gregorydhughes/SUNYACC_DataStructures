#include "OrdList.h"

OrdListClass::OrdListClass()
{}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OrdListClass::IsFull() const
// returns true if list is full, false otherwise
// overridden to ensure functionality of existing client code, list now expands)
//Pre: list has been instantiated
//Post: false has been returned
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OrdListClass::Find(/* in */KeyType key)						// key to search for
//finds position of key within the OrdList. 
//Pre: target contains a keyType value to search OrdList for. 
//Post: If target is found within the OrdList, true is returned and 
//      currPos is set to the elements location in the list. If target is 
//      not found, false is returned and currPos is set to the 
//      location where the element would have appeared had it been in the 
//      List. 
{
	// if the lsit is empty set currpos to 0 and return false, the item is not here
	if (IsEmpty())
	{
		SetCurrPos(0);
		return false;
	}

	// integers to hold first, middle and last positions for binary search
	int frst, mddl, last;

	// initialize values
	frst = 0;
	last = GetLength() - 1;

	mddl = (frst + last) / 2;

	// set the first currPos
	SetCurrPos(mddl);

	// just worry about finding the key first
	while (frst <= last)
	{
		// If the keys match keep currPos and return true
		if (Retrieve().key == key)
			return true;
		// if key is less than current, search lower list
		else if (key < Retrieve().key)
		{
			// Modify LCV
			last = mddl - 1;
			mddl = (frst + last) / 2;
		}
		// else key is greater than current, search upper list
		else
		{
			// Modify lcv
			frst = mddl + 1;
			mddl = (frst + last) / 2;
		}

		// set currPos to the new mid point
		SetCurrPos(mddl);
	}

	// based on where currPos is we can determine where to insert the next key if that was the intension of the call

	// get a temporary list to find the best position for an insertion
	ItemType* tempList = GetListPtr();

	// find the best position for key
	while (key > tempList[mddl].key && mddl < GetLength())
	{
		// Modify LCV
		mddl++;
	}

	// Set currPos to the best position
	SetCurrPos(mddl);

	return false;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrdListClass::Insert(/* in */ ItemType target)				//target to insert
//inserts target into OrdList at position specified by PDM currPos. 
//Pre: currPos contains location at which to insert new element; 
//			where (0 <= currPos <= length) 
//Post: target has been inserted into the OrdList at the location specified by currPos. 
//		if list was full prior to insertion, list will now contain twice as many elements
{
	// if there is no room in the list expand
	if (NoRoom())
		Expand();

	// if the item is not found in list insert it
	if (!Find(target.key))
	{
		ItemType* tempList;		// pointer to point to the list

		// get the position of the list in memory
		tempList = GetListPtr();

		// if there are elements within the list
		if (!IsEmpty())
		{
			// if the length is equal to 1
			if (GetLength() == 1)
			{
				// see if the key should be inserted before or after the first element in the list
				if (target.key > tempList[0].key)
					SetCurrPos(1);
				else
				{
					tempList[1] = tempList[0];
					SetCurrPos(0);
				}
			}
			// or if it contains more than one element
			else
			{
				// Shuffle list for the newly inserted item
				for (int i = GetLength(); i > GetCurrPos(); i--)
				{
					tempList[i] = tempList[i - 1];
				}
			}

			// the new key is inserted at currPos
			tempList[GetCurrPos()] = target;
		}
		// insert at the begining of an empty list
		else
			// A list with one element is an ordered list
			tempList[0] = target;
		

		// Increment length
		SetLength(GetLength() + 1);
	}
	else
		throw DuplicateKeyException();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrdListClass::Delete()
{
	ItemType* tempList;			// pointer to hold the location of our list

	// get the location of the list
	tempList = GetListPtr();

	// shuffle each element of the list
	for (int i = GetCurrPos(); i < GetLength() - 1; i++)
	{
		tempList[i] = tempList[i + 1];
	}

	// reduce length  of the list
	SetLength(GetLength() - 1);

	// if the new length is 25% or less of the current size contract list in half
	if ((GetSize() != 4) && (GetLength() <= (int)(OCCUPANCY_TRIGGER * GetSize())))
		Contract();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//NOTE: This is the implementation of the PVF in the Base ListCLass
void OrdListClass::Print()
//Allows users to print the contents of their struct in an appropriate manner
//Pre: List exists
//Post: The contents of the list(ItemType) has been printed.
{
	// if currPos is at a valid location we can print the item at said location
	if (GetCurrPos() < GetLength())
		cout << "Item " << GetCurrPos() << " contains key " << Retrieve().key;
	// or else we must throw a retreive on empty exception
	else
		throw RetreiveOnEmptyException();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//overloaded operators
bool OrdListClass::operator== (/* in */const OrdListClass& rtOp)const			//right operand for operator
//tests the contents of rtOp with that of applying ListClass for equality
//returns true if keys are equal false otherwise
{
	ItemType* left, *rght;		// left and right pointers to point to the arrays

	left = GetListPtr();		// the *this list pointer

	rght = rtOp.GetListPtr();	// the right pointer

	// if the sizes are different they are not equal
	if (GetLength() != rtOp.GetLength())
		return false;
	// compare each entry if there is a difference they are not equal
	else
	{
		for (int i = 0; i < GetLength(); i++)
		{
			if (left[i].key != rght[i].key)
				return false;
		}
	}

	return true;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OrdListClass::operator!= (/* in */const OrdListClass& rtOp)const			//right operand for operator
//tests the contents of rtOp with that of applying ListClass for equality
//returns true if keys are not equal false otherwise
{
	ItemType* left, *rght;		// left and right pointers to point to the arrays

	left = GetListPtr();		// the *this list pointer
	
	rght = rtOp.GetListPtr();	// the right pointer

	// if the sizes are different they are not equal
	if (GetLength() != rtOp.GetLength())
		return true;
	// compare each entry if there is a difference they are not equal
	else
	{
		for (int i = 0; i < GetLength(); i++)
		{
			if (left[i].key != rght[i].key)
				return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OrdListClass OrdListClass::operator* (/* in */const OrdListClass& rtOp)const		//right operand for operator
//joins/intersects the contents of rtOp with that ListClass
//--only keys appearing in both will appear in the resultant class
{
	OrdListClass ans, temp;

	// Only the shorter list needs to be used for an intersection
	// if the left operand is smaller or equivalent to the right
	if (GetLength() <= rtOp.GetLength())
	{
		ans = *this;
		temp = rtOp;
	}
	// If the right operand is smaller
	else
	{
		ans = rtOp;
		temp = *this;
	}

	// prime loop
	ans.FirstPosition();

	// remove all items from teh list that are not found in the other
	while (!ans.EndOfList())
	{
		// if the item is not found delete it from the list
		if (!temp.Find(ans.Retrieve().key))
		{
			ans.Delete();
		}
		// move onto the next position if the item is found
		else
		{
			ans.NextPosition();
		}
	}

	return ans;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OrdListClass OrdListClass::operator+(/* in */const OrdListClass& rtOp) const	     //right operand for operator
//Merges lists-- if duplicates encountered only 1 ends up in list, the other is discarded
{
	OrdListClass ans, temp;

	// The Largest list copied to the answer will provide less data points to search for
	// if the Left operand is larger or equivalent to the right
	if (GetLength() >= rtOp.GetLength())
	{
		ans = *this;
		temp = rtOp;
	}
	// If the right operand is bigger
	else
	{
		ans = rtOp;
		temp = *this;
	}

	// Prime loop
	temp.FirstPosition();

	// add all items that are not already in list
	while (!temp.EndOfList())
	{
		// if the item is not in the list insert it
		if (!ans.Find(temp.Retrieve().key))
		{
			ans.Insert(temp.Retrieve());
		}

		// modify LCV
		temp.NextPosition();
	}

	return ans;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrdListClass::operator=(/* in */const OrdListClass& orig)					//original list
//assigns orig to applying class object
{
	// if the size of the lists are not equivalent set the lists sizes congruent
	if (GetSize() != orig.GetSize())
	{
		ItemType* newArr, * oldArr;		// New array to hold the list
		
		// create a new array of the same size as the right operand
		newArr = new ItemType[orig.GetSize()];
		
		// get the location of the old list to return it to system
		oldArr = GetListPtr();

		// set the size of the list and where the list exists in memory
		SetSize(orig.GetSize());
		SetListPtr(newArr);

		newArr = nullptr;
		delete [] oldArr;
	}

	// temporay arrays to point to the original lists
	ItemType* newList, *oldList;

	// the old list is the list sent from the right operator
	oldList = orig.GetListPtr();

	// set pdms to that of the old list
	SetSize(orig.GetSize());
	SetLength(orig.GetLength());

	// get the postion in memory of the list to be updated
	newList = GetListPtr();

	// copy each member to the new list
	for (int i = 0; i < orig.GetLength(); i++)
	{
		newList[i] = oldList[i];
	}

	// hold onto the old *this list for further deletion
	oldList = GetListPtr();

	// set the current list to the newly created list and update pdms
	SetListPtr(newList);
	SetCurrPos(orig.GetCurrPos());

	// return the old list to system
	delete [] oldList;
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//implementation of PVF's
void OrdListClass::Expand()
{
	try
	{
		ItemType* orgArr;		// Original array
		ItemType* newArr;		// New array to hold the list

		// get the list from list class
		orgArr = GetListPtr();

		// Create a new array to hold the list
		newArr = new ItemType[(int)(GetSize() * EXPANSION_FACTOR];

		// move the list to it's new container
		for (int i = 0; i < GetLength(); i++)
		{
			newArr[i] = orgArr[i];
		}

		// set the size of the list and where the list exists in memory
		SetSize((int)(GetSize() * EXPANSION_FACTOR));
		SetListPtr(newArr);

		// return the original array to memory
		delete[] orgArr;
	}
	catch (bad_alloc)
	{
		throw OutOfMemoryException();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void OrdListClass::Contract()
{
	ItemType* orgArr;		// Original array
	ItemType* newArr;		// New array to hold the list

	// get the list from list class
	orgArr = GetListPtr();

	// Create a new array to hold the list
	newArr = new ItemType[(int)(GetSize() * CONTRACTION_FACTOR)];

	// move the list to it's new container
	for (int i = 0; i < GetLength(); i++)
	{
		newArr[i] = orgArr[i];
	}

	// set the size of the list and where the list exists in memory
	SetSize((int)(GetSize() * CONTRACTION_FACTOR));
	SetListPtr(newArr);

	// return the original array to memory
	delete[] orgArr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool OrdListClass::NoRoom()
{
	// if the length of the list is equivalent to the size return true
	if (GetSize() == GetLength())
		return true;
	// else return false
	else
		return false;
}
