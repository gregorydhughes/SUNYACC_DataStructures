/*	Filename:		WalkingDeadClient.cpp
	Project:		Walking Dead (Project 1)
	Author:			Gregory Hughes
	Date:			October 7th 2014
	Input:			Input from file to create players
	Processing:
	Output:			Output winners to screen and to file
	Assumptions:	None
	Error
	Handling:		None
*/

//Libraries Used
#include "GameBoardClass.h"
#include <iostream>
#include <fstream>

// For cout and dout
using namespace std;

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//Constant  Declarations//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
const int SEED_VALUE = 123456789;					// Seed for random number generation

const int NUM_ZOMBIES = 10;							// The number of zombies introduced in the game

const int NUM_ROUNDS = 100;							// The Number of rounds to be played

const string IN_FILE_NAME = "six.in";				// Input File
const string OUT_FILE_NAME = "results.dat";			// Output File

enum DirectionEnum { NORTH, SOUTH, EAST, WEST };	// The directions players can move in

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\Prototypes\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void ZombieCreation(/*in/out*/ZListClass& zombieList,			// The list to generate our Zombies
					/*in/out*/GameBoardClass& theBoard);		// The game board we will be working with

void HumanAssignment(/*in/out*/HListClass& humanList,			// The List to be filled with players
					 /*in/out*/GameBoardClass& theBoard);		// The game board we will be working with

WeaponEnum DetermineWeapon(/*in*/string tempWeapon);			// String of the weapon to be converted

LocationRec DetermineHumanStartingPosition(/*in*/int id,		// ID of the curent player
										   /*in/out*/GameBoardClass& theBoard);	// The game board we will be working with

void HumanMove(/*in/out*/ZListClass& zombieList,				// List of zombies
			   /*in/out*/HListClass& humanList,					// List of humans
			   /*in/out*/GameBoardClass& theBoard,				// The game board we will be working with
			   /*in*/int round);								// The round number in case of deaths

int DetermineWeaponStrength(/*in*/WeaponEnum weapon);			// The Enumerated weapon type to determine weapon strength

void ZombieMove(/*in/out*/ZListClass& zombieList,				// List of zombies
				/*in/out*/HListClass& humanList,				// List of humans
				/*in/out*/GameBoardClass& theBoard,				// The game board we will be working with
				/*in*/int battleRound);							// The round number in case of deaths

void MovePlayers(/*in/out*/HListClass& humanList,				// Players to be moved
				 /*in/out*/GameBoardClass& theBoard);			// Board to be updated

DirectionEnum DetermineMoveDirection();

bool DetermineEndOfGame(/*in*/const ZListClass& zombieList,		// List for human success
						/*in*/const HListClass& humanList,		// List for zombie success
						/*in*/const int& battleRound);			// To determine if the max rounds have been played

void PrintGameOutcome(/*in*/const GameBoardClass& theBoard,		// The board for finding players and zombies
					  /*in*/ZListClass& zombieList,				// List of zombies
					  /*in*/HListClass& humanList,				// List of humans
					  /*in*/const int& battleRound);			// Round to determine if max rounds played

void PrintBoards(/*in*/const GameBoardClass& theBoard,			// The board for finding players and zombies
				 /*in*/ZListClass& zombieList,					// List of zombies
				 /*in*/HListClass& humanList,					// List of humans
				 /*in/out*/ofstream& dout);						// To write to file

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void main()
{
	// Seed RNG
	srand(SEED_VALUE);

	int battleRound = 0;			// Initialize battle
	bool endOfGame = false;			// The game has just begun

	GameBoardClass theBoard;		// Create board to battle
	ZListClass zombieList;			// Create hungry zombies
	HListClass humanList;			// Create humans 

	// Zombies Enter gameboard first
	ZombieCreation(zombieList, theBoard);

	// Players that enter gameboard
	HumanAssignment(humanList, theBoard);

	// For the ultimate test to see of players placed correctly
	endOfGame = DetermineEndOfGame(zombieList, humanList, battleRound);

	// Do battle
	while (!endOfGame)
	{
		// Modify LCV
		battleRound++;

		// Humans Attack First
		HumanMove(zombieList, humanList, theBoard, battleRound);

		// Zombies try to satify their hunger
		ZombieMove(zombieList, humanList, theBoard, battleRound);

		// Living players try to escape!
		MovePlayers(humanList, theBoard);

		// Determine if the max number of rounds were played or if humans or zombies won
		endOfGame = DetermineEndOfGame(zombieList, humanList, battleRound);
	}

	// Game's over! Print the results
	PrintGameOutcome(theBoard, zombieList, humanList, battleRound);

}// End Main

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void ZombieCreation(/*in/out*/ZListClass& zombieList,		//Zombies to be modified
					/*in/out*/GameBoardClass& theBoard)		// Gameboard to be modified
//Pre:		zombieList and theBoard have been instantiated
//Post:		Zombie list is filled and the pdms for theBoard have been set
{
	ZombieRec tempZombie;		// Temp zombie to work with
	int tempNum;				// Temporary nuber to use for zombie num and number of zombies on the board
	LocationRec tempLoc;		// Temporary location to be assigned to a zombie

	// Attributes all new baby zombies get assigned
	tempZombie.livingDead = true;	
	tempZombie.roundKilled = 0;
	tempZombie.strength = 5;
	tempZombie.biteCount = 0;
	tempZombie.killCount = 0;

	// Number assignment
	for (int i = 0; i < NUM_ZOMBIES; i++)
	{
		// Get the new zombie number
		tempNum = i + 1;
		tempZombie.zombieNum = tempNum;

		// Get a new location for baby zombie
		tempLoc.row = rand() % MAX_ROW + 1;
		tempLoc.col = rand() % MAX_COL + 1;
		tempZombie.loc = tempLoc;

		// Number of zombies on location gets incremented
		tempNum = theBoard.GetNumZombies(tempLoc) + 1;
		theBoard.ModNumZombies(tempLoc, tempNum);

		// Baby zombie inserted into list
		zombieList.Insert(tempZombie);
	}
}// End ZombieCreation

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void HumanAssignment(/*in/out*/HListClass& humanList,		// Human list to be modified
					 /*in/out*/GameBoardClass& theBoard)	// Gameboard that is being modified
//Pre:		humanList and theBoard have been instantiated
//Post:		humanList has been populated with players and theBoard has been updted with the players on location
{
	ifstream din;				// variable to read from file

	// open the file location
	din.open(IN_FILE_NAME);

	HumanRec tempHuman;			// Temp human struct to inset into list

	string tempLName;			// temp human first name
	string tempFNAme;			// temp human last name
	int tempLife;				// Life units for temp player
	string tempWeaponStr;		// string to read in player weapon
	WeaponEnum tempWeaponEnum;	// WEapon used by player
	LocationRec tempLoc;		// the location for a player
	int tempID = 0;				// the ID for players
	

	//Player initial attributes
	tempHuman.biteCount = 0;	
	tempHuman.killerID = -1;
	tempHuman.kills = 0;
	tempHuman.roundKilled = -1;
	tempHuman.alive = true;

	// priming read
	din >> tempFNAme >> tempLName >> tempLife >> tempWeaponStr;

	while (din)
	{
		// IDs start at one and go up
		tempID++;

		// Determine the weapon
		tempWeaponEnum = DetermineWeapon(tempWeaponStr);

		// determine the location
		tempLoc = DetermineHumanStartingPosition(tempID, theBoard);

		// Plug in values from file
		tempHuman.fName = tempFNAme;
		tempHuman.lName = tempLName;
		tempHuman.lifeUnits = tempLife;
		tempHuman.weapon = tempWeaponEnum;
		tempHuman.ID = tempID;
		tempHuman.loc = tempLoc;
		
		// Set what we have in our player struct
		theBoard.SetOccupied(tempLoc, true);
		humanList.Insert(tempHuman);

		// Modify LCV
		din >> tempFNAme >> tempLName >> tempLife >> tempWeaponStr;
	}

	// Close the stream
	din.close();

}// End HumanAssignment

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

WeaponEnum DetermineWeapon(/*in*/string tempWeapon)			//String representing weapon of player
//Pre:		A weapon has been read in from file
//Post:		The coresponding weapon has been returned to caller
{
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
}// End DetermineWeapon

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

LocationRec DetermineHumanStartingPosition(/*in*/int id,							// ID of player to be located on board
										   /*in/out*/GameBoardClass& theBoard)		// GameBoard to be modified
//Pre:		Player has been initialized with an ID
//Post:		The random board position that is unoccupied is set to occupied
{
	LocationRec ans;		// Location deemed appropriate for player

	// Get a location for player
	ans.row = rand() % MAX_ROW + 1;
	ans.col = rand() % MAX_COL + 1;

	// While that location is occupied with another player...
	while (theBoard.IsOccupied(ans))
	{
		// ...get another location
		ans.row = rand() % MAX_ROW + 1;
		ans.col = rand() % MAX_COL + 1;
	}

	// set player on board
	theBoard.SetPlayerID(ans, id);

	// Return the correct location to caller
	return ans;
}// End DetermineHumanPosition

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void HumanMove(/*in/out*/ZListClass& zombieList,		// List of zombies to be changed
			   /*in/out*/HListClass& humanList,			// List of humans to be changed
			   /*in/out*/GameBoardClass& theBoard,		// Game Board to be changed
			   /*in*/int battleRound)					// The current round of play
//Pre:		zombieList, humanList, theBoard have been initialized and battle round is updated for the current round of play
//Post:		All class objects are updated for the human move in the game
{
	// Go to first position in the list
	humanList.FirstPosition();

	// Temporary variables
	int tempZStrength;
	int tempNumZombies;

	// While not the end of the human list go through and do battle
	while (!humanList.EndOfList())
	{
		// So long as the human is alive
		if (humanList.IsHumanAlive())
		{
			// if there are more than 3 zombies on location
			if (theBoard.GetNumZombies(humanList.Retrieve().loc) >= 3)
			{
				tempNumZombies = theBoard.GetNumZombies(humanList.Retrieve().loc);

				zombieList.Find(humanList.Retrieve().loc);
				tempZStrength = zombieList.Retrieve().strength;
				// Split LU and ...
				tempZStrength = (humanList.Retrieve().lifeUnits / tempNumZombies) + tempZStrength;
				zombieList.AddBitenHuman(humanList.Retrieve().ID);
				zombieList.SetZombieStrength(tempZStrength, battleRound);

				// Distribute among Zombies
				for (int i = 1; i < tempNumZombies; i++)
				{
					tempZStrength = zombieList.Retrieve().strength;
					tempZStrength = (humanList.Retrieve().lifeUnits / tempNumZombies) + tempZStrength;
					zombieList.FindNext(humanList.Retrieve().loc);
					zombieList.AddBitenHuman(humanList.Retrieve().ID);
					zombieList.SetZombieStrength(tempZStrength, battleRound);
				}

				// Kill off human
				humanList.SetHumanLifeUnits(0, battleRound);
				humanList.SetKillerID(zombieList.Retrieve().zombieNum);
				theBoard.SetOccupied(humanList.Retrieve().loc, false);
				theBoard.SetPlayerID(humanList.Retrieve().loc, -1);

			}// End three+ found
			// Or if there are only two zombies
			else if (theBoard.GetNumZombies(humanList.Retrieve().loc) == 2)
			{
				// Attack first zombie found
				zombieList.Find(humanList.Retrieve().loc);
				tempZStrength = zombieList.Retrieve().strength;
				tempZStrength = tempZStrength - DetermineWeaponStrength(humanList.Retrieve().weapon);
				zombieList.SetZombieStrength(tempZStrength, battleRound);

				if (zombieList.Retrieve().strength == 0)
				{
					humanList.AddDeadZombie(zombieList.Retrieve().zombieNum);
					tempNumZombies = theBoard.GetNumZombies(humanList.Retrieve().loc);
					tempNumZombies--;
					theBoard.ModNumZombies(humanList.Retrieve().loc, tempNumZombies);

				}

				// Attack second zombie found
				zombieList.FindNext(humanList.Retrieve().loc);
				tempZStrength = zombieList.Retrieve().strength;
				tempZStrength = tempZStrength - DetermineWeaponStrength(humanList.Retrieve().weapon);
				zombieList.SetZombieStrength(tempZStrength, battleRound);

				if (zombieList.Retrieve().strength == 0)
				{
					humanList.AddDeadZombie(zombieList.Retrieve().zombieNum);
					tempNumZombies = theBoard.GetNumZombies(humanList.Retrieve().loc);
					tempNumZombies--;
					theBoard.ModNumZombies(humanList.Retrieve().loc, tempNumZombies);
				}

			}// End two Found

			// Just one?
			else if (theBoard.GetNumZombies(humanList.Retrieve().loc) == 1)
			{
				// Get that one
				zombieList.Find(humanList.Retrieve().loc);
				tempZStrength = zombieList.Retrieve().strength;
				tempZStrength = tempZStrength - DetermineWeaponStrength(humanList.Retrieve().weapon);
				zombieList.SetZombieStrength(tempZStrength, battleRound);

				if (zombieList.Retrieve().strength == 0)
				{
					humanList.AddDeadZombie(zombieList.Retrieve().zombieNum);
					tempNumZombies = theBoard.GetNumZombies(humanList.Retrieve().loc);
					tempNumZombies--;
					theBoard.ModNumZombies(humanList.Retrieve().loc, tempNumZombies);
				}

			}// End one found
		}// End Fightable human

		// Modify LCV
		humanList.NextPosition();
	}// End While

}// End HumanMove

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

int DetermineWeaponStrength(/*in*/WeaponEnum weapon)		// Type of weapon to determine strength
//Pre:		A weapon enum type has been determined
//Post:		The strength of a particular weapon is returned to caller
{
	switch (weapon)
	{
	case NO_WEAPON: return 0; break;
	case TEASPOON: return 1; break;
	case PITCHFORK: return 2; break;
	case CROSSBOW: return 3; break;
	case FIVEFINGERDEATHPUNCH: return 3; break;
	case KATANA: return 4; break;
	case FORTYFIVEAUTO: return 4; break;
	}
}// End DetermineWeaponStrength

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void ZombieMove(/*in/out*/ZListClass& zombieList,			// Zombies to be edited
				/*in/out*/HListClass& humanList,			// Humans to be edited
				/*in/out*/GameBoardClass& theBoard,			// Board to be edited
				/*in*/int battleRound)						// Battle round for time of death
//Pre:		zombieList, humanList, theBoard have been initialized and battle round is updated for the current round of play
//Post:		All class objects are updated for the zombie move in the game
{
	zombieList.FirstPosition();

	LocationRec tempLoc;
	int tempHumanLU;

	// Go through zombie list
	while (!zombieList.EndOfList())
	{
		// If the zombie can bite
		if (zombieList.IsZombieLivingDead())
		{
			// the zombie bites and the location is set
			tempLoc = zombieList.Retrieve().loc;

			// is the board has a human then the zombie has something to bite
			if (theBoard.IsOccupied(tempLoc))
			{
				// find that delicious human!
				humanList.Find(tempLoc);

				// 
				if (humanList.IsHumanAlive())
				{
					tempHumanLU = humanList.Retrieve().lifeUnits;
					tempHumanLU = tempHumanLU - zombieList.Retrieve().strength;

					humanList.IncreaseBiteCount(battleRound);
					humanList.SetHumanLifeUnits(tempHumanLU, battleRound);
					zombieList.AddBitenHuman(humanList.Retrieve().ID);


					if (!humanList.IsHumanAlive())
					{
						humanList.SetKillerID(zombieList.Retrieve().zombieNum);
						zombieList.AddDeadHuman(humanList.Retrieve().ID);
						theBoard.SetOccupied(tempLoc, false);
						theBoard.SetPlayerID(tempLoc, -1);
					}// End Dead human
				}// end LivingHuman test
			}// end Occupied location
		}// end LivingDead zombie test

		zombieList.NextPosition();
	}
}// End ZombieMove

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void MovePlayers(/*in/out*/HListClass& humanList,		// Human list to be edited
				 /*in/out*/GameBoardClass& theBoard)	// Gameboard to be edited
//Pre:		humanList and theBoard have been instantiated and a round has been played
//Post:		Human position updated within the players list and on gameBoard location
{
	// Find the direction to move in
	DirectionEnum playerMoveDir = DetermineMoveDirection();

	// Set first position
	humanList.FirstPosition();
	// Temp locations for placement tests
	LocationRec newLoc;
	LocationRec oldLoc;

	// While we still have people
	while (!humanList.EndOfList())
	{
		// And if they are alive
		if (humanList.Retrieve().alive)
		{
			// move players
			oldLoc = humanList.Retrieve().loc;
			newLoc = oldLoc;

			switch (playerMoveDir)
			{
			case NORTH:
				newLoc.row = newLoc.row - 1;
				break;
			case SOUTH:
				newLoc.row = newLoc.row + 1;
				break;
			case EAST:
				newLoc.col = newLoc.col + 1;
				break;
			case WEST:
				newLoc.col = newLoc.col - 1;
				break;
			}

			// but only if the cell is unoccupied
			if (!theBoard.IsOccupied(newLoc) && theBoard.IsActive(newLoc))
			{
				humanList.SetHumanLocation(newLoc);
				theBoard.SetOccupied(oldLoc, false);
				theBoard.SetPlayerID(oldLoc, -1);
				theBoard.SetOccupied(newLoc, true);
				theBoard.SetPlayerID(newLoc, humanList.Retrieve().ID);
			}
		}
		// Modify LCV
		humanList.NextPosition();
	}
}// End Move Players

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

DirectionEnum DetermineMoveDirection()
//Pre:		Move players has been called and a direction to move players in is needed by caller
//Post:		The direction for the player is determined and sent to caller
{
	int directionInt;

	// get a direction 0, 1, 2, or 3
	directionInt = rand() % 4;

	switch (directionInt)
	{
	case 0: return NORTH; break;		// 0
	case 1: return SOUTH; break;		// 1
	case 2: return EAST; break;			// 2
	case 3: return WEST; break;			// 3
	}
}// End DetermineMoveDirection

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

bool DetermineEndOfGame(/*in*/const ZListClass& zombieList,		//List of zombies to see if humans won
						/*in*/const HListClass& humanList,		//List of human to see if humans won
						/*in*/const int& battleRound)
//Pre:		A iteration of a round has been completed
//Post:		Whether the game is over is returned to caller
{
	//Maximum rounds played
	if (battleRound == NUM_ROUNDS)
		return true;

	// If no more zombies then the humans won!
	if (zombieList.GetNumZombies() == 0)
		return true;

	// If no more humans then the zombies won!
	if (humanList.HumansRemaining() == 0)
		return true;

	// if all else, then the game continues
	return false;
}// End DetermineEndOfGame

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void PrintGameOutcome(/*in*/const GameBoardClass& theBoard,		//The board to read results
					  /*in*/ZListClass& zombieList,				//Results of all zombies
					  /*in*/HListClass& humanList,				//Results of all players
					  /*in*/const int& battleRound)				//The round that the game made it to.
// Pre:		The game is over
// Post:	The results of the game are output to screen and file
{
	// Variables
	ofstream dout;		// To write to file
	string outcomeStr;	// The string to hold the outcome of game

	cout << "Filename for output will be \"" << OUT_FILE_NAME << "\"\n";

	// open the stream
	dout.open(OUT_FILE_NAME);
	
	// Print of the boards(winners and losers)
	PrintBoards(theBoard, zombieList, humanList, dout);
	
	// determine the end of game for print
	if (battleRound == NUM_ROUNDS)
	{
		outcomeStr = "Maximuim rounds played";
		cout << "\t" << zombieList.GetNumZombies() << " Zombies Remaining\n" << "\t" << humanList.HumansRemaining() << " Humans Remaining\n";
		dout << "\t" << zombieList.GetNumZombies() << " Zombies Remaining\n" << "\t" << humanList.HumansRemaining() << " Humans Remaining\n";
	}// end max rounds played
	else if (humanList.HumansRemaining() == 0)
	{
		outcomeStr = "Zombies are victorious! All the humans have had their brains thoroughly consumed by round ";
	}// end zombies win
	else if (zombieList.GetNumZombies() == 0)
	{
		outcomeStr = "Humans are victorious! All the zombies have been bludgeoned by round ";

		int maxPoints = 0;		// the maximum number of points
		int tempPoints;			// temp alue to hold current player points
		playerID winnerID;		// the Id of the winner(most points

		//First position
		humanList.FirstPosition();

		while (!humanList.EndOfList())
		{
			// only alive players can be winners
			if (humanList.Retrieve().alive)
			{
				//calculate points
				tempPoints = humanList.Retrieve().lifeUnits * 2 + humanList.Retrieve().kills * 5;
				//if those points are greater than anothers then that is the winner
				if (tempPoints > maxPoints)
				{
					maxPoints = tempPoints;
					winnerID = humanList.Retrieve().ID;
				}// end winning player judge
			}// end alive player judge

			// Modify LCV
			humanList.NextPosition();
		}// end determine most points on human

		// find what we found
		humanList.Find(winnerID);

		// print result to screen
		cout << humanList.Retrieve().fName << " " << humanList.Retrieve().lName << " won, with " << maxPoints << " points"
			<< ", killing " << humanList.Retrieve().kills << " zombies";
		dout << humanList.Retrieve().fName << " " << humanList.Retrieve().lName << " won, with " << maxPoints << " points"
			<< ", killing " << humanList.Retrieve().kills << " zombies.\n";

		// list zombies if there were any kills
		if (humanList.Retrieve().kills > 0)
		{
			cout << "(";
			for (int i = 0; i < humanList.Retrieve().kills - 1; i++)
				cout << humanList.Retrieve().killList[i] << ", ";
			cout << humanList.Retrieve().killList[humanList.Retrieve().kills - 1];
			cout << ")";
		}
		cout << "." << endl;
	}// end humans win

	cout << outcomeStr << battleRound << "."<< endl;
	dout << outcomeStr << battleRound << "." << endl;

	dout.close();
}// End print gameoutcome

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

void PrintBoards(/*in*/const GameBoardClass& theBoard,		//
				 /*in*/ZListClass& zombieList,
				 /*in*/HListClass& humanList,
				 /*in*/ofstream& dout)
// Pre:		The game is over
// Post:	The board is output to screen and printed to file
{
	LocationRec tempLoc;

	// Print a spacer
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < 80; i++)
	{
		cout << "-";
		dout << "-";
	}

	cout << endl;
	dout << endl;

	//Go through board for dead zombies and humans
	for (int i = 1; i <= MAX_ROW; i++)
	{
		tempLoc.row = i;
		
		// Humans first
		cout << "PlayerID\t\t";
		dout << "PlayerID\t\t";
		for (int j = 1; j <= MAX_COL; j++)
		{
			
			tempLoc.col = j;
			if (humanList.Find(tempLoc))
			{
				if (!humanList.IsHumanAlive())
				{
					cout << humanList.Retrieve().ID << "\t";
					dout << humanList.Retrieve().ID << "\t";
				}
				else
				{
					cout << "--\t";
					dout << "--\t";
				}
			}
			else
			{
				cout << "--\t";
				dout << "--\t";
			}
		}

		//Zombies next
		cout << endl << "ID of Dead Zombie\t";
		dout << endl << "ID of Dead Zombie\t";
		for (int j = 1; j <= MAX_COL; j++)
		{

			tempLoc.col = j;
			if (zombieList.Find(tempLoc))
			{
				if (!zombieList.IsZombieLivingDead())
				{
					cout << zombieList.Retrieve().zombieNum << "\t";
					dout << zombieList.Retrieve().zombieNum << "\t";
				}
				else
				{
					cout << "--\t";
					dout << "--\t";
				}
			}
			else
			{
				cout << "--\t";
				dout << "--\t";
			}
		}

		cout << endl << endl << endl;
		dout << endl << endl << endl;
	}// End dead out

	// Print a spacer
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < 80; i++)
		cout << "-";


	// Print living players and active zombies
	cout << "Living Players and number of living-dead zombies\n";
	dout << "Living Players and number of living-dead zombies\n";

	for (int i = 1; i <= MAX_ROW; i++)
	{
		tempLoc.row = i;

		cout << "PlayerID\t\t";
		dout << "PlayerID\t\t";

		// get players that are alive
		for (int j = 1; j <= MAX_COL; j++)
		{
			tempLoc.col = j;
			cout << theBoard.GetPlayerID(tempLoc) << "\t";
			dout << theBoard.GetPlayerID(tempLoc) << "\t";
		}

		cout << endl << "Player Points\t\t";
		dout << endl << "Player Points\t\t";

		// then their points
		for (int j = 1; j <= MAX_COL; j++)
		{
			tempLoc.col = j;
			if (humanList.Find(tempLoc)){
				cout << humanList.Retrieve().lifeUnits * 2 + humanList.Retrieve().kills * 5 << "\t";
				dout << humanList.Retrieve().lifeUnits * 2 + humanList.Retrieve().kills * 5 << "\t";
			}
			else
			{
				cout << "--\t";
				dout << "--\t";
			}
		}

		// Finally the remaining zombies
		cout << endl << "Zombies Remaining\t";
		dout << endl << "Zombies Remaining\t";

		for (int j = 1; j <= MAX_COL; j++)
		{
			tempLoc.col = j;
			cout << theBoard.GetNumZombies(tempLoc) << "\t";
			dout << theBoard.GetNumZombies(tempLoc) << "\t";
		}

		cout << endl << endl << endl;
		dout << endl << endl << endl;
	}// End living out
}// End print boards