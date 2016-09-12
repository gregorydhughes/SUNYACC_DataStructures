/*
Author:			Gregory D Hughes
Project:		Luke Nukem (Project 1)
Filename:		Location.h
Purpose:		Record a location within a game board (2-d array)
*/
#ifndef LOCATION_H
#define LOCATION_H

const int MAX_LIST_SIZE = 125;

struct LocationRec
{
	short row;			// Row position in game board
	short col;			// Column position in game board
	short timesVisited;	// Number of times a particle has visted a particular location
};

#endif