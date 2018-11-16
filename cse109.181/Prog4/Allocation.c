/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
Allocaiton.c create allocation objects
and accessors to get start and size of 
allocation objects.
Program #4
*/


#include "Allocation.h"
#include <stdio.h>
#include <stdlib.h>
void makeAllocation(struct Allocation_t* it, size_t start, size_t size)
{
	it->start = start;
	it->size = size;
}

void freeAllocation(struct Allocation_t* it)
{
	//destroy?
	free(it);
}

size_t getStart(struct Allocation_t* it)
{
	if(it == NULL)
    {
        return 0 ;
    }
	return it->start;
}

size_t getEnd(struct Allocation_t* it)
{
	if(it == NULL)
    {
        return 0 ;
    }
	size_t end = it->start + it->size;
	return end;
}

size_t getSize(struct Allocation_t* it)
{
	if(it == NULL)
	{
		return 0 ;
	}
	return it->size;
}

int doesOverlap(struct Allocation_t* it, size_t start, size_t size)
{
	if(it == NULL)
	{
		return 1;
	}
	if(getEnd(it) > start && getEnd(it) <= start+size)
	{
		return 1;
	}
	if(start+size > getStart(it) && start+size <= getEnd(it))
	{
		return 1;
	}
	return 0;
}

