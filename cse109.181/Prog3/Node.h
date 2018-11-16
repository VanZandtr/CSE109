/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
Node's constructor file with prototypes.
Program #3
*/

#ifndef NODE_H
#define NODE_H


#include<stdio.h>

struct Node_t
{
	struct Node_t* next;
	int data;
};


struct Node_t* makeNode1(struct Node_t* it);
struct Node_t* makeNode2(struct Node_t* it, int data);
struct Node_t* makeNode4(struct Node_t* it, int data, struct Node_t* next);

struct Node_t* freeNode(struct Node_t* it);

int setData(struct Node_t* it, int data);
int getData(struct Node_t* it);

struct Node_t* getNext(struct Node_t* it);
struct Node_t* setNext(struct Node_t* it, struct Node_t* next);


#endif

