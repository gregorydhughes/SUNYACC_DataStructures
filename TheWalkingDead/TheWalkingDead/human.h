#ifndef HUMAN_H
#define HUMAN_H

#include "location.h"
//#include "ZombieList.h"
#include <string>

using std::string;

const int MAX_LENGTH = 125;

enum WeaponEnum {NO_WEAPON, TEASPOON, PITCHFORK, FIVEFINGERDEATHPUNCH, CROSSBOW, KATANA, FORTYFIVEAUTO};

typedef int zKillList[MAX_LENGTH];
typedef int playerID;

struct HumanRec
{
	playerID ID;		// ID Number for player searches and reference
	string fName;		// First Name
	string lName;		// Last Name
	LocationRec loc;	// Record of human location
	int lifeUnits;		// Life units of player
	WeaponEnum weapon;	// Record of player's weapon
	int biteCount;		// The number of bites a human has incured 
	bool alive;			// Boolean value to dtermine if player is alive
	int kills;			// Number of kills(length of kill list
	zKillList killList;	// List of zombies killed
	int roundKilled;	// The round that a human was killed in
	int killerID;		// The zombie number that killed the player
};

#endif