/*
Author:			Gregory D Hughes
Project:		Luke Nukem (Project 1)
Filename:		Particle.h
Purpose:		Hold details of particle in a particle list class object
*/
#ifndef PARTICLE_H
#define PARTICLE_H

#include "LocationListClass.h"			// List of locations a particle hase traveled to

struct ParticleRec
{
	short particleID;					// ID of a particle
	short pEnergy;						// Particles Energy
	LocationListClass LocationList;		// Array of positions that a particle has traveled to
	LocationRec currLoc;				// The current location a particle resides
	LocationRec prevLoc;				// The last position of the particle
};

#endif