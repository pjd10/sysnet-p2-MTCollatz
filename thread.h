/** @file       thread.h
 *  @brief      This file holds the functions that handle all thread operations.
 *
 *  @author     Paul Davila (pjd10)
 *  @author     Christopher Blaylock (cdb56)
 *  @class      COP4634
 *  @assignment Project 2
 *
 *  @bug        No known bugs
 */

 // Include Definitions
#ifndef _THREAD_H_
#define _THREAD_H_

// Custom Definitions
#define T_MAX 	30
#define T_MIN	1
#define N_MAX 	1000000
#define N_MIN	1
#define C_MAX	1000
#define INT_MAX	4294967295

 // Global Variables
extern pthread_t thread[T_MAX];
extern int cStopCount[C_MAX];
extern int threadLock;
extern unsigned long int counter;
 


void createCollatzThreads(int numOfThreads, unsigned long *n);

void joinCollatzThreads(int numOfThreads);
void initThreadArray();

/**
 *@brief       			Thread function for collatz sequences.
 *						while the counter is less than "N" grab the next
 *						number and compute the collatzStoppingTime. Increment
 *						the array[collatzStoppingTime]
 *
 *@param n_void_ptr 	A void pointer that is an integer passed into the function
 *						that is casted into an int for use.
 *
 *@return				returns NULL.
 */
void *collatzThread(void *n_void_ptr);

/** @brief 	Retrieves the number of iterations needed for a number
 *			"a" to reach the end of the collatz sequence when the 
 *			sequence reaches 1.
 *
 * @param	a	Integer number of which we will retrieve
 *				the collatz stopping time.
 * 
 * @return 	the number i or the number of steps needed to reach
 *			the end of the collatz sequence.
 */
int getCollatzStoppingTime(unsigned long int a);

/** @brief 	Retrieves the next number in the collatz sequence.
 *
 * @param	n	Integer current number to find the next
 *				number in the sequence.
 * 
 * @return 	If n is even return n / 2.
 *			else return 3 * n + 1.
 */
unsigned long int getCollatzNextNumber(unsigned long int n);

void pErrorExit(char * msg, int eNum, int rVal);

#endif
