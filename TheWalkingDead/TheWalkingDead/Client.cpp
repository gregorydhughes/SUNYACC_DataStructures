#include "GameBoardClass.h"
#include <iostream>
#include <fstream>

using namespace std;

const int SEED_VALUE = 123456789;

const int NUM_ZOMBIES = 50;

const string FILE_NAME = "six.in";

void ZombieCreation(ZListClass& zombieList, GameBoardClass& theBoard);

void HumanAssignment(HListClass& humanList, GameBoardClass& theBoard);

WeaponEnum DetermineWeapon(string tempWeapon);

LocationRec DetermineHumanPosition(int id, GameBoardClass& theBoard);

void main()
{
	srand(SEED_VALUE);

	int round = 0;
	bool endOfGame = false;

	GameBoardClass theBoard;
	//ZListClass zombieList;
	HListClass humanList;
	system("pause");
	/*ZombieCreation(zombieList, theBoard);*/

	/*HumanAssignment(humanList, theBoard);*/

	//while (!endOfGame)
	//{

	//}

}

void ZombieCreation(ZListClass& zombieList, GameBoardClass& theBoard)
{
	ZombieRec tempZombie;
	int tempNum;
	LocationRec tempLoc;

	tempZombie.livingDead = true;
	tempZombie.roundKilled = 0;
	tempZombie.strength = 5;

	// Number assignment
	for (int i = 0; i < NUM_ZOMBIES; i++)
	{

		tempNum = i+1;
		tempZombie.zombieNum = tempNum;
		
		tempLoc.row = rand() % MAX_ROW + 1;
		tempLoc.col = rand() % MAX_COL + 1;
		tempZombie.loc = tempLoc;

		tempNum = theBoard.GetNumZombies(tempLoc) + 1;
		theBoard.ModNumZombies(tempLoc, tempNum);

		zombieList.Insert(tempZombie);
	}



}

void HumanAssignment(HListClass& humanList, GameBoardClass& theBoard)
{
	ifstream din;

	din.open(FILE_NAME);


	HumanRec tempHuman;

	string tempLName;
	string tempFNAme;
	int tempLife;
	string tempWeaponStr;
	WeaponEnum tempWeaponEnum;
	LocationRec tempLoc;
	int tempID = 0;

	while (din)
	{
		tempID++;

		din >> tempFNAme >> tempLName >> tempLife >> tempWeaponStr;
		tempWeaponEnum = DetermineWeapon(tempWeaponStr);
		tempLoc = DetermineHumanPosition(tempID, theBoard);
		
		tempHuman.alive = true;
		tempHuman.biteCount = 0;
		tempHuman.fName = tempFNAme;
		tempHuman.lName = tempLName;
		tempHuman.killerID = -1;
		tempHuman.kills = 0;
		tempHuman.lifeUnits = tempLife;
		tempHuman.roundKilled = -1;
		tempHuman.weapon = tempWeaponEnum;
		tempHuman.playerID = tempID;
		tempHuman.loc = tempLoc;

		humanList.Insert(tempHuman);
	}

	din.close();
	
}

WeaponEnum DetermineWeapon(string tempWeapon)
{
	WeaponEnum ans;
	//enum WeaponEnum {NO_WEAPON, TEASPOON, PITCHFORK, FIVEFINGERDEATHPUNCH, CROSSBOW, KATANA, FORTYFIVEAUTO};

	if (tempWeapon == "Teaspoon")
		return TEASPOON;
	else if (tempWeapon == "Pitchfork")
		return PITCHFORK;
	else if (tempWeapon == "FiveFingerDeathPunch")
		return FIVEFINGERDEATHPUNCH;
	else if (tempWeapon == "Crossbow")
		return CROSSBOW;
	else if (tempWeapon == "Katana")
		return KATANA;
	else if (tempWeapon == "FortyFiveAuto")
		return FORTYFIVEAUTO;
	else if (tempWeapon == "NoWeapon")
		return NO_WEAPON;
}
LocationRec DetermineHumanPosition(int id, GameBoardClass& theBoard)
{
	LocationRec ans;

	ans.row = rand() % MAX_ROW + 1;
	ans.col = rand() % MAX_COL + 1;

	while (theBoard.IsOccupied(ans))
	{
		ans.row = rand() % MAX_ROW + 1;
		ans.col = rand() % MAX_COL + 1;
	}

	theBoard.SetPlayerID(ans, id);

	return ans;
}