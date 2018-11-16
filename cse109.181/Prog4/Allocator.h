/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
Allocator's constructor file with prototypes.
Program #4
*/

#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include"Allocation.h"
#include<stdio.h>

struct Allocator_t
{
	size_t allocationSum;
    void* memory;
    size_t capacity;
	struct	Allocation_t** allocationList;
	size_t sizeList;
	size_t capacityList;
};

struct Allocation_t** addToList(struct Allocation_t** list, size_t* listSize, size_t* listCapacity, struct Allocation_t* newAllocation);

void makeAllocator(struct Allocator_t* it, size_t capacity);

void freeAllocator(struct Allocator_t* it);

void* allocate(struct Allocator_t* it, size_t amt);

void deallocate(struct Allocator_t* it, void* ptr);

void* getBase(struct Allocator_t* it);

size_t getUsed(struct Allocator_t* it);

size_t getCapacity(struct Allocator_t* it);

struct Allocation_t* getAllocation(struct Allocator_t* it, size_t index);

size_t numAllocations(struct Allocator_t* it);

void* riskyAlloc(struct Allocator_t* it, size_t size);

#endif


