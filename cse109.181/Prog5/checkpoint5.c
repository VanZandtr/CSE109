#ifndef NODE_H
#define NODE_H

#include<stdlib.h>

struct Node_t
{
	char* name;
	void* data;
	size_t size;
	struct Node_t* next;
};

void constructNode(struct Node_t*, const char*, void*, size_t, struct Node_t*);
void destroyNode(struct Node_t*);

const char* getName(struct Node_t*);
void* getData(struct Node_t*);
size_t getNodeSize(struct Node_t*);
struct Node_t* getNext(struct Node_t*);

void setName(struct Node_t*, char*);
void setData(struct Node_t*, void*, size_t);
void setNext(struct Node_t*, struct Node_t*);
#endif
#include<string.h>
#include<stdlib.h>
#include "Node.h"
void constructNode(struct Node_t* it, const char* name, void* data, size_t size, struct Node_t* next)
{
    if(data == NULL)
    {
        it->data = NULL;
    }
	else
	{
		void* newData = (void*)malloc(size);
   	 	memcpy(newData, data, size);
    	it->data = newData;
    	it->size = size;
	}
    if(name == NULL)
    {
        it->data = NULL;
    }
    else
    {
		char* newName = (char*)malloc(strlen(name)*sizeof(char)+1);
 	    strcpy(newName, name);
    	it->name = newName;

    }

	it->next = next;
}
void destroyNode(struct Node_t* it)
{
	free(it->name);
	free(it->data);
	it->name = NULL;
    it->data = NULL;
    it->size = 0;
}
const char* getName(struct Node_t* it)
{
	if(it == NULL)
	{
		return NULL;
	}
	if(it->name == NULL)
	{
		return NULL;
	}
	return it->name;
}
void* getData(struct Node_t* it)
{
	if(it == NULL)
    {
        return NULL;
    }
 	if(it->data == NULL)
    {
        return NULL;
    }

    return it->data;
}

size_t getNodeSize(struct Node_t* it)
{
 	if(it == NULL)
    {
        return 0;
    }
    return it->size;
}

struct Node_t* getNext(struct Node_t* it)
{
	if(it == NULL)
	{
		return NULL;
	}
    return it->next;
}

void setName(struct Node_t* it, char* name)
{
	if(it == NULL)
	{
		return;
	}
	free(it->name);
	if(name == NULL)
	{
		it->name = NULL;
	}
	else
	{
		char* newName = (char*)malloc(strlen(name)+1*sizeof(char));
		strcpy(newName, name);
		it->name = newName;
	}
}

void setData(struct Node_t* it, void* data, size_t size)
{
	if(it == NULL)
    {
        return;
    }
	free(it->data);
	if(data == NULL)
	{
		it->data = NULL;
		it->size = 0;
	}
	else
	{
 		void* newData = (void*)malloc(size);
    	memcpy(newData, data, size);
    	it->data = newData;
		it->size = size;
	}
}

void setNext(struct Node_t* it, struct Node_t* next)
{
	it->next = next;
}
