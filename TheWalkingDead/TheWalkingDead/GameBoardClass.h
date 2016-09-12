// Author: Gregory D Hughes
// Date: September 30th 2014
// Purpose: This specification contains the basis for an gameboard class. 
// It currently contains a maximum of 64 elements. It allows Gameboard 
// creation and sets details on location
// 
// Assumptions:
//	Gameboard supports 64 places (8 x 8) and border will be an even number
//
// Error Handling: None
//
// Summary of Methods
// GameBoardClass() -- initializes gameboard object
// bool IsActive(LocationRec loc) -- Returns wheither a gamecell is active or not
// int GetNumZombis(LocationRec loc) -- Returns the number of zombies occuping a cell
// void ModNumZombies(LocationRec loc, int num) -- Modifies the number of zombies in a cell
// int GetPlayerID(LocationRec loc) -- Returns the player ID of a player in a cell
// void SetPlayerID(LocationRec loc, int playerID) -- Sets the player ID at a specified location
// bool IsOccupied(LocationRec loc) -- returns whether a cell is occupied by a human
// void SetOccupied(LocationRec loc, bool set) -- Sets a cell to be occupied or unoccupied
#ifndef GAMEBOARDCLASS_H
#define GAMEBOARDCLASS_H

#include "HumanList.h"
#include "ZombieList.h"
#include "gameCell.h"

const int MAX_ROW = 3;		// The number of rows in the gameboard
const int MAX_COL = 3;		// The number of columns in the gameboard
const int BORDER = 2;		// The boarder around the gameboard

// the data objet that the class will use
typedef GameCell GameBoard[MAX_ROW + BORDER][MAX_COL + BORDER];

class GameBoardClass
{
public:
	GameBoardClass();
	// Pre:		None
	// Post:	The object has been instantiated

	bool IsActive(LocationRec loc) const;
	// Pre:		The object has been instantiated and a location determined
	// Post:	Client is given the details on loc if a cell is active

	int GetNumZombies(LocationRec loc) const;
	// Pre:		The object has been instantiated and a location determined
	// Post:	Client is returned the number of zombies at loc

	void ModNumZombies(LocationRec loc, int num);
	// Pre:		The object has been instantiated and a location determined
	// Post:	The number of zombies is modified at loc by num

	int GetPlayerID(LocationRec loc) const;
	// Pre:		The object has been instantiated and a location determined
	// Post:	The playerID has been returned to client at loc

	void SetPlayerID(LocationRec loc, int playerID);
	// Pre:		The object has been instantiated and a location determined
	// Post:	The playerID given by client has been set at loc

	bool IsOccupied(LocationRec loc) const;
	// Pre:		The object has been instantiated and a location determined
	// Post:	Client is informed of the occupation status at loc

	void SetOccupied(LocationRec loc, bool set);
	// Pre:		The object has been instantiated and a location determined
	// Post:	The loc given by client has been either set or unset by bool set

private:
	GameBoard board;		 // The array used for gameboard datatype
};

#endif