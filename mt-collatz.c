/** @file       mt-collatz.c
 *  @brief      Main file for the program
 *
 *  @author     Paul Davila (pjd10)
 *  @author     Christopher Blaylock (cdb56)
 *  @class      COP4634
 *  @assignment Project 2
 *
 *  @bug        No known bugs
 */

 // Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "thread.h"

int main(int argc, char *argv[])
{
	struct timespec start, end;

	char *ptr;
	double elapsedTime, totalTime;
	unsigned long int number = 0;
	int i = 0;

	unsigned long int N = strtoul(argv[1], &ptr, 10);
	int T = atoi(argv[2]);

	if(N > MAX_INT)
	{
		fprintf(stderr,"OVERFLOW!\n");
		return 0;
	}

	for (number = 2; number < N; number++) 
	{
		i = 0;
		elapsedTime = 0;
		if(clock_gettime(CLOCK_REALTIME, &start) == -1)
		{	
			fprintf(stderr,"Time Error!\n");
			return 0;
		}

		i = collatzSequence(number, i);

		if(clock_gettime(CLOCK_REALTIME, &end) == -1)
		{	
			fprintf(stderr,"Time Error!\n");
			return 0;
		}

		elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/BILLION;
		//printf("number: %ld\nsteps: %d\ntime: %.9lf\n", number, i, elapsedTime);
		totalTime += elapsedTime;
	}
	printf("Total Time: %lf\n", totalTime);
	return 0;
}
