/*
Author:			Gregory D Hughes
Project:		Luke Nukem
Filename:		SimulationClient.cpp
Input:			From File
Processing:		Using serveral class objects a simulation of radioactive particles and eco-protesters will take place. Class object that 
				will be used, will be a gameBoardClass object to place pariticle inside of a "reactor" or core and will be surrounded by a 
				track with eco protesters circleing the reactor collecting radioactive particles, a playerListClass will contain a list of
				four players who will absorb the particles energy, and a Particle Listt class will display statistic on the particles that
				are to be generated and depleated
Output:			output to file















Assumptions:	There will be less than 125 particles generated. 
				There will only be four players
Error
Handling:		None
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GameBoardClass.h"				// To create a gameBoard class object
#include "ParticleListClass.h"			// To create a class object to hold a list of particles
#include "PlayerListClass.h"			// To create a class object to hold a list of players
#include "LocationListClass.h"			// To create a class object to hold a list of locations
#include <iostream>						// For output to screen at the end of simulation
#include <string>						// For input from file at beging and output to screen at the end of simulation
#include <fstream>						// To read players from a file at the begining, and write to file at the end of simulation
#include <cmath>						// For converting a string to number

using namespace std;

//////////////////////////////////////////////////////////////////Constants/////////////////////////////////////////////////////////////////

const int SEED = 123456789;					// Seed for the RNG
const int NUM_PART_GEN = 25;				// The number of particles to be generated
const int PART_DEFAULT_ENG = 50;			// The default amount of energy a particle is generated with
const short NON_LOC_ROW = -1;				// Out of bounds location row
const short NON_LOC_COL = -1;				// Out of bounds location column
const short NON_DEATH = -1;					// Out of bounds level of death for a particle or player
const string FILENAME = "Datafile.dat";		// File containing the players
const string OUTFILE = "results.dat";		// File to write results to
const short NUM_PLAYERS = 4;				// The number of players client supports
const short MAX_SHORT_LEN = 5;				// The maximuim number of digits in a short
const short MIN_ROW_COL = 0;				// The minimum row & column in on the game board
const short DEATH = 0;						// Number that equate to particle or player death


// Enumerated type to calculate the direction all particles will move in
enum DirectionEnum{NORTH, SOUTH, WEST, EAST};

/////////////////////////////////////////////////////////////////Prototypes/////////////////////////////////////////////////////////////////

//Places players on the game board and assigns a location in the player list
void PlacePlayers(/*in/out*/GameBoardClass& theBoard,					// For board placement
					/*in/out*/PlayerListClass& players);				// For list generation

// Converts a string into a short
short ConvertStringToShort(/*in*/string inputStr);						// String to be converted

// Converts a string of a single charecter into a digit
short ConvertStringToDigit(/*in*/string inputstr);						// String of single char to be converted
	
// PLaces particles on the board and generates stats for the particle list
void PlaceParticles(/*in/out*/GameBoardClass& theBoard,					// For particle placement on the board
					/*in/out*/ParticleListClass& particles);			// For list generation

// Moves the particles once the simulation begins
void MoveParticles(/*in/out*/GameBoardClass& theBoard,					// For Board update
						/*in/out*/ParticleListClass& particles,			// List to update per particle
						/*in*/DirectionEnum& prevMoveDir,				// Last move direction to determine energy to move
						/*in*/short round);								// round to determine if the it is the initial move or not

//Returns the direction the particles will move in
DirectionEnum DetermineParticleDirection();

// Updates the particle at the current location in the list
LocationRec UpdateParticleLocation(/*in*/LocationRec currLoc,			// The current location to be updated
									/*in*/DirectionEnum dir);			// Direction to move the particle in

// Updates the current particle that is being updated
void UpdateParticleRec(/*in/out*/ParticleListClass& particles,			// Particle list ot update with new rec
						/*in/out*/GameBoardClass& theBoard,				// Board to update each position of the new particle placement
						/*in*/DirectionEnum moveDir,					// The direction to move each paricle in
						/*in*/short energyToMove);						// The required energy needed to move in determined direction

// Moves the players on the game board and within the list of players
void MovePlayers(/*in/out*/PlayerListClass& players,					// Player list to be updated
						/*in/out*/GameBoardClass& theBoard,				// Gameboard to be updated
						/*in/out*/ParticleListClass& particles,			// Particle list to update in the event of particle inactivity
						/*in*/short round);								// Round to record player death

// New location for a player depending on current location on the game board
LocationRec UpdatePlayerLocation(/*in/out*/LocationRec currLoc);		//location to be updated

// Update the current player record
void UpdatePlayerRec(/*in/out*/PlayerListClass& players,				// List of players to updated
						/*in/out*/GameBoardClass& theBoard,				// Board to update
						/*in/out*/ParticleListClass& particles,			// Particles to update in the event of a collision with protester
						/*in/out*/short round);							// Round of player death/Birthday!

// Predicates if the simulation will end
bool DetermineEndOfSimulation(/*in/out*/ParticleListClass& const particles);// List of particles determines end of simulation

// Print the result of the simulation
void PrintSimulationResults(/*in/out*/PlayerListClass& const players,		// List of player information
							/*in/out*/GameBoardClass& const  theBoard,		// Gameboard to be printed
							/*in/out*/ParticleListClass& const particles);	// List of particle information

// Write the game board to file
void PrintBoard(/*in/out*/GameBoardClass& const theBoard,				// Gameboard to be printed 
					/*in/out*/ofstream& dout);							// Stream to write to

// Write the particle details to file
void PrintParticles(/*in/out*/ParticleListClass& const particles,		// Particle list to print
						/*in/out*/ofstream& dout);						// Stream to write to

// Write player details to file
void PrintPlayers(/*in/out*/PlayerListClass& const players,				// Player list to print
						/*in/out*/ofstream& dout);						// Stream to write to

// Order the players by the 
PlayerListClass OrderPlayers/*in*/(PlayerListClass& players);			// Player list to order

// Print a line to file
void PrintLine(/*in/out*/ofstream& dout);								// Stream to write to

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	DirectionEnum prevMoveDir;	// Previous direction that particle moved
	short round = 0;			// round number.

	// Instantiate class objects
	GameBoardClass theBoard;
	PlayerListClass players;
	ParticleListClass particles;

	//Seed RNG
	srand(SEED);

	// Place players and particles
	PlacePlayers(theBoard, players);
	PlaceParticles(theBoard, particles);

	// Continue with the simulation until all particles are inactive
	while (!DetermineEndOfSimulation(particles))
	{
		// Move particles and players respectively
		MoveParticles(theBoard, particles, prevMoveDir, round);
		MovePlayers(players, theBoard, particles, round);
		
		// Increase round number
		round++;
	}

	// Once the simulation is complete print results
	PrintSimulationResults(players, theBoard, particles);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlacePlayers(/*in/out*/GameBoardClass& theBoard, /*in/out*/PlayerListClass& players)
//Pre:	PLayers and gameboard have been intialized
//Post:	Game board and players are updated
{
	ifstream din;					// Stream to read data from
	char delimiter = ',';			// Comma seperated values
	string tempLine;				// Line to store information
	short playerCt = 0;				// The number of players to generate
	PlayerRec tempPlayer;			// Record to hold a temporary player
	string playerIDStr;				// string to convert to an ID
	string playerName;				// name of temp player
	string playerLifeStr;			// TempPlayer Health
	LocationRec currLoc;			// Current location for player
	LocationRec nextLoc;			// The next location for following player
	LocationRec tempLoc;			// Temporary location for swap
	
	currLoc.row = MIN_ROW_COL;		// ASsign first location
	currLoc.col = MIN_ROW_COL;
	nextLoc.row = MIN_ROW_COL;		// Then the following location
	nextLoc.col = MAX_COL - 1;

	// Open the stream
	din.open(FILENAME.c_str());

	// Get the first player
	getline(din, playerIDStr, delimiter);
	getline(din, playerName, delimiter);
	getline(din, playerLifeStr);	

	// While there is information read from file upto the max number of players
	while (din && (playerCt < NUM_PLAYERS))
	{
		// collect the amount of life a player has
		playerLifeStr = playerLifeStr.substr(1,playerLifeStr.length()-1);

		// followed by player ID, and name
		tempPlayer.playerID = ConvertStringToShort(playerIDStr);
		tempPlayer.name = playerName;
		
		//Convert string value to number
		tempPlayer.health = ConvertStringToShort(playerLifeStr);

		// assign location for player
		tempPlayer.currLoc = currLoc;

		// Determine the next location for the following player
		tempLoc = currLoc;
		currLoc = nextLoc;

		// Move players placement clockwise
		// if the rows where the same assign new row
		if (currLoc.row == tempLoc.row && currLoc.row == MIN_ROW_COL)
			nextLoc.row = MAX_ROW-1;
		else if (currLoc.row == tempLoc.row && currLoc.row == MAX_ROW - 1)
			nextLoc.row = MIN_ROW_COL;
		//If the columns where the same assign new column
		if (currLoc.col == tempLoc.col && currLoc.col == MIN_ROW_COL)
			nextLoc.col = MAX_ROW-1;
		else if (currLoc.col == tempLoc.col && currLoc.col == MAX_COL - 1)
			nextLoc.col = MIN_ROW_COL;
			
		//Insert player
		players.Insert(tempPlayer);

		// Get next player
		getline(din, playerIDStr, delimiter);
		getline(din, playerName, delimiter);
		getline(din, playerLifeStr);
	}

	// set up game board
	players.FirstPosition();
	theBoard.SetPlayerID(players.Retrieve().currLoc, players.Retrieve().playerID);

	// Insert each player onto board
	while (!players.EndOfList())
	{
		players.NextPosition();
		theBoard.SetPlayerID(players.Retrieve().currLoc, players.Retrieve().playerID);
	}

	// Close the stream
	din.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

short ConvertStringToShort(/*in*/string inputStr)
// Pre:		A string value is determined
// Post:	A Short is returned to caller
{
	double ans = 0;							// Number to return
	double place = inputStr.length() - 1;	// Place holder
	double multiplicative;					// Multiplicative for calculation

	// make sure the number is valid
	if (inputStr.length() > MAX_SHORT_LEN)
		return 0;

	// Calculate the number
	while (place >= 0)
	{
		// find the first place of the string
		multiplicative = pow(10, (double) place);

		// Add ot answer
		ans = ans + (multiplicative * (double) ConvertStringToDigit(inputStr.substr(0, 1)));
		// adjust the string
		inputStr = inputStr.substr(1, inputStr.length() - 1);
		// Modify LCV
		place--;
	}

	// Return the answer
	return (short) ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

short ConvertStringToDigit(/*in*/string inputStr)
// Pre:		String is determined
// Post:	A digit of short length is returned to caller
{
	short ans;		// answet to return
	
	char* first;	// charecter to hold value

	// Determine value
	first = &inputStr[0];	

	// Switch on value
	switch (*first)
	{
	case '0': ans = 0; break;
	case '1': ans = 1; break;
	case '2': ans = 2; break;
	case '3': ans = 3; break;
	case '4': ans = 4; break;
	case '5': ans = 5; break;
	case '6': ans = 6; break;
	case '7': ans = 7; break;
	case '8': ans = 8; break;
	case '9': ans = 9; break;
	}

	// Return answer
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlaceParticles(/*in/out*/GameBoardClass& theBoard, /*in/out*/ParticleListClass& particles)
// Pre:		Particlelist has been Instantiated
// Post:	Particles are placed in the list and on the board
{
	ParticleRec tempPart;		// Temporary particle
	short numPartGen = 0;		// number of particles generated
	LocationRec nonLoc;			// Location to show that a particle has just been born
	
	// Fill non-Location
	nonLoc.row = NON_LOC_ROW;
	nonLoc.col = NON_LOC_COL;

	// Set default values for particles
	tempPart.pEnergy = PART_DEFAULT_ENG;
	tempPart.prevLoc = nonLoc;

	// generate particles
	while (numPartGen < NUM_PART_GEN)
	{
		// ID
		tempPart.particleID = numPartGen + 1;
		
		// Location
		tempPart.currLoc.row = (rand() % (MAX_ROW - TRACK_WID)) + 1;
		tempPart.currLoc.col = (rand() % (MAX_ROW - TRACK_WID)) + 1;
		
		tempPart.LocationList.Insert(tempPart.currLoc);

		// Increase the born and current particle number on gameboard location
		theBoard.IncreaseNumParticles(tempPart.currLoc);
		theBoard.PlusPlusBornParticls(tempPart.currLoc);

		// Insert new particle into list
		particles.Insert(tempPart);

		// Modify LCV
		numPartGen++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool DetermineEndOfSimulation(/*in*/ParticleListClass& const particles)
// Pre:		Particles have been placed
// Post:	Boolean expression if the simulation has come to an end is returned to caller
{
	//Move to first position in the particle list
	particles.FirstPosition();
	// if that particle is not dead the game is not over
	if (particles.Retrieve().pEnergy > DEATH)
		return false;

	// move to the next particles in the list
	while (!particles.EndOfList())
	{
		particles.NextPosition();
		// if that particle is not dead the game is not over
		if (particles.Retrieve().pEnergy > DEATH)
			return false;
	}

	// if all particles are dead, the simulation is over
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MoveParticles(/*in/out*/GameBoardClass& theBoard, /*in/out*/ParticleListClass& particles, /*in/out*/DirectionEnum& prevMoveDir, 
																														/*in*/short round)
// Pre:		Particles have been places on the board and are set up in the particle list
// Post:	Particles are moved
{
	// Direction to move particles must be determined
	DirectionEnum moveDir = DetermineParticleDirection();

	// Temporary record to update
	ParticleRec updateRec;
	
	// Energy required to move remains the same unless there is a change in direction
	short energyToMove = 1;

	// if the simulation is beginging then
	if (round == 0)
	{
		// Start with the first particle
		particles.FirstPosition();
		// Update particle
		UpdateParticleRec(particles, theBoard, moveDir, energyToMove);

		// and for the remaining particles
		while (!particles.EndOfList())
		{
			particles.NextPosition();
			// Update those particles
			UpdateParticleRec(particles, theBoard, moveDir, energyToMove);
		}

	}
	else// The simulation is still on going
	{
		// If there is a change in direction update cost to move
		if (prevMoveDir != moveDir)
			energyToMove = 2;

		// Start with the first particle in the list
		particles.FirstPosition();
		// Update first particle
		UpdateParticleRec(particles, theBoard, moveDir, energyToMove);

		// and for the remaining particles
		while (!particles.EndOfList())
		{
			particles.NextPosition();
			// Update each particle
			UpdateParticleRec(particles, theBoard, moveDir, energyToMove);
		}
	}

	// The previous move direction is set and returned to caller
	prevMoveDir = moveDir;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DirectionEnum DetermineParticleDirection()
// Pre:		The RNG is seeded
// Post:	Direction to move particles in is determined
{
	// Determine the direction based on enum type
	switch (rand() % 4)
	{
	case 0: return NORTH; break;
	case 1: return SOUTH; break;
	case 2: return WEST; break;
	case 3: return EAST; break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateParticleRec(/*in/out*/ParticleListClass& particles, /*in/out*/GameBoardClass& theBoard, /*in*/DirectionEnum moveDir, 
																												/*in*/short energyToMove)
// Pre:		The energy needed  and the direction to move is determined
// Post:	The particle is update in the list and on the board
{
	ParticleRec updateRec = particles.Retrieve();	// Gather the particle to be updated
	LocationRec prevLoc = updateRec.prevLoc;		// In case updateRec.prevLoc is overwriten

	// if the particle is within the core...
	if (theBoard.IsCore(updateRec.currLoc))
	{
		// The particle can be updated..
		updateRec.prevLoc = updateRec.currLoc;
		updateRec.currLoc = UpdateParticleLocation(updateRec.currLoc, moveDir);

		// energy required to move is added to the particles populating the new location
		energyToMove = energyToMove + theBoard.GetNumParticlesBorn(updateRec.currLoc);
		
		// if the particle is dead
		if (updateRec.pEnergy == DEATH)
		{
			//Do nothing
		}
		// if the particle has enough energy to move
		else if (updateRec.pEnergy > energyToMove)
		{
			// Update particle & gameboard
			updateRec.LocationList.Insert(updateRec.currLoc);
			updateRec.pEnergy = updateRec.pEnergy - energyToMove;
			theBoard.DecreaseNumParticles(updateRec.prevLoc);
			theBoard.IncreaseNumParticles(updateRec.currLoc);

			// If applicable increase the number of particles escaping the core.
			theBoard.PlusPlusEscapedParticles(updateRec.prevLoc, updateRec.currLoc);
			
			particles.UpdateItem(updateRec);
		}

		// else the particle will die upon move
		else
		{
			updateRec.currLoc = updateRec.prevLoc;
			updateRec.prevLoc = prevLoc;
			updateRec.pEnergy = DEATH;
			theBoard.DecreaseNumParticles(updateRec.currLoc);

			particles.UpdateItem(updateRec);
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LocationRec UpdateParticleLocation(/*in*/LocationRec currLoc, /*in*/DirectionEnum dir)
// Pre:		A dirction and current location is determined
// Post:	A new location is returned to caller
{
	// with the direction determined switch on direction
	switch (dir)
	{
	case NORTH: currLoc.row--; break;
	case SOUTH: currLoc.row++; break;
	case WEST: currLoc.col--; break;
	case EAST: currLoc.col++; break;
	}

	// return new position
	return currLoc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MovePlayers(/*in/out*/PlayerListClass& players, /*in/out*/GameBoardClass& theBoard, /*in/out*/ParticleListClass& particles, 
																														/*in*/short round)
// Pre:		Players have been placed and locations are determined
// Post:	Players are moved on the baord and the location list is updated
{
	// Go to first position
	players.FirstPosition();
	// Update player and board
	UpdatePlayerRec(players, theBoard, particles, round);

	// Continue through all players
	while (!players.EndOfList())
	{
		players.NextPosition();
		// Update player and board
		UpdatePlayerRec(players, theBoard, particles, round);
	}
	

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LocationRec UpdatePlayerLocation(/*in*/LocationRec currLoc)
// Pre:		Current location of player is determined
// Post:	A new location for player is determined
{
	// define the corners, for they have differing movement rules
	LocationRec nwCorner, neCorner, seCorner, swCorner;

	nwCorner.row = MIN_ROW_COL;		nwCorner.col = MIN_ROW_COL;
	neCorner.row = MIN_ROW_COL;		neCorner.col = MAX_COL - 1;
	seCorner.row = MAX_ROW - 1;		seCorner.col = MAX_COL - 1;
	swCorner.row = MAX_ROW - 1;		swCorner.col = MIN_ROW_COL;

	// Test if the player is in one of the corners
	// NW
	if (currLoc.row == nwCorner.row && currLoc.col == nwCorner.col)
		currLoc.col++;
	//NE
	else if (currLoc.row == neCorner.row && currLoc.col == neCorner.col)
		currLoc.row++;
	//SE
	else if (currLoc.row == seCorner.row && currLoc.col == seCorner.col)
		currLoc.col--;
	//SW
	else if (currLoc.row == swCorner.row && currLoc.col == swCorner.col)
		currLoc.row--;
	// Or if they are along one of the walls
	//North
	else if (currLoc.row == MIN_ROW_COL)
		currLoc.col++;
	//South
	else if (currLoc.row == MAX_ROW - 1)
		currLoc.col--;
	//West
	else if (currLoc.col == MIN_ROW_COL)
		currLoc.row--;
	//East
	else if (currLoc.col == MAX_COL - 1)
		currLoc.row++;
	
	// Return new location
	return currLoc;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdatePlayerRec(/*in/out*/PlayerListClass& players, /*in/out*/GameBoardClass& theBoard, /*in/out*/ParticleListClass& particles, 
																														/*in*/short round)
// Pre:		Players have been placed on the board and locations are set in the list
// Post:	Players and board are updated per record
{
	// retrieve the player record
	PlayerRec updateRec = players.Retrieve();
	// retreive the previous position
	LocationRec prevPos = updateRec.currLoc;
	// Temporary particle for updating particle list
	ParticleRec tempPart;

	// If the player is alive
	if (updateRec.health > DEATH)
	{
		// Update player
		updateRec.currLoc = UpdatePlayerLocation(prevPos);
		// Find particles in the cell, player moves to
		particles.Find(updateRec.currLoc);
		updateRec.health = updateRec.health - particles.Retrieve().pEnergy;
		// update particle
		tempPart = particles.Retrieve();
		tempPart.pEnergy = DEATH;
		particles.UpdateItem(tempPart);

		// move through all particles at location
		while (particles.FindNext(updateRec.currLoc))
		{
			updateRec.health = updateRec.health - particles.Retrieve().pEnergy;
			//Update particle			
			tempPart = particles.Retrieve();
			tempPart.pEnergy = DEATH;
			particles.UpdateItem(tempPart);
		}

		// Kill ecoprotester if nessecary
		if (updateRec.health < DEATH)
		{
			updateRec.health = DEATH;
			theBoard.SetUnoccupied(prevPos);
			theBoard.SetUnoccupied(updateRec.currLoc);
			players.UpdateItem(updateRec);
		}
		else//			or update eco Location
		{
			updateRec.currAge = round + 1;
			theBoard.SetUnoccupied(prevPos);
			theBoard.SetPlayerID(updateRec.currLoc, updateRec.playerID);
			players.UpdateItem(updateRec);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintSimulationResults(/*in*/PlayerListClass& const players, /*in*/GameBoardClass& const theBoard, 
																								/*in*/ParticleListClass& const particles)
// Pre:		Simulation is terminated	
// Post:	File with results is output
{
	// Open The stream
	ofstream dout;

	dout.open(OUTFILE.c_str());

	//Print the game board
	PrintBoard(theBoard, dout);

	// Print a line to seperate
	PrintLine(dout);

	// Print the details of each particle travel location
	PrintParticles(particles, dout);

	// Print a line to seperate
	PrintLine(dout);

	// Print the players in winning order
	PrintPlayers(players, dout);

	// Close the stream
	dout.close();

	// Show user where everything was printed
	cout << "Results of simulation printed to file \"" << OUTFILE << "\"" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintBoard(GameBoardClass& const theBoard, ofstream& dout)
// Pre:		Simulation is terminated	
// Post:	Gameboard is printed to file
{
	dout << "A for active, I for inactive; O for occupied and U for unoccupied; C for Core, T for track; " << endl
		<< "followed by player ID; number of particles born and the number of particles that escaped" << endl;

	string tempDetails;		// A temporary string to hold details about a gameboard location
	LocationRec tempLoc;

	for (int j = 0; j < MAX_ROW; j++)
	{
		tempLoc.row = j;
		
		for (int k = 0; k < MAX_COL; k++)
		{
			tempLoc.col = k;

			// set the first letter of the tempDetails string
			if (theBoard.IsActive(tempLoc))
				tempDetails = "A ";
			else
				tempDetails = "I ";
			// set the second letter of the tempDetails string
			if (theBoard.IsOccupied(tempLoc))
				tempDetails = tempDetails + "O ";
			else
				tempDetails = tempDetails + "U ";

			if (theBoard.IsCore(tempLoc))
				tempDetails = tempDetails + "C";
			else
				tempDetails = tempDetails + "T";

			// output the string along with the player ID in each cell
			dout << tempDetails << "\t\t";
		}

		dout << endl;

		for (int k = 0; k < MAX_COL; k++)
		{
			tempLoc.col = k;
			
			dout << theBoard.GetPlayerID(tempLoc) << " " << theBoard.GetNumParticlesBorn(tempLoc) << " " << theBoard.GetNumParticlesEscpaed(tempLoc) << "\t\t";
		}

		// Add a line in-between rows
		dout << endl << endl;
	}
	// Add an extra line in-between faces
	dout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintParticles(ParticleListClass& particles, ofstream& dout)
// Pre:		Simulation is terminated	
// Post:	particles are printed to file
{
	// List of locations temporary
	LocationListClass multiList;

	// Move to the first position in the particla list
	particles.FirstPosition();
	// Get the list of locations
	multiList = particles.Retrieve().LocationList.DetermineMultipleVisitSites();

	// if there were no multiple locations in list
	if (multiList.IsEmpty())
		dout << "Particle " << particles.Retrieve().particleID << " did not travel to a location multiple times." << endl;
	else
	{
		// otherwise print the multiples
		dout << "Particle " << particles.Retrieve().particleID << ", traveled to " << endl;
		dout << multiList.Retrieve().row << "x" << multiList.Retrieve().col << ", " << multiList.Retrieve().timesVisited << " times";
		while (!multiList.EndOfList())
		{
			multiList.NextPosition();
			dout << "; " << multiList.Retrieve().row << "x" << multiList.Retrieve().col << ", " << multiList.Retrieve().timesVisited << " times";
		}
		dout << "." << endl;
	}

	// Continue through all particles in the list
	while (!particles.EndOfList())
	{
		// modify LCV
		particles.NextPosition();

		//Get particle Multi-travel list
		multiList = particles.Retrieve().LocationList.DetermineMultipleVisitSites();

		// if there were no multiple locations in list
		if (multiList.IsEmpty())
			dout << "Particle " << particles.Retrieve().particleID << " did not travel to a location multiple times." << endl;
		else
		{
			// otherwise print the multiples
			dout << "Particle " << particles.Retrieve().particleID << ", traveled to ";
			dout << multiList.Retrieve().row << "x" << multiList.Retrieve().col << ", " << multiList.Retrieve().timesVisited << " times";
			while (!multiList.EndOfList())
			{
				multiList.NextPosition();
				dout << "; " << multiList.Retrieve().row << "x" << multiList.Retrieve().col << ", " << multiList.Retrieve().timesVisited << " times";
			}
			dout << "." << endl;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintPlayers(PlayerListClass& players, ofstream& dout)
// Pre:		Simulation is terminated	
// Post:	Players are printed to file
{
	// Order players by health
	PlayerListClass ordPlayers = OrderPlayers(players);

	// add space
	dout << endl << endl;

	// The first position is that of the winner
	ordPlayers.FirstPosition();
	dout << "The winner was " << ordPlayers.Retrieve().name << "(player " << ordPlayers.Retrieve().playerID << ") with "
		<< ordPlayers.Retrieve().health << " health remaing, living to a ripe age of " << ordPlayers.Retrieve().currAge
		<< endl << endl << "The runners up are as follows respectively:" << endl;

	// Print the remainging players
	while (!ordPlayers.EndOfList())
	{
		ordPlayers.NextPosition();
		dout << "Player " << ordPlayers.Retrieve().playerID << "\t" << ordPlayers.Retrieve().name << " with "
			<< ordPlayers.Retrieve().health << " health remaing, living to a ripe age of " << ordPlayers.Retrieve().currAge << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerListClass OrderPlayers(/*in/out*/PlayerListClass& const players)
// Pre:		Players are about to be printed
// Post:	Players are ordered and returned to caller
{
	PlayerListClass temp = players;		// temporary list to order
	PlayerListClass ans;				// corrected list to return to caller
	PlayerRec tempPlayer;				// Temporary player to hold			

	// Set tempPlayer to minimum values
	tempPlayer.health = NON_DEATH;
	tempPlayer.currAge = NON_DEATH;

	// shrink the list until a sorted list is determined
	while (temp.ReturnLength() > 0)
	{
		// Find healthiest player
		temp.FirstPosition();
		if (tempPlayer.health < temp.Retrieve().health)
			tempPlayer = temp.Retrieve();

		// for each player i nthe list
		while (!temp.EndOfList())
		{
			temp.NextPosition();
			if (tempPlayer.health < temp.Retrieve().health)
				tempPlayer = temp.Retrieve();
		}

		// remove and add player to respective lists
		temp.Find(tempPlayer);
		temp.Delete();
		ans.Insert(tempPlayer);

		// reset least player values
		tempPlayer.health = NON_DEATH;
		tempPlayer.currAge = NON_DEATH;
	}



	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintLine(ofstream& dout)
// Pre:		An output file stream is determined	
// Post:	A line is printed to file seperating data
{
	// Width of page in character
	int pageWidth = 120;
	// charecter to print on line
	for (int i = 0; i < pageWidth; i++)
		dout << "-";

	// Add space
	dout << endl;
}