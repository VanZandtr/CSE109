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

#include"Node.h"
#include<stdlib.h>
#include<string.h>


struct Node_t* makeNode1(struct Node_t* it)
{
   // it = (struct Node_t*)malloc(1 * sizeof(struct Node_t));
    it->next = NULL;
    it->data = 0;
    return it;
}


struct Node_t* makeNode2(struct Node_t* it, int data)
{
    //it = (struct Node_t*)malloc(1 * sizeof(struct Node_t));
	it->next = NULL;
    it->data = data;
    return it;
}


struct Node_t* makeNode4(struct Node_t* it, int data, struct Node_t* next)
{
    //it = (struct Node_t*)malloc(1 * sizeof(struct Node_t));
	//malloc Node_t* next?
    it->next = next;
    it->data = data;
    return it;
}

struct Node_t* freeNode(struct Node_t* it)
{
    free(it);
    return NULL;
}


int setData(struct Node_t* it, int data)
{
    it->data = data;
    return data;
}


struct Node_t* setNext(struct Node_t* it, struct Node_t* next)
{
    return it->next = next;
}


int getData(struct Node_t* it)
{
	return it->data;
}


struct Node_t* getNext(struct Node_t* it)
{
    return it->next;
}



