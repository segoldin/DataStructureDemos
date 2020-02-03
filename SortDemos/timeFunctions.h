/* 
 * timeFunctions.h
 * 
 * Declaration of functions for measuring time in programs
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 *
 */
#ifndef TIME_FUNCTIONS_H
#define TIME_FUNCTIONS_H

/* Measure an interval in microseconds
 * Argument
 *   bStart      -  If true, record starting time
 *                  If false, return difference in microseconds
 * Return 0 if bStart is true, difference between
 * starting and ending calls in microseconds if bStart is false.
 */  
unsigned long recordTime(int bStart);

#endif
