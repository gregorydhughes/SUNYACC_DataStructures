/*
Author:			Gregory D Hughes
Project:		Luke Nukem (Project 1)
Filename:		gbRec.h
Purpose:		To store a record of each member of a gameboard class object
*/

#ifndef GAMEBOARDREC_H
#define GAMEBOARDREC_H

const short MAX_ROW = 7;			// The maximuim rows in a gameboard
const short MAX_COL = 7;			// The maximuim columns in a gameboard
const short TRACK_WID = 2;			// Width of the track on the overall board horizontally and vertically

// Structure to define a record in a game board class object
struct GameBoardRec
{
	bool active;			// Predicates if the cell is active or not
	bool occupied;			// Predicates if the cell is occupied or not
	bool core;				// Predicates if the cell is part of the lead sheild or not
	short playerID;			// Contains the ID of a player, -1 if unoccupied
	short particles;		// Contains the number of particles that are active in a given cell
	short bornParticles;	// Contains the number of particles that were placed in a cell upon simulation
	short particlesEsc;		// The number of particles escaping
};

#endif