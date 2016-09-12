/*
	Author:			Gregory D Hughes
	Date:			April 15th 2015
	Project:		CPU Simulation
	Filename:		CPUSimClient.cpp
	Purpose:		Simulate a CPU queue as items are placed into a wait queue and are processed in a round robin scheme, where each process 
					is either a IO or CPU intensive tast that will require either one tenth of a second or two tenths of a second, respectively
					per each slice of CPU time, and will have to be processed for a set amount of time either 10, 20, 30, or 60 sixty seconds 
					of processing time. Upon termination of program a file is writen that describes the parameters and the statistics of the 
					simulation.
	Input:			None
	Processing:		Use two queue, dynamic and static, to hold and process simulated jobs
	Output:			Prints statistics and parameters to file
	Assumptions:	None
	Exceptions
	Thrown:			None
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>					// To enable write to file
//#include <iostream>				// For testing only
#include "CLLQueueClass.h"			// Data structure for wait queue
#include "StaticQueueClass.h"		// Data structure for CPU queue

// To enable write to file
using namespace std;

//////////////////////////////////////////////////////////////////Declarations//////////////////////////////////////////////////////////////////

typedef int JobNum;						// typedef to describe a number of jobs

const string FILENAME = "CPUSim.out";	// File to write to

const int SEED = 123456789;				// seed for RNG
const JobNum NUM_JOBS = 250;			// Number of jobs to generate

const int ONE_JOB_PROB = 40;			// Probability of having one job simulated
const int TWO_JOB_PROB = 50;			// Probability of having at two jobs simulated (TWO_JOB - ONE_JOB)
const int NO_JOB_PROB = 100;			// Probability of having no jobs generated (NO_JOB - TWO_JOB)

const int IO_PROB = 65;					// Probability of an IO intensive task being genrated
const int CPU_PROB = 35;				// Probability of a CPU intensive task being generated

const int TEN_SEC = 50;					// Probability of a ten second task being generated
const int TWEN_SEC = 84;				// Probability of a twenty second task being generated
const int THIR_SEC = 95;				// Probability of a thirty second task being generated
const int SIXT_SEC = 100;				// Probability of a sixty second task being generated

const int SIZE_TEN = 10;				// Ten seconds
const int SIZE_TWEN = 20;				// Twenty seconds
const int SIZE_THIR = 30;				// Thrity seconds
const int SIZE_SIXT = 60;				// Sixty seconds

const int TENTHS_IN_SEC = 10;			// Tenths of a second in a second
const int TENTHS_IN_MIN = 600;			// Tenths of a second in a minute
const int TENTHS_IN_TEN = 6000;			// Tenths of a second in ten minutes
const int TENTHS_IN_HOUR = 36000;		// Tenths of a second in an hour

const int SECS_IN_HOUR = 3600;			// Seconds in an hour

const int IO_TIME = 1;					// tenth of a second process requires
const int CPU_TIME = 2;					// tenths of second process requires

///////////////////////////////////////////////////////////////////Prototypes///////////////////////////////////////////////////////////////////

// Generates each job for the wait queue
void GenerateJob(CLLQueueClass& waitQ,				// Wait queue for jobs pending
					StaticQueueClass& cpuQ,			// Queue for items processing
					JobNum& processed,				// Number of jobs generated
					second& time,					// Current system time
					ItemType& tempItem,				// Temporary job to deterime if the CPU is still processing an item
					second& waitTime,				// Total time all processed items spend in wait queue
					JobNum& ioCount,				// The count of all IO intensive tasks (total - IO = CPU)
					ofstream& dout);				// To write generated items to file

// returns the number of jobs to be generated
JobNum GetNumJobs();

// returns the job classification
JOBCLASS GetJobType(JobNum& ioCount);				// Number of IO tasks that must be modified for statistics

// returns the time required for a job
second GetJobTime();								

// Returns a probability 1 - 100
int GetProb();

// Processes the items within the CPU queue
void ProcessCPUQueue(CLLQueueClass& waitQ,			// Wait queue for jobs pending
						StaticQueueClass& cpuQ,		// Queue for items processing
						JobNum& processed,			// Number of jobs generated
						second& time,				// Current system time
						ItemType& tempItem,			// Temporary job to deterime if the CPU is still processing an item
						second& waitTime,			// Total time all processed items spend in wait queue
						second& cpuTime);			// Total time all items spend in the CPU queue

// If there is room in the queue and no other tasks are being processed waiting items are placed in the CPU
void MoveWaitJobToCPU(CLLQueueClass& waitQ,			// Structure to get the next item for CPU queue
						StaticQueueClass& cpuQ,		// Structure to place new item into
						second& time,				// Time to place the time entering CPU queue into
						second& waitTime);			// Time to increment total time spent waiting

// Predicates if the system clock is at a whole second
bool IsWholeSecond(second& time);					// Time to determine if system clock is on a whole second

// Predicates if the system clock has surpassed ten minutes
bool SurpassedTenMinutes(second& time);				// Time to determine if system is passed 10 minutes

// Predicates if the system clock is at a whole minute
bool IsWholeMinute(second& time);					// Time to determine if system clock is on a whole minute

// Returns the size of a dynamic queue
int GetCLLQueueSize(CLLQueueClass& waitQ);			// Queue to count size of

// Returns the size of a static queue
int GetStaticQueueSize(StaticQueueClass& cpuQ);		// Queue to count size of

// Prints the parameters of program to above file name
void PrintParam(ofstream& dout);					// Stream to write to

// Prints the statistics of the program upon termination
void PrintStats(JobNum& ioCount,					// Count of the IO intensive tasks generated
				second& waitTime,					// Total time processes spent in the wait queue
				second& cpuTime,					// Total time processes spent in the CPU queue
				second& time,						// Current system time
				ofstream& dout);					// Stream to write to

// Prints a line to seperate data in file
void PrintLine(ofstream& dout);						// Stream to write to

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	// Begin seeding RNG
	srand(SEED);

	// Creat and open stream to write to
	ofstream dout;
	dout.open(FILENAME);

	JobNum processed = 0;		// Number of jobs processed
	JobNum ioCount = 0;			// number of jobss that are IO intensive

	second time;				// System time
	second waitTime;			// Total time processes spend in wait
	second cpuTime;				// Total time processes spend bein processed

	// initialize system, wait and CPU times
	time.tenths = 0;
	waitTime.tenths = 0;
	cpuTime.tenths = 0;

	// Instantiat classes to be modified
	CLLQueueClass waitQ;
	StaticQueueClass cpuQ;

	// creata temporary item in the cance a process must be paused at interval seconds 
	ItemType tempItem;

	tempItem.key = 0;

	// Print the parameters for program
	PrintParam(dout);

	// Label the output for the jobs being generated
	dout << "Job Key\t\tJob Class\tCPU Time\tTime Entered" << endl;

	// Continue to generate jobs until the number of jobs generated is meet
	while (processed < NUM_JOBS)
	{
		// only generate jobs on whole second
		if (IsWholeSecond(time))
			GenerateJob(waitQ, cpuQ, processed, time, tempItem, waitTime, ioCount, dout);

		// process the items in the CPU
		ProcessCPUQueue(waitQ, cpuQ, processed, time, tempItem, waitTime, cpuTime);
	}

	// continue to process the CPU while the wait and CPU queues are occupied 
	while (!cpuQ.IsEmpty() && !waitQ.IsEmpty())
	{
		//Continue with round robin scheme until cpu Queue cleared
		ProcessCPUQueue(waitQ, cpuQ, processed, time, tempItem, waitTime, cpuTime);
	}

	// Once complete output results
	PrintStats(ioCount, waitTime, cpuTime, time, dout);

	// Close teh stream and create file
	dout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GenerateJob(CLLQueueClass& waitQ,				// Wait queue for jobs pending
					StaticQueueClass& cpuQ,			// Queue for items processing
					JobNum& processed,				// Number of jobs generated
					second& time,					// Current system time
					ItemType& tempItem,				// Temporary job to deterime if the CPU is still processing an item
					second& waitTime,				// Total time all processed items spend in wait queue
					JobNum& ioCount,				// The count of all IO intensive tasks (total - IO = CPU)
					ofstream& dout)					// To write generated items to file
// Pre:		All parameters are intialized
// Post:	Jobs are enqueue to wait or CPu if there is room
{
	// determin the number of jobs required at this integral second
	JobNum generate = GetNumJobs();

	// create a temporary job to be enqueued into system
	ItemType tempJob;

	// create jobs for the number of jobs to generate at this second
	for (int i = 0; i < generate; i++)
	{
		// set the Key for job
		tempJob.key = processed + 1;

		// set the time the job was put in wait
		tempJob.data.timeInW = time;

		// determine the type of process
		tempJob.data.type = GetJobType(ioCount);

		// Determine the time requirment for job
		tempJob.data.timeReq = GetJobTime();

		// enque item into wait
		waitQ.EnQ(tempJob);

		// if the time is less than 10 minutes
		if (!SurpassedTenMinutes(time))
		{
			// output each key of job generated
			dout << tempJob.key;
			
			// determine if job is IO or CPU intensive
			if (tempJob.data.type == IO)
				dout << "\t\tIO\t\t";
			else
				dout << "\t\tCPU\t\t";

			// and write the time required and hte time entering system
			dout << (tempJob.data.timeReq.tenths / TENTHS_IN_SEC) << "\t\t"
				<< (time.tenths / TENTHS_IN_SEC) << endl;
		}
		// or if the time is more than 10 minutes and at a whole minute
		else if (IsWholeMinute(time))
		{
			// print a summary for each minute surpassing ten minutes
			PrintLine(dout);

			// with the current time, the items in the wait queue, and the items in the CPU queue
			dout << time.tenths / TENTHS_IN_SEC << " seconds\n"
				<< GetCLLQueueSize(waitQ) << " items in wait\n"
				<< GetStaticQueueSize(cpuQ) << " items in CPU\n";

			// print the next items in each of the queues
			if (cpuQ.IsEmpty())
				dout << " no item is at the head of the CPU queue, and\n";
			else
				dout << cpuQ.Retrieve().key << " is at the head of the CPU queue, and\n";

			dout << waitQ.Retrieve().key << " is the next item to be placed in the CPU\n"
				<< endl;
		}

		// if the CPU Queue has room place the next tiem in wait into queue only if there is no item currently being processed
		if (tempItem.key == 0)
		{
			MoveWaitJobToCPU(waitQ, cpuQ, time, waitTime);
		}

		// Increment the number of processed items
		processed++;
	}// end for

}// End generate

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JobNum GetNumJobs()
// Pre:		The RNG has been seeded
// Post:	The number of jobs to be generated is returned
{
	// Get the probability
	int prob = GetProb();

	// Determine the number of jobs to generate based on probability
	if (prob <= ONE_JOB_PROB)
		return 1;
	else if (prob <= TWO_JOB_PROB)
		return 2;
	else
		return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JOBCLASS GetJobType(JobNum& ioCount)				// Number of IO tasks that must be modified for statistics
// Pre:		The RNG has been seeded, and ioCount has been intialized
// Post:	The type of job to be generated is returned	
{
	// Get the probability
	int prob = GetProb();

	// Determine the type of job to generate based on probability
	if (prob <= IO_PROB)
	{
		// If it was IO intensive increment count
		ioCount++;
		return IO;
	}
	else
		return CPU;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

second GetJobTime()
// Pre:		The RNG has been seeded
// Post:	The time requirment of a job to be generated is returned	
{
	// Get the probability
	int prob = GetProb();

	// temporary time data member to be returned
	second ans;

	// Determine the time requirement of a job to be generate based on probability
	if (prob <= TEN_SEC)
		ans.tenths = (SIZE_TEN * TENTHS_IN_SEC);
	else if (prob <= TWEN_SEC)
		ans.tenths = (SIZE_TWEN * TENTHS_IN_SEC);
	else if (prob <= THIR_SEC)
		ans.tenths = (SIZE_THIR * TENTHS_IN_SEC);
	else
		ans.tenths = (SIZE_SIXT * TENTHS_IN_SEC);
	
	// Return determined value
	return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GetProb()
// Pre:		The RNG has been seeded
// Post:	A number between 1 and 100 inclusive is returned
{
	// get a random number betwixt 1 and 100 inclusive
	int tempInt = ((rand() % 100) + 1);

	// For desk check
	//cout << tempInt << endl;

	// return the answer
	return tempInt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ProcessCPUQueue(CLLQueueClass& waitQ,			// Wait queue for jobs pending
						StaticQueueClass& cpuQ,		// Queue for items processing
						JobNum& processed,			// Number of jobs generated
						second& time,				// Current system time
						ItemType& tempItem,			// Temporary job to deterime if the CPU is still processing an item
						second& waitTime,			// Total time all processed items spend in wait queue
						second& cpuTime)			// Total time all items spend in the CPU queue
// Pre:		All parameters are intialized
// Post:	The queued items in the CPU queue are processed in a round robin scheme until the end of a whole second
{
	// create a record to record the current time with a simulated second
	second tempSec;

	// create a record to add to the temporary time
	int tempTime;

	// Initialize the current simulated second
	tempSec.tenths = 0;

	// continue to process with previous item or while not on a whole second and items are within the queue
	while (!cpuQ.IsEmpty() && tempSec.tenths < TENTHS_IN_SEC)
	{
		// only can insert items into cpu if they exist in the wait queue and there is nothing being processed
		if (!waitQ.IsEmpty() && tempItem.key == 0)
		{
			MoveWaitJobToCPU(waitQ, cpuQ, time, waitTime);
		}

		// Get the time slice of the current process
		// if we are still workng with a job from the last cycle
		if (tempItem.key != 0)
		{
			tempTime = IO_TIME;
		}
		// OR we get a new job
		else
		{
			// collect the first item in the CPU queue
			tempItem = cpuQ.Retrieve();
			cpuQ.DeQ();

			// determine the time slice requirement
			if (tempItem.data.type == IO)
				tempTime = IO_TIME;
			else
			{
				tempTime = CPU_TIME;
			}
		}

		// if the current time slice requires more time than that is available pause the current task midway through
		if (tempTime == CPU_TIME && ((tempSec.tenths + 1) == TENTHS_IN_SEC))
		{
			// Adjust the simulated second
			tempSec.tenths = tempSec.tenths + IO_TIME;

			// Adjust temporary item and save for the next processed cycle
			tempItem.data.timeReq.tenths = tempItem.data.timeReq.tenths - IO_TIME;
		}
		else
		{
			// Adjust the simulated second
			tempSec.tenths = tempSec.tenths + tempTime;

			// Adjust the temporary item
			tempItem.data.timeReq.tenths = tempItem.data.timeReq.tenths - tempTime;

			// if the item is not done processing place at the end of CPU queue
			if (tempItem.data.timeReq.tenths > 0)
				cpuQ.EnQ(tempItem);
			// Or adjust the time that items spent in the CPU until they were processed completely
			else
			{ 
				// record time out in record
				tempItem.data.timeOut = time;

				// adjust the time items spent inside of the CPU
				cpuTime.tenths = cpuTime.tenths + (tempItem.data.timeOut.tenths - tempItem.data.timeInC.tenths);
			}

			// reset the temporary item for cycle
			tempItem.key = 0;
		}

		// only can insert items into cpu if they exist in the wait queue and there is nothing being processed
		if (!waitQ.IsEmpty() && tempItem.key == 0)
		{
			MoveWaitJobToCPU(waitQ, cpuQ, time, waitTime);
		}
	}// end while

	time.tenths = time.tenths + TENTHS_IN_SEC;

}// End Process

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MoveWaitJobToCPU(CLLQueueClass& waitQ,			// Structure to get the next item for CPU queue
						StaticQueueClass& cpuQ,		// Structure to place new item into
						second& time,				// Time to place the time entering CPU queue into
						second& waitTime)			// Time to increment total time spent waiting
// Pre:		Parameters are intialized
// Post:	A porcessed is enqueued into the cpu queue if there is space
{
	// Only if hte CPU queue has room
	if (!cpuQ.IsFull())
	{
		// create a temporary job ot hold the wait queue item
		ItemType tempJob;

		// get the waiting item
		tempJob = waitQ.Retrieve();
		// set the time job enters CPU queue
		tempJob.data.timeInC = time;
		// Adjust the wait time object spend in wait for global statistic
		waitTime.tenths = waitTime.tenths + (tempJob.data.timeInC.tenths - tempJob.data.timeInW.tenths);

		// Remove the item from wait
		waitQ.DeQ();
		
		// Add item to CPU
		cpuQ.EnQ(tempJob);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsWholeSecond(second& time)					// Time to determine if system clock is on a whole second
// Pre:		System time has been intialized
// Post:	True is returned if the system time is at an integral second, false otherwise
{
	return ((time.tenths % 10) == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SurpassedTenMinutes(second& time)				// Time to determine if system clock surpassed ten minutes
// Pre:		System time has been intialized
// Post:	True is returned if the system time has surpassed ten minutes, false otherwise
{
	return (time.tenths >= TENTHS_IN_TEN);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsWholeMinute(second& time)					// Time to determine if system clock is on a whole minute
// Pre:		System time has been intialized
// Post:	True is returned if the system time is at an integral minute, false otherwise
{
	return ((time.tenths % TENTHS_IN_MIN) == 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GetCLLQueueSize(CLLQueueClass& waitQ)			// Queue to count size of
// Pre:		A circular link list (CLL) queue class object has been initialized
// Post:	The number of items in a CLL is returned to caller
{
	// Creat a temporary queue to hold values of items in a queue
	CLLQueueClass tempQ;

	// create a temporary item to hold each member of a queue
	ItemType temp;

	// initialize a count to return to caller
	int count = 0;

	// count the elements in the list while elements remain
	while (!waitQ.IsEmpty())
	{
		// move the element to a new list to modify LCV
		temp = waitQ.Retrieve();
		waitQ.DeQ();
		tempQ.EnQ(temp);

		// increment count
		count++;
	}

	// set the now empty queue to the temporary queue
	waitQ = tempQ;

	// return the number of elements
	return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int GetStaticQueueSize(StaticQueueClass& cpuQ)		// Queue to count size of
// Pre:		A static array based queue class object has been initialized
// Post:	The number of items in a queue is returned to caller
{
	// Creat a temporary queue to hold values of items in a queue
	StaticQueueClass tempQ;

	// create a temporary item to hold each member of a queue
	ItemType temp;

	// initialize a count to return to caller
	int count = 0;

	// count the elements in the list while elements remain
	while (!cpuQ.IsEmpty())
	{
		// move the element to a new list to modify LCV
		temp = cpuQ.Retrieve();
		cpuQ.DeQ();
		tempQ.EnQ(temp);

		// increment count
		count++;
	}

	// set the now empty queue to the temporary queue
	cpuQ = tempQ;

	// return the number of elements
	return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintParam(ofstream& dout)						// Stream to write to
// Pre:		Stream to write to is initialized
// Post:	THe program's parameters are printed to file
{
	// Print all constants of program
	dout << "RNG seed:\t" << SEED << endl
		<< NUM_JOBS << " jobs to be generated." << endl
		<< endl
		<< ONE_JOB_PROB << "% probability of one job being generated" << endl
		<< TWO_JOB_PROB - ONE_JOB_PROB << "% probability of two jobs being generated" << endl
		<< NO_JOB_PROB - ((TWO_JOB_PROB - ONE_JOB_PROB) + ONE_JOB_PROB) << "% probability of no jobs being generated" << endl
		<< endl
		<< IO_PROB << "% of INput/output intesive task generated" << endl
		<< CPU_PROB << "% of CPU intesive task being generated" << endl
		<< endl
		<< TEN_SEC << "% chance of task taking 10 seconds of CPU time" << endl
		<< TWEN_SEC - TEN_SEC << "% chance of task taking 20 seconds of CPU time" << endl
		<< THIR_SEC - TWEN_SEC << "% chance of task taking 30 seconds of CPU time" << endl
		<< SIXT_SEC - THIR_SEC << "% chance of task taking 60 seconds of CPU time" << endl;

	// Print a line to seperate data
	PrintLine(dout);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintStats(JobNum& ioCount,					// Count of the IO intensive tasks generated
				second& waitTime,					// Total time processes spent in the wait queue
				second& cpuTime,					// Total time processes spent in the CPU queue
				second& time,						// Current system time
				ofstream& dout)						// Stream to write to
// Pre:		The simulation is terminated and numbers to determine statistics are set, file stream is inititialized
// Post:	The statistics of simulation are printed to file
{
	// Seperate data in file
	PrintLine(dout);

	// Print the statistics of simulation
	dout << ioCount << " jobs that were IO intensive\n"
		<< NUM_JOBS - ioCount << " jobs that were CPU intensive" << endl
		<< (cpuTime.tenths / TENTHS_IN_SEC) / NUM_JOBS << " seconds on average spent in the CPU" << endl
		<< (NUM_JOBS * TENTHS_IN_HOUR) / time.tenths  << " jobs processed per hour" << endl	// processed in a tenth of a second
		<< (waitTime.tenths / TENTHS_IN_SEC) / NUM_JOBS<< " seconds on average spent in the wait queue" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintLine(ofstream& dout)						// Stream to write to
// Pre:		File stream is initialized
// Post:	A line(hyphens) is printed to file seperating data
{
	// width to print line to
	int width = 80;

	// space above line
	dout << endl;

	// Hyphens making up line
	for (int i = 0; i < width; i++)
		dout << "-";

	// Space below line
	dout << endl;
}