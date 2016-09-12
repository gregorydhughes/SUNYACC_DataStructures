//FileName : ordlist.h 
//Author:Luke Musto 
//Modifications: Gregory Hughes
//Date 03/18/2015
//Project OrdList 
//Purpose: This file contains the specification for an expandable/contractable ordered list(ascending)
//   class. It inherits basic properties and actions from the abstract base ListClass. Duplicates are
//	 not allowed to be inserted into the list.
//
//Assumptions:
//
//
//Exception Handling: exceptions are thrown in the event of running out of memory or allocating memory poorly, if currPos is set beyond the end of list
//						an Item is attempting to be retrieved from an empty list, and if a duplicate key is inserted into the list
//
//
//
//
//
//
//
//
//                         SUMMARY OF METHODS
//	bool IsFull() const;
//		returns true if list is full, false otherwise
//		overridden to ensure functionality of existing client code, list now expands)

//
//
//	bool Find(/* in */KeyType key);						// key to search for
//		finds position of key within the OrdList. 

//
//
//
//void Insert(/* in */ ItemType target);				//target to insert
////inserts target into OrdList at position specified by PDM currPos. 

//
//
//void Delete();
////deletes list entry specified by currPos, 


// The following public methods have been added to the class to provide additional 
// functionality


// None



//The following methods are also implemented as required by the Abstract Base Class


//	virtual void Expand() = 0;
//		creates a new list twice the size of the original and copies the
//		info from the smaller list to the larger one.


//virtual void Contract() = 0;
////	--creates a new list half the size of the original w/ same elements 


//	virtual bool NoRoom() = 0;
//		returns true if list has no empty locations, false otherwise



// The following operators have been overloaded to provided added functionality


//	virtual bool operator== (/* in */const OrdListClass& rtOp)const;			//right operand for operator
//		tests the contents of rtOp with that of applying ListClass for equality
//		returns true if keys are equal false otherwise

//	virtual bool operator!= (/* in */const OrdListClass& rtOp)const;			//right operand for operator
//		tests the contents of rtOp with that of applying ListClass for equality
//		returns true if keys are not equal false otherwise

//	virtual OrdListClass operator* (/* in */const OrdListClass& rtOp)const;		//right operand for operator
//		joins/intersects the contents of rtOp with that ListClass
//		only keys appearing in both will appear in the resultant class

//	virtual OrdListClass operator+(/* in */const OrdListClass& rtOp) const;	     //right operand for operator
//		Merges lists-- if duplicates encountered only 1 ends up in list, the other is discarded

//	virtual void operator=(/* in */const OrdListClass& orig);					//original list
//		assigns orig to applying class object



// The following protected methods have been added to allow expansion and contraction.

// None

//ASSUMPTIONS: A list can never be full, iostream has to be included for the print method




#include "ABCListClass.h"
#include "ExceptionClass.h"
#include <iostream>
#include <new>

// Class Declarations 
class OrdListClass : public ListClass			//uses ListClass as template for further derivations
{
	public: 
		
		OrdListClass(); 
		//Purpose:  initialized OrdListClass
		//Pre: List has been instantiated
		//Post: List has been initialized



	//OVERRIDDEN METHODS
		
		
		bool IsFull() const;
		// returns true if list is full, false otherwise
		// overridden to ensure functionality of existing client code, list now expands)
		//Pre: list has been instantiated
		//Post: false has been returned


		bool Find(/* in */KeyType key);						// key to search for
		//finds position of key within the OrdList. 
		//Pre: target contains a keyType value to search OrdList for. 
		//Post: If target is found within the OrdList, true is returned and 
		//      currPos is set to the elements location in the list. If target is 
		//      not found, false is returned and currPos is set to the 
		//      location where the element would have appeared had it been in the 
		//      List. 



		void Insert(/* in */ ItemType target);				//target to insert
		//inserts target into OrdList at position specified by PDM currPos. 
		//Pre: currPos contains location at which to insert new element; 
		//			where (0 <= currPos <= length) 
		//Post: target has been inserted into the OrdList at the location specified by currPos. 
		//		if list was full prior to insertion, list will now contain twice as many elements
		

		void Delete(); 
		//deletes list entry specified by currPos, 
		//Pre: currPos contains the location of the element to be deleted;
		//     where (O <= position < length) 
	   	//Post: element has been deleted from list. If deletion results in a percentage of ocuupancy
		//		less than 25%, list has been contracted to half the original size.



		//NOTE: This is the implementation of the PVF in the Base ListCLass
		void Print();
		//Allows users to print the contents of their struct in an appropriate manner
		//Pre: List exists
		//Post: The contents of the list(ItemType) has been printed.


		//overloaded operators
		virtual bool operator== (/* in */const OrdListClass& rtOp)const;			//right operand for operator
		//tests the contents of rtOp with that of applying ListClass for equality
		//returns true if keys are equal false otherwise
	
		virtual bool operator!= (/* in */const OrdListClass& rtOp)const;			//right operand for operator
		//tests the contents of rtOp with that of applying ListClass for equality
		//returns true if keys are not equal false otherwise


		virtual OrdListClass operator* (/* in */const OrdListClass& rtOp)const;		//right operand for operator
		//joins/intersects the contents of rtOp with that ListClass
		//--only keys appearing in both will appear in the resultant class
	
		virtual OrdListClass operator+(/* in */const OrdListClass& rtOp) const;	     //right operand for operator
		//Merges lists-- if duplicates encountered only 1 ends up in list, the other is discarded
		
		virtual void operator=(/* in */const OrdListClass& orig);					//original list
		//assigns orig to applying class object


	protected: 
		
		virtual void Expand();
		// creates a new list twice the size of the original and copies the
		//info from the smaller list to the larger one.
		//Pre : List is full and needs to be enlarged
		//Post: List size has been doubled 
		
		virtual void Contract();
		// creates a new list half the size of the original and copies the
		//info from the old list to the new one.
		//Pre : List has less than  25% occupancy
		//Post: List size has been cut in half
	
		virtual bool NoRoom();
		//	--returns true if list has no empty locations, false otherwise
		//Pre : List exists
		//Post: true is returned if list has no available locations, false otherwise


 	private:
		// nothing additional

};//end OrdListClass 
