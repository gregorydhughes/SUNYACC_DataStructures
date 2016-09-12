/*
Author:			Gregory D Hughes
Date:			April 15th 2015
Project:		CPU Simulation
Filename:		ItemType.h
Purpose:		Throw exceptions based on a queue implementation
*/

#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include "ExceptionClass.h"		// Classes for exceptions

// keyType integer
typedef int keyType;

// types of jobs that are available
enum JOBCLASS{ IO, CPU };

// Unit of time
struct second
{
	int tenths;				// time unit in tenths of a second
};

// Used to hold details of a simulated job
struct job
{
	JOBCLASS type;			// type of job in queue
	second timeInW;			// time entering wait queue
	second timeInC;			// time entering the CPU queue
	second timeOut;			// time process finishes execution
	second timeReq;			// the time required for the process
};

// Item to be used in queues
struct ItemType
{
	keyType key;			// Key for each job
	job data;				// struct to hold details about job
};

#endif