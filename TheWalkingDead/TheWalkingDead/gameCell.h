#ifndef GAMECELL_H
#define GAMECELL_H

#include "location.h"

struct GameCell
{
	bool active;		// Whether a cell is active or not
	bool occupied;		// Whether a cell is occupied
	int playerID;		// ID of player in cell
	int numZombies;		// Number of active zombies on location
};

#endif