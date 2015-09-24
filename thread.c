/** @file       thread.c
 *  @brief      File that implements the fuctions of thread.h
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
#include <pthread.h>
#include <time.h>
#include "thread.h"

int collatzSequence(unsigned long int n, int i)
{
	if(n == 1)
		return i;

	else if ((n % 2) == 0)
	{
		n = n / 2;
		i++;
		return collatzSequence(n, i);
	}
	else if((n % 2) != 0)
	{
		n = 3 * n + 1;
		i++;
		return collatzSequence(n, i);
	}

	return i;	
}
