/** @file       thread.c
 *  @brief      Implements the functions of thread.h.
 *
 *  @author     Paul Davila (pjd10)
 *  @author     Christopher Blaylock (cdb56)
 *  @class      COP4634
 *  @assignment Project 2
 *
 *  @bug        No known bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include "thread.h"

void createCollatzThreads(int numOfThreads, unsigned long *n)
{
	initThreadArray();
	void *num = (void *)n;
	
	int i = 0;
	for(i = 0; i < numOfThreads; i++)
	{
		if(pthread_create(&thread[i], NULL, &collatzThread, num))
			pErrorExit("Error creating thread.\n", 0, -1);
	}
	return;
}

void joinCollatzThreads(int numOfThreads)
{
	int i = 0;
	for(i = 0; i < numOfThreads; i++)
	{
		if(pthread_join(thread[i], NULL))
			pErrorExit("Error joining from thread.\n", 0, -1);
	}
	return;
}

/**
*	Initialize Thread Array
 */
void initThreadArray()
{
	int i = 0;
	for(i = 0; i < T_MAX; i++)
		thread[i] = 0;

	return;
}

/**
*	Initialize Collatz Thread
 */
void *collatzThread(void *n_void_ptr)
{
	//pthread_t t_id = pthread_self();
	unsigned long int temp = 0;
	
	// Wait for all threads to be created.
	/*while(threadLock)
		sched_yield();*/
		
	unsigned long int *n_ptr = (unsigned long int *)n_void_ptr;
	
	while(counter <= *n_ptr)
	{
		temp = counter++;
		cStopCount[getCollatzStoppingTime(temp)]++;
		//fprintf(stdout, "T: %lu\tN:%lu\tK:%d\n", t_id, temp, getCollatzStoppingTime(temp));
	}
	
	pthread_exit(NULL);
	return NULL;
}

/**
*	Retrieve the Collatz Stopping Time in Steps
*/
int getCollatzStoppingTime(unsigned long int a)
{
	int i = 0;
	unsigned long int n = 0;
	
	for(n = a; n > 1; i++)
		n = getCollatzNextNumber(n);

	return i;
}

/** 
 * 	Retrieve the Next Number in the Collatz Sequence
 */
unsigned long int getCollatzNextNumber(unsigned long int n)
{
	if( (n % 2) == 0)
		return (n / 2);
	else
		return (3*n + 1);
}

// Work in Progress
void pErrorExit(char * msg, int eNum, int rVal)
{
	switch(eNum)
	{
		case 1:
			fprintf(stderr, "Argument # of threads must be between %d and %d\n", T_MIN, T_MAX);
			break;
		case 2:
			fprintf(stderr, "Argument # of collatz seq must be between %d and %d\n", N_MIN, N_MAX);
			break;
		default:
			if(msg != NULL)
				fprintf(stderr, msg);
			break;
	}
	
	exit(rVal);
}
