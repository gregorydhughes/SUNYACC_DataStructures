//*************************************************************************************************
/*									Struct Definition
Author: Luke Musto
Date: 4/10/2015
Project: Doubly Linked Recursive List
Filename: ItemType.h
Purpose: This file contains the struct ItemType and KeyType definitions for the OrdList Class.
*/

#ifndef ITEM_TYPE
#define ITEM_TYPE

// Named Constants
const int MORE_MEMORY = 10000;		// Size of the array to allocate more memory

// Type Definitions
typedef int KeyType;				// key used to order the list

typedef double MemArray[MORE_MEMORY];   // filler for record 

struct ItemType
{
	KeyType key;		// The key used to find list elements.
	MemArray moreMem;	// Makes testing the OutofMemoryException easier.

}; // End struct ItemType

#endif