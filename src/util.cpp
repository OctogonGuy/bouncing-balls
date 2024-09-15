#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void initRand()
{
	// Use current time as seed for random numbers
	srand(time(NULL));
}


int randInt(const int& lowerBound, const int& upperBound)
{
	// Error if upper bound is less than lower bound
	if (upperBound < lowerBound)
	{
		printf("Error in randInt(): upper bound (%d) less than lower bound (%d)", upperBound, lowerBound);
		exit(1);
	}

	// Return random number in range
	return rand()/((RAND_MAX + 1u)/(upperBound - lowerBound + 1)) + lowerBound;
}


float randFloat(const float& lowerBound, const float& upperBound)
{
	// Error if upper bound is less than lower bound
	if (upperBound < lowerBound)
	{
		printf("Error in randFloat(): upper bound (%f) less than lower bound (%f)", upperBound, lowerBound);
		exit(1);
	}

	// Return random number in range
	return rand()/(static_cast<float>(RAND_MAX + 1u)/(upperBound - lowerBound)) + lowerBound;
}
