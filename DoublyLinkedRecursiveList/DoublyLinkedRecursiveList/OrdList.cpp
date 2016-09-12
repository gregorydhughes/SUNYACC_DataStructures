//*************************************************************************************************
//										IMPLEMENTATION FILE
/*
Author: Luke Musto
Date: 04/10/2015
Modifications:
Mod Date:
Project: Doubly Linked Recursive List
Filename: OrdList.cpp
Purpose: This file contains the implementation of OrdList.
*/
//*************************************************************************************************

// Included Libraries
#include "OrdList.h"

//definition of forward declaration
struct node
{
	node* prev;			// Pointer to the previous node 
	ItemType data;		// Data stored
	node* next;			// Pointer to the next node 
}; // End node struct

// ------------------------------------------------------------------------------------------------
// |																							  |
// |								Constructors & Destructors									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		OrdListClass::OrdListClass()
		{
			// set the head and tail of object to null
			head = nullptr;
			tail = nullptr;
		} // End Default Constructor

//*************************************************************************************************

		OrdListClass::~OrdListClass()
		{
			// Clear object from meory when leaving scope
			Clear();
		} // End Destructor

//*************************************************************************************************

		OrdListClass::OrdListClass(/*in*/ const OrdListClass& orig) // List to be copied.
		{
			// set the head and tail of object to null
			head = nullptr;
			tail = nullptr;

			// CurrObj = origObj
			operator=(orig);
		} // End Copy Constructor

// ------------------------------------------------------------------------------------------------
// |																							  |
// |							Observer Predicators											  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		bool OrdListClass::IsFull() const
		{
			// List can never be full
			return false;
		} // End IsFull()

//*************************************************************************************************

		bool OrdListClass::IsEmpty() const
		{
			// when head point nowhere, list is empty
			return (head == nullptr);
		} // End IsEmpty()

// ------------------------------------------------------------------------------------------------
// |																							  |
// |										Mutators											  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		void OrdListClass::Insert(/*in*/ ItemType newItem) // Item to be inserted.
		{
			//call recursive function
			rInsert(head, newItem);
		} // End Insert()

//*************************************************************************************************

		void OrdListClass::Delete(/*in*/ KeyType target) // Key of item to delete.
		{
			// only can delete if the list is not empty
			if(!IsEmpty())
				rDelete(head, target);
			else
				throw KeyNotThereException();
		} // End Delete()

//*************************************************************************************************

		void OrdListClass::Clear()
		{
			// can only clear object if object is already occupied
			if(!IsEmpty())
				rClear(head);

			head = nullptr;
			tail = nullptr;
		} // End Clear()

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Observer Accessor										  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		ItemType OrdListClass::Retrieve(/*in*/ KeyType target) const // Key of item to be returned.
		{
			// If the list isn't empty try to retrieve. Otherwise, throw an exception.
			if(!IsEmpty())
			{
				ItemType tbr;					// to be returned

				// Call recursive function
				rRetrieve(head, tbr, target);

				return tbr;
			} // End not empty path.
			else
				throw KeyNotThereException();

			
		} // End Retrieve()

// ------------------------------------------------------------------------------------------------
// |																							  |
// |								Observer Summarizers/Printerators(lol)						  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		void OrdListClass::Print() const
		{
			// call recursive function only if the list is occupied
			if(!IsEmpty())
				rPrint(head);
		} // End Print()

//*************************************************************************************************

		void OrdListClass::PrintReverse() const
		{
			// call recursive function only if the list is occupied
			if(!IsEmpty())
				rPrintRev(tail);
		} // End PrintReverse()

// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Overloaded Operators									  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		void OrdListClass::operator =(/*in*/ const OrdListClass& orig)	// List to be copied.
		{
			// clear the original list to make way for the new items.
			Clear();

			// if orig is empty we don't have to place items into list
			if (!orig.IsEmpty())
			{
				// set trav to the orig head
				node* trav = orig.head;

				// and creata new node to tack onto list
				node* newNode = Allocate();

				// set the newNodes data to the original list data
				newNode->data = trav->data;

				// tack the new node to head
				head = newNode;

				// move down orig
				trav = trav->next;

				// while trav is not at the end of list
				while (trav != nullptr)
				{
					// get a new node for the next element
					newNode->next = Allocate();

					// set the new nodes previous field to the last node created
					newNode->next->prev = newNode;

					// set to point to the new node
					newNode = newNode->next;

					// set data with orig's data
					newNode->data = trav->data;

					// if orig's tail is found set tail in new list
					if (trav->next == nullptr)
					{
						tail = newNode;
					}
					
					// move to next position
					trav = trav->next;
				}// end While

			}// End Empty list check

		} // End operator=()
		

//*************************************************************************************************
		OrdListClass OrdListClass::operator +(/*in*/ const OrdListClass& rtOp) const // List to be added to applying object.
		{
			OrdListClass tbr;  //to be returned

			// set list to left list
			tbr = *this;

			// create a traveler for the left operand and the right
			node* lTrav = tbr.head;
			node* rTrav = rtOp.head;

			// while each list has not come to an end
			while (rTrav != nullptr && lTrav != nullptr)
			{
				// place item before the current left traversal
				if (rTrav->data.key < lTrav->data.key)
				{
					// create a new node(allocate did not work for me here)
					node* temp = new node;
					
					// set the next feild for the smaller key to the larger lTRav key
					temp->next = lTrav;
										
					// insert the data into feild
					temp->data = rTrav->data;

					// determine if we are moving head
					if (lTrav->prev == nullptr)
					{
						lTrav->prev = temp;

						temp->prev = nullptr;

						tbr.head = temp;
					}
					// General case insert into list
					else
					{
						lTrav->prev->next = temp;

						temp->prev = lTrav->prev;

						lTrav->prev = temp;
					}

					// move down rtOp
					rTrav = rTrav->next;
				}
				// if the rtOp is large than the left move the left traversal down
				else if (rTrav->data.key > lTrav->data.key)
				{
					lTrav = lTrav->next;
				}
				else
				{
					// Duplicate key move to next field
					lTrav = lTrav->next;
					rTrav = rTrav->next;
				}
			}
			// If their are items still remaining in the rtOp place items into the list in order.
			if (lTrav == nullptr)
			{
				lTrav = tbr.tail;
				
				// while we are not at the end of the rtOp list
				while (rTrav != nullptr)
				{
					// Add nodes to end of *this
					node* temp = new node;

					temp->next = nullptr;

					temp->data = rTrav->data;

					temp->prev = lTrav;

					lTrav->next = temp;

					tbr.tail = temp;

					lTrav = lTrav->next;

					rTrav = rTrav->next;
				}
			}

			// return new list
			return tbr;
		}

	
//*************************************************************************************************

		OrdListClass OrdListClass::operator -(/*in*/ const OrdListClass& rtOp) const // List to be subtracted from applying object.
		{
			OrdListClass tbr;  //to be returned

			// set list to the left operand
			tbr = *this;

			// create a traveler for the left operand and the right
			node* lTrav = tbr.head;
			node* rTrav = rtOp.head;

			// while we are not at the end of list
			while (lTrav != nullptr && rTrav != nullptr)
			{
				// if the keys are found remove them from list
				if (lTrav->data.key == rTrav->data.key)
				{
					//item to delete
					node* temp = lTrav;

					// Determine if we are removing head
					if (lTrav->prev == nullptr)
					{
						// make sure there is more than one item in the list
						if (lTrav->next != nullptr)
						{
							tbr.head = tbr.head->next;

							tbr.head->prev = nullptr;
						}
						else
							tbr.Clear();
					}
					// Determine if we are removing tail
					else if (lTrav->next == nullptr)
					{
						tbr.tail = tbr.tail->prev;

						tbr.tail->next = nullptr;
					}
					// else remove general case
					else
					{
						lTrav->prev->next = lTrav->next;

						lTrav->next->prev = lTrav->prev;
					}

					// move onto next item in list
					lTrav = lTrav->next;

					rTrav = rTrav->next;

					delete temp;
				}
				// move down left list if the right key is larger
				else if (rTrav->data.key > lTrav->data.key)
				{
					lTrav = lTrav->next;
				}
				// move down the right list if left is larger
				else
				{
					rTrav = rTrav->next;
				}
			}


			return tbr;
		}

//*************************************************************************************************

		
// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Protected Methods										  |
// |																							  |
// ------------------------------------------------------------------------------------------------
		
		node* OrdListClass::Allocate()
		{
			// Try to allocate memory
			
			try
			{
				// create a temporary node
				node* temp = new node;
		
				// set the pointers to null
				temp->next = nullptr;
				temp->prev = nullptr;
				return temp;
			}
			// throw out of memory exception in such an event
			catch (std::bad_alloc)
			{
				throw OutOfMemoryException();
			}


		} // End Allocate()
		
// ------------------------------------------------------------------------------------------------
// |																							  |
// |									Recursive (Wrapped) Methods								  |
// |																							  |
// ------------------------------------------------------------------------------------------------

		void OrdListClass::rPrint(/*in*/ const node* trav) const // Pointer to traversal node 
		{
			// only print until the end of list
			if (trav != nullptr)
			{
				// print the key and move to next item
				cout << trav->data.key << endl;
				rPrint(trav->next);	
			}
		} // End rPrint()

//*************************************************************************************************

		void OrdListClass::rPrintRev(/*in*/ const node* trav) const // Pointer to traversal node 
		{
			// only print until the begining of list
			if (trav != nullptr)
			{
				// print last item and move to previous
				cout << trav->data.key << endl;
				rPrintRev(trav->prev);
			}
		} // End rPrintRev()

//*************************************************************************************************

		void OrdListClass::rClear(/*in*/ node* trav) // Pointer to traversal node 
		{
			// create a hold for deletion
			node* temp = trav;

			// so long as there are multiple elements in the list
			if (temp->next != nullptr)
			{
				// move down the list
				head = temp->next;

				//removing head
				head->prev = nullptr;

				// return system resources
				delete temp;

				rClear(head);
			}
			// if not remove the last element in list
			else
			{
				delete temp;
			}

		} // End rClear()

//*************************************************************************************************

		void OrdListClass::rDelete(/*in*/ node* trav,			// Pointer to traversal node 
				 				   /*in*/ KeyType target)		// Target key to be deleted.
		{
			// so long as we are not at end of list
			if (trav != nullptr)
			{
				// delete if key matches
				if (trav->data.key == target)
				{
					// deleting head
					if (trav->prev == nullptr)
					{
						node* temp = trav;

						node* newHead = temp->next;

						newHead->prev = nullptr;

						head = newHead;

						delete temp;
					}
					// deleting tail
					else if (trav->next == nullptr)
					{
						node* temp = trav;

						node* newTail = temp->prev;

						newTail->next = nullptr;

						delete temp;
					}
					// deleting general case
					else
					{
						node* temp = trav;

						node* prev = temp->prev;

						prev->next = temp->next;

						temp->next->prev = prev;

						delete temp;
					}
				}
				// move on if key not found so far
				else
					rDelete(trav->next, target);
			}
			// reached the end of list, key not found
			else
				throw KeyNotThereException();
			
		} // End rDelete()

//*************************************************************************************************

		void OrdListClass::rInsert(/*in*/ node* trav,			// Pointer to traversal node 
									/*in*/ ItemType newItem)	// Item to be inserted.
		{
			//if the list is empty
			if (head == nullptr)
			{
				head = Allocate();
				tail = head;
				head->data = newItem;
			}
			// if reached the end of list
			else if (trav->next == nullptr)
			{
				// if the key already exists
				if (trav->data.key == newItem.key)
					throw DuplicateKeyException();
				// end of a list where item should be placed last
				else if (trav->data.key < newItem.key)
				{
					trav->next = Allocate();

					trav->next->data = newItem;

					trav->next->prev = trav;

					trav->next->next = nullptr;

					tail = trav->next->next;
				}
				// end of list where item should be placed second to last
				else if (trav->data.key > newItem.key)
				{
					// if there is only one item in list and item must be placed at head
					if (trav->prev == nullptr)
					{
						node* newNode = Allocate();

						newNode->next = trav;

						newNode->data = newItem;

						trav->prev = newNode;

						head = newNode;

					}
					//or else insert as the general case
					else
					{
						node* temp = Allocate();
						node* hold = trav->prev;

						temp->prev = hold;

						temp->data = newItem;

						temp->next = trav;

						hold->next = temp;

						trav->prev = temp;
					}
				}
			}
			// else it is general case and will continue the traversal or insert at trav->prev
			else
			{
				// if the key already exists
				if (trav->data.key == newItem.key)
					throw DuplicateKeyException();
				// insert at the next location
				else if (trav->data.key > newItem.key)
				{
					// insert item at the head in a list with elements
					if (trav->prev == nullptr)
					{
						node* temp = Allocate();

						temp->data = newItem;

						temp->next = trav;

						trav->prev = temp;

						head = temp;
					}
					// insert as a general case in the middle of a list
					else
					{
						node* temp = Allocate();
						node* hold = trav->prev;

						temp->prev = hold;

						temp->data = newItem;

						temp->next = trav;

						hold->next = temp;

						trav->prev = temp;
					}
				}
				// check next position
				else
				{
					rInsert(trav->next, newItem);
				}
			}

		} // End rInsert()

//*************************************************************************************************

		void OrdListClass::rRetrieve(/*in*/ node* trav,					// Pointer to traversal node 
									 /*in/out*/ ItemType& tbr,			// Item to be returned.
									 /*in*/ KeyType target) const		// Requested key to be retrieved.
		{
			// make sure we are not at the end of list
			if (trav != nullptr)
			{
				// if the key is found
				if (trav->data.key == target)
					tbr = trav->data;
				// if the position in list is greater than the target the item cannot be in an ordered list
				else if (trav->data.key > target)
					throw KeyNotThereException();
				// move to next postion if not
				else
					rRetrieve(trav->next, tbr, target);
			}
			else
				throw KeyNotThereException();
		} // End rRetrieve()


