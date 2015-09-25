/** @file   mt-collatz.c
 *  @brief  Main file for computing collatz sequences
 *
 *  @author Paul Davila (pjd10)
 *  @author Christopher Blaylock (cdb56)
 *	@class	COP4634
 *	@assignment	Project 2
 *
 *  @bug    No known bugs
 */

 // Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "thread.h"

// Global Variable
pthread_t thread[T_MAX];
int cStopCount[C_MAX];
int threadLock = 1;
unsigned long int counter = 2;

// Function Definitions
void initIntArray(int * array, int capacity);

/** @brief mt-collatz entry point.
 *  
 *  This is the entry point for mt-collatz where
 *	we will retrieve the value "N" number of colltaz
 *	sequences we will computer and "T" number of threads
 * 	we will use to compute these sequences.
 *
 * @param	argc	Number of arguments
 * @param	argv	Vector with the string arguments
 * 
 * @return 	will return 0 upon successful completion of
 *			the program.
 */
int main(int argc, char *argv[])
{
	// Initialize Array
	initIntArray(cStopCount, C_MAX);
	
	struct timespec start, end;
	unsigned long nCount = 0;
	int tCount = 0;
	
	// Retrieve Arguments
	if(argc < 3)
		pErrorExit("Incorrect number of arguments: ./mt-collatz [# of collatz seq] [# of threads]\n", 0, -1);

	if(argv[1] != NULL)
		sscanf(argv[1], "%lu", &nCount);
	if(argv[2] != NULL)
		sscanf(argv[2], "%d", &tCount);
	
	// Argument Error Checking
	if(tCount < T_MIN || tCount > T_MAX)
		pErrorExit(NULL, 1, -1);
		
	if(nCount < N_MIN || nCount > INT_MAX)
		pErrorExit(NULL, 2, -1);
	
	// Get Ready to Go
	clock_gettime(CLOCK_REALTIME, &start);
	threadLock = 0;
	
	// Create Threads
	createCollatzThreads(tCount, &nCount);
	
	// Join Threads
	joinCollatzThreads(tCount);

	// Time
	clock_gettime(CLOCK_REALTIME, &end);
	fprintf(stderr, "%lu,%d,%lu.%lu\n", nCount, tCount, end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
	
	int i = 0;
	
	for(i = 0; i < C_MAX; i++)
	{
		if(cStopCount[i] != 0)
			fprintf(stdout, "Index: %d, Count: %d\n", i, cStopCount[i]);
	}
	
	return 0;
}

/**
 *@brief       	Initializes an integer array of size N. Setting all values
 *				from 0 - size = 0.
 *
 *@param array 		A pointer to the array we will be zero-ing out.
 *@param capacity	Capacity of the array.
 *
 *@return				returns NULL.
 */
void initIntArray(int * array, int capacity)
{
	int i = 0;
	for(i = 0; i < capacity; i++)
		array[i] = 0;
	return;
}
