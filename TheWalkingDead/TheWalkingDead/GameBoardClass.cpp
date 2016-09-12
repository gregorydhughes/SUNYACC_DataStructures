// Author: Gregory D Hughes
// Date: September 30th 2014
// Purpose: This specification contains the basis for an gameboard class. 
// It currently contains a maximum of 64 elements. It allows Gameboard 
// creation and sets details on location
// 
// Assumptions:
//	Gameboard supports WL (w*l) places ( or Width * length) and border will be 
//	an even number

/*
Private members of class:

GameBoard board;		 // The array used for gameboard datatype

*/

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

#include "GameBoardClass.h"

GameBoardClass::GameBoardClass()
// Pre:		None
// Post:	The object has been instantiated
{
	// Enable the border and set all cells to inactive and unoccupied
	for (int i = 0; i < MAX_COL + BORDER; i++)
	{
		for (int j = 0; j < MAX_ROW + BORDER; j++)
		{
			board[i][j].active = false;
			board[i][j].numZombies = 0;
			board[i][j].occupied = false;
			board[i][j].playerID = -1;
		}
	}

	// activate cells
	for (int i = 1; i <= MAX_COL; i++)
	{
		for (int j = 1; j <= MAX_ROW; j++)
		{
			board[i][j].active = true;
		}
	}

}

bool GameBoardClass::IsActive(LocationRec loc) const
// Pre:		The object has been instantiated and a location determined
// Post:	Client is given the details on loc if a cell is active
{
	return board[loc.row][loc.col].active;
}
int GameBoardClass::GetNumZombies(LocationRec loc) const
// Pre:		The object has been instantiated and a location determined
// Post:	Client is returned the number of zombies at loc
{
	return board[loc.row][loc.col].numZombies;
}
void GameBoardClass::ModNumZombies(LocationRec loc, int num)
// Pre:		The object has been instantiated and a location determined
// Post:	The number of zombies is modified at loc by num
{
	board[loc.row][loc.col].numZombies = num;
}
int GameBoardClass::GetPlayerID(LocationRec loc) const
// Pre:		The object has been instantiated and a location determined
// Post:	The playerID has been returned to client at loc
{
	return board[loc.row][loc.col].playerID;
}
void GameBoardClass::SetPlayerID(LocationRec loc, int playerID)
// Pre:		The object has been instantiated and a location determined
// Post:	The playerID given by client has been set at loc
{
	board[loc.row][loc.col].playerID = playerID;
}
bool GameBoardClass::IsOccupied(LocationRec loc) const
// Pre:		The object has been instantiated and a location determined
// Post:	Client is informed of the occupation status at loc
{
	return board[loc.row][loc.col].occupied;
}
void GameBoardClass::SetOccupied(LocationRec loc, bool set)
// Pre:		The object has been instantiated and a location determined
// Post:	The loc given by client has been either set or unset by bool set
{
	board[loc.row][loc.col].occupied = set;
}
