/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
List Constructor and prototypes
Program #3
*/
#ifndef LIST_H
#define LIST_H

#include"Node.h"
#include<stdio.h>


struct List_t
{
    size_t size;
    struct Node_t* pointer;
};

struct Node_t* helper(struct Node_t* node);

struct List_t* makeList(struct List_t* list);

struct List_t* freeList(struct List_t* list);

size_t size(struct List_t* list);

struct Node_t* insert(struct List_t* list, int value);

size_t find(struct List_t* list, int value);

size_t traverse(struct List_t* list, char* string);

size_t removeItem(struct List_t* list, int value);

char* traverse2(struct List_t* list);

#endif

