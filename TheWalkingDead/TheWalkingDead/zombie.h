#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "location.h"
#include "HumanList.h"

typedef int humanIDArr[MAX_LENGTH];
typedef int zombieID;

struct ZombieRec
{
	zombieID zombieNum;		// Id number for zombie searches and reference
	bool livingDead;		// Boolean expression to detrmine if a zombie is dead
	LocationRec loc;		// Location of a zombie
	int strength;			// The strength of a zombie
	int biteCount;			// The number of times a zombie has biten a player (length of biteList)
	humanIDArr bitenList;	// The list of humans that a zombie has bitten
	int killCount;			// The number of players a zombie has killed (length of kill list)
	humanIDArr killsList;	// The list of humans killed by a zombie
	int roundKilled;		// The round a zombie was killed in
};

#endif