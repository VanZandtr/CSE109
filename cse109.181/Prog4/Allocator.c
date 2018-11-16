/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
Allocator file that takes
allocates and deallocates 
allocation objects within an
expandedable memory and stored 
array
Program #4
*/

#include "Allocator.h"
#include <stdlib.h>
#include <stdio.h>

void makeAllocator(struct Allocator_t* it, size_t capacity)
{
	if(capacity%16 != 0)
	{
		capacity += 16 - (capacity%16);
	}

	it->memory = (void*)malloc(capacity);
	it->allocationSum  = 0;
	it->capacity = capacity;
	it->allocationList = NULL;
	it->sizeList = 0;
	it->capacityList = 0;
}

void freeAllocator(struct Allocator_t* it)
{
	for(size_t i = 0; i< it->sizeList; i++)
	{
		freeAllocation(it->allocationList[i]);
	}
	free(it->allocationList);
	free(it->memory);
	free(it);
}

struct Allocation_t** addToList(struct Allocation_t** list, size_t* listSize, size_t* listCapacity, struct Allocation_t* newAllocation)
{
	if((*listSize) == (*listCapacity))
	{
            size_t newCapacity = ((*listCapacity) * 2) + 1;
            struct Allocation_t** temp = (struct Allocation_t**)malloc(newCapacity * sizeof(struct Allocation_t*));
            for(size_t i=0; i<(*listSize); i++)
            {
                temp[i] = list[i];//issue here, getting null pointers to 0x0 here
            }
            free(list);
            list = temp;
            temp = NULL;
            (*listCapacity) = newCapacity;
	}
	list[(*listSize)] = newAllocation;
	(*listSize)++;
	return list;
}

void* allocate(struct Allocator_t* it, size_t amt)
{
 	if(amt%16 != 0)
    {
        amt+= 16 - (amt%16);
    }

	if(amt > (it->capacity - it->allocationSum))
	{
		return NULL;
	}
	int overLap = 0;
	for(size_t i = 0; i< it->capacity; i= i +16)
	{
		overLap = 0;
		size_t end = i + amt;
		if(end > it->capacity)
		{
			return NULL;
		}
		if(amt > (it->capacity - it->allocationSum))
		{
			return NULL;
		}
		else
		{
			for(size_t j = 0; j < it->sizeList; j++)// should j be 0, 0 is accessing 0x0
			{
				if(doesOverlap(it->allocationList[j], i, amt) == 1)//allocationList[0] is accessing 0x0
				{
					overLap = 1;
				}
			}
			if(overLap == 1)
			{
				continue;
			}
			else
			{
				struct Allocation_t* newAllocation  = (struct Allocation_t*)malloc(sizeof(struct Allocation_t));
				makeAllocation(newAllocation, i, amt);
            	it->allocationList = addToList(it->allocationList, &(it->sizeList), &(it->capacityList), newAllocation);
            	it->allocationSum = it->allocationSum + newAllocation->size;
				return &(((char*)it->memory)[i]);
			}
		}
	}
	return NULL;
}

void deallocate(struct Allocator_t* it, void* ptr)
{
	if(it == NULL)
	{
		return;
	}
	if(ptr == NULL)
	{
		return;
	}
	for(size_t i = 0; i< it->sizeList; i++)
	{
		if((size_t)(ptr - it->memory) == (getAllocation(it,i))->start)
		{
			it->allocationSum -= (getAllocation(it,i))->size;
			freeAllocation(it->allocationList[i]);
			it->sizeList--;
			for(size_t j = i; j< it->sizeList; j++)
			{
				it->allocationList[j] = it->allocationList[j+1];
			}
			return;
		}
	}
	fprintf(stderr,"Corruption in free.");
	exit(1);
}

void* getBase(struct Allocator_t* it)
{
	return it->memory;
}

size_t getUsed(struct Allocator_t* it)
{
	return it->allocationSum;
}

size_t getCapacity(struct Allocator_t* it)
{
	return it->capacity;
}

struct Allocation_t* getAllocation(struct Allocator_t* it, size_t index)
{
	if(it == NULL )
    {
        return NULL;
    }
	else if((it->sizeList)== 0 || index >= it->sizeList)
	{
		return NULL;
	}
	return it->allocationList[index];
}

size_t numAllocations(struct Allocator_t* it)
{
	return it->sizeList;
}

void* riskyAlloc(struct Allocator_t* it, size_t size)
{
  if(size%16 != 0)
    {
        size+= 16 - (size%16);
    }

    if(size > (it->capacity - it->allocationSum))
    {
        return NULL;
    }

	int overLap = 0;
    for(size_t i = 0; i< it->capacity; i= i +16)
    {
        overLap = 0;
        size_t end = i + size;
        if(end > it->capacity)
        {
            //realloc more memory...
			if(realloc(it->memory, size) == NULL)
			{
				fprintf(stderr,"Bad realloc.");
				return NULL;
			}
        }
        for(size_t j = 0; j < it->sizeList; j++)
        {
            if(doesOverlap(it->allocationList[j], i, end) == 1)
            {
                overLap = 1;
            }
        }
        if(overLap == 1)
        {
            continue;
        }
        else
        {
                struct Allocation_t* newAllocation  = (struct Allocation_t*)malloc(sizeof(struct Allocation_t));
                makeAllocation(newAllocation, i, size);
                addToList(it->allocationList, &(it->sizeList), &(it->capacityList), newAllocation);
                it->allocationSum = it->allocationSum + newAllocation->size;
                return it->memory;
        }
    }
    return NULL;
}
