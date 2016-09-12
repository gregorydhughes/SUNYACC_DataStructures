/*
Author:			Gregory D Hughes
Project:		Development of a GameBoardClass
Filename:		GameBoardClass.h
Purpose:
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

#include "gbRec.h"			// Includes the record for each of the gameboard cells
#include "Location.h"	// Includes a record detailing a location within the board

const short NO_PLAYER = -1;			// A constant to show that no player is in the Gameboard's location

// A easier way to use the 3d array of a game board
typedef GameBoardRec GameBoard[MAX_ROW][MAX_COL];// [MAX_DEP];

class GameBoardClass
{
public:
	GameBoardClass();

	bool IsActive(LocationRec loc);							// Location to predicate if cell is active

	bool IsOccupied(LocationRec loc);						// Location to predicate if cell is occupied

	void SetActive(LocationRec loc);						// Location to set active

	void SetOccupied(LocationRec loc);						// Location to set occupied
	
	void SetInactive(LocationRec loc);						// Location to set inactive

	void SetUnoccupied(LocationRec loc);					// Location to set unoccupied

	void SetPlayerID(LocationRec loc,						// Location to set player ID
						short playerID);					// ID of player to set

	short GetPlayerID(LocationRec loc);						// Location to retreive player ID

	bool RemovePlayer(short playerID);						// Player ID to search for and remove if present

	bool IsCore(LocationRec loc);							// Location to predicate if is part of the core

	short GetNumParticles(LocationRec Loc);					// Location to return the number of particles

	void IncreaseNumParticles(LocationRec loc);				// Location to decrease the number of particles

	void DecreaseNumParticles(LocationRec loc);				// Location to decrease the number of particles

	void PlusPlusBornParticls(LocationRec loc);				// Location to increase the number of particle born

	void PlusPlusEscapedParticles(LocationRec startLoc,		// Location that a particle is escaping from
									LocationRec endLoc);	// Location particle escapes to

	short GetNumParticlesBorn(LocationRec loc);				// Location to return the number of particles born in a cell

	short GetNumParticlesEscpaed(LocationRec loc);			// Location to return the number of particles escaped

private:
	bool IsTrackAdgecent(LocationRec loc);					// Location to determine if a cell is adjacent to the track

	GameBoard gb;
};
