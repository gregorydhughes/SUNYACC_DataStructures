/*
Author:			Gregory D Hughes
Project:		Luke Nukem (Project 1)
Filename:		Player.h
Purpose:		To hold player record details
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "Location.h"
#include <string>

struct PlayerRec
{
	short playerID;			// ID of player
	std::string name;		// Name of player
	short health;			// Health of player
	LocationRec currLoc;	// Player's location
	short currAge;
};

#endif