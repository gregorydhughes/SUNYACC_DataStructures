/*
Author:			Gregory D Hughes
Project:		Development of a GameBoardClass
Filename:		GameBoardClass.cpp
Input:			None
Processing:		None
Output:			Class can output the game board in full
Assumptions:	All locations sent to methods will be valid
Error
Handling:		None
*/

/*************************************************************Summary of Methods**************************************************************
GameBoardClass(); - Default Constructor sets all members in a gameboard class to active, unoccupied and sets the player value to NO_PLAYER(-1)

bool IsActive(LocationRec loc); - Predicates if the location given by client is active.

bool IsOccupied(LocationRec loc); - Predicates if the location given by client is occupied.

void SetActive(LocationRec loc); - Sets the location given by client to active.

void SetOccupied(LocationRec loc); - Sets the location given by client to occupied.

void SetInactive(LocationRec loc); - Sets the location given by client to inactive.

void SetUnoccupied(LocationRec loc); - Sets the location given by client to unoccupied.

void SetPlayerID(LocationRec loc, short playerID); - Sets the player ID at location given by client to the player ID also given by client.

short GetPlayerID(LocationRec loc); - Returns the player ID that is assigned to location given by client.

bool RemovePlayer(short playerID); - Removes the player with the defined player ID given by client.

bool IsCore(LocationRec loc); - Predicates if the location is the core

short GetNumParticles(LocationRec Loc); - returnd the number of particles at a determined location

void IncreaseNumParticles(LocationRec loc); - Increase the number of particles at a given location

void DecreaseNumParticles(LocationRec loc); - Increase the number of particles at a given location

void PlusPlusBornParticls(LocationRec loc); - Increase the number of particles born at a given location

void PlusPlusEscapedParticles(LocationRec startLoc,
LocationRec endLoc); - Increase the number of particles escaping at a given location

short GetNumParticlesBorn(LocationRec loc); - return the number of particles born at a given location

short GetNumParticlesEscpaed(LocationRec loc); - Increase the number of particles escaped at a given location

bool IsTrackAdjacent(LocationRec loc); - Predicates if a given location is next to a track location
*/

#include "GameBoardClass.h"		// Include all applicable libraries

using namespace std;

GameBoardClass::GameBoardClass()
// Pre:		None
// Post:	The game board class object is intialized
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			gb[i][j].active = true;
			gb[i][j].occupied = false;
			gb[i][j].core = false;
			gb[i][j].playerID = NO_PLAYER;
			gb[i][j].particles = 0;
			gb[i][j].bornParticles = 0;
			gb[i][j].particlesEsc = 0;
		}
	}

	//Create the core!
	for (int i = 0; i < MAX_ROW - TRACK_WID; i++)
	{
		for (int j = 0; j < MAX_COL - TRACK_WID; j++)
		{
			gb[i + 1][j + 1].core = true;
		}
	}
}

bool GameBoardClass::IsActive(LocationRec loc)			//Location to predicate if the cell is active
// Pre:		A game board class object ahs been intialized
// Post:	The status of a cell activation at location loc is returned to client
{
	// Predicate at location
	return gb[loc.row][loc.col].active;
}

bool GameBoardClass::IsOccupied(LocationRec loc)		//Location to predicate if the cell is occupied
// Pre:		A game board class object has been intialized
// Post:	The status of a cell occupation at location loc is returned to client
{
	return gb[loc.row][loc.col].occupied;
}

void GameBoardClass::SetActive(LocationRec loc)			//Location to set cell active
// Pre:		A game board class object has been intialized
// Post:	The status of a cells activity at location loc is set
{
	gb[loc.row][loc.col].active = true;
}

void GameBoardClass::SetOccupied(LocationRec loc)		//Location to set cell occupied
// Pre:		A game board class object has been intialized
// Post:	The status of a cells occupation at location loc is set
{
	gb[loc.row][loc.col].occupied = true;
}

void GameBoardClass::SetInactive(LocationRec loc)		//Location to set cell inactive
// Pre:		A game board class object has been intialized
// Post:	The status of a cell's inactivity at location loc is set
{
	gb[loc.row][loc.col].active = false;
}

void GameBoardClass::SetUnoccupied(LocationRec loc)		//Location to set cell unoccupied
// Pre:		A game board class object has been intialized
// Post:	The status of a cell's unoccupation at location loc is set
{
	gb[loc.row][loc.col].playerID = NO_PLAYER;
	gb[loc.row][loc.col].occupied = false;
}

void GameBoardClass::SetPlayerID(LocationRec loc,		// Location to set player ID
									short playerID)		// Player ID to set at location loc
	// Pre:		A game board class object has been intialized
	// Post:	The status of a cell's Player ID at location loc is set
{
	

	// if the location was previously unoccupied set the cell to occupied
	if (playerID >= 0 && gb[loc.row][loc.col].occupied == false)
	{
		// set the gameboard location loc to player ID given by client
		gb[loc.row][loc.col].playerID = playerID;

		//And set the location to occupied
		gb[loc.row][loc.col].occupied = true;
	}
	// if the player ID is invalid set the location to unoccupied
	else
	{
		gb[loc.row][loc.col].occupied = false;
		gb[loc.row][loc.col].playerID = -1;
	}
}

short GameBoardClass::GetPlayerID(LocationRec loc)		// Location to get player ID from
// Pre:		A game board class object has been intialized
// Post:	The player ID at location loc is returned to client
{
	return gb[loc.row][loc.col].playerID;
}

bool GameBoardClass::RemovePlayer(short playerID)		// ID of player to be removed from the board
// Pre:		A game board class object has been intialized
// Post:	The player ID given is removed from board and a status of true is given if ID found, false otherwise
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{

			// If the ID matches set the location to unoccupied and NO_PLAYER
			if (gb[i][j].playerID == playerID)
			{
				gb[i][j].occupied = false;
				gb[i][j].playerID = NO_PLAYER;
				// Return true
				return true;
			}

		}
	}

	// If the ID is not found in the entire gameboard then return false.
	return false;
}

bool GameBoardClass::IsCore(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	Status of the location provided is returned to client
{
	return gb[loc.row][loc.col].core;
}

short GameBoardClass::GetNumParticles(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	The Number of particles at the location is returned
{
	return gb[loc.row][loc.col].particles;
}

void GameBoardClass::IncreaseNumParticles(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	The number of particles at location loc is increased
{
	gb[loc.row][loc.col].particles++;
}

void GameBoardClass::DecreaseNumParticles(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	The number of particles at a location is decreased
{
	gb[loc.row][loc.col].particles--;
}

void GameBoardClass::PlusPlusBornParticls(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	the number of born particles is increased
{
	gb[loc.row][loc.col].bornParticles++;
}

void GameBoardClass::PlusPlusEscapedParticles(LocationRec startLoc, LocationRec endLoc)
// Pre:		A game board class object has been intialized
// Post:	The number of particles escaping a cell is increased
{
	// if the location moving from is located on the outside of the core
	if (IsTrackAdgecent(startLoc))
		// and will be exiting onto the track..
		if (!IsCore(endLoc))
			// update escaped particles
			gb[startLoc.row][startLoc.col].particlesEsc++;
}

short GameBoardClass::GetNumParticlesBorn(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	The number of particles at location is returned to caller
{
	return gb[loc.row][loc.col].bornParticles;
}

short GameBoardClass::GetNumParticlesEscpaed(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	The number of particles escaping at location loc is returned
{
	if (IsTrackAdgecent(loc))
		return gb[loc.row][loc.col].particlesEsc;
	else 
		return 0;
}

bool GameBoardClass::IsTrackAdgecent(LocationRec loc)
// Pre:		A game board class object has been intialized
// Post:	The expression of whether or not a cell is adjacent to the track is returned
{
	if (gb[loc.row][loc.col].core)
	{
		if (!gb[loc.row + 1][loc.col].core)
			return true;
		if (!gb[loc.row - 1][loc.col].core)
			return true;
		if (!gb[loc.row][loc.col + 1].core)
			return true;
		if (!gb[loc.row][loc.col - 1].core)
			return true;
	}
}