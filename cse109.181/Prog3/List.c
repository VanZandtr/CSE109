/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
List constructor and methods.
Program #3
*/

#include"List.h"
#include<stdlib.h>
#include<string.h>


struct List_t* makeList(struct List_t* list)
{
	//malloc here ??? list = (struct List_t*)malloc(1 * sizeof(struct List_t));
    list->size = 0;
	list->pointer = NULL;
   // makeNode1(list->pointer);
	return list;

}


struct List_t* freeList(struct List_t* list)
{
	if(list == NULL)
	{
		return NULL;
	}
	if(list->pointer == NULL)
	{
		free(list);
		return NULL;
	}
	helper((list->pointer));
	free(list);
	return NULL;
}


struct Node_t* helper(struct Node_t* node)
{
	if(getNext(node) != NULL)
	{
		helper(getNext(node));
	}
	freeNode(node);
	return NULL;
}


size_t size(struct List_t* list)
{
	if(list == NULL)
	{
		return -1;
	}
	return list->size;
}


struct Node_t* insert(struct List_t* list, int value)
{
	if(list->pointer  == NULL)
	{
		list->pointer = (struct Node_t*)malloc(1*sizeof(struct Node_t));
		makeNode2(list->pointer, value);
		list->size = (list->size +1);
		return list->pointer;
	}
	struct Node_t* current = (list->pointer);
	while(getNext(current) != NULL)
	{
		current = getNext(current);
    }
	struct Node_t* newNode = (struct Node_t*)malloc(1*sizeof(struct Node_t));
	newNode = makeNode2(newNode, value);
	setNext(current,newNode);
	current = getNext(current);
	list->size = list->size + 1;
	return current;
}


size_t find(struct List_t* list, int value)
{
 	size_t counter = 0;
	if(list->pointer  == NULL)
    {
        return 0;
    }
    struct Node_t* current = (list->pointer);
    while(getNext(current) != NULL)
    {
		if(getData(current) == value)// correct loop?
		{
			counter++;
		}
        current = getNext(current);
    }
	if(getData(current) == value)
	{
		counter++;
	}
    return counter;
}


size_t traverse(struct List_t* list, char* string)
{
	size_t stringSize = 0;
	if(list == NULL || list->pointer == NULL)
	{
		return stringSize;
	}
    struct Node_t* current = (list->pointer);
	while(current != NULL)
    {
		stringSize += sprintf(string + stringSize,"%i,", (current->data));
		//string = string + (current->data);
		//string = string + ',';
		current = getNext(current);
    }
	string[stringSize-1] = '\0';
	//string = string + (current->data);
	//string = string + '\0';
	return stringSize;
}

size_t removeItem(struct List_t* list, int value)
{
	 if(list == NULL)
    {
        return 0;
    }
    if(list->pointer == NULL)
    {
        return 0;
    }
	size_t counter = 0;
	while(list->pointer->data == value)
	{
		struct Node_t* temp = list->pointer;
	    list->pointer = getNext(temp);
		if(getNext(temp) == NULL)
		{
			free(temp);
			counter++;
			list->size--;
			return counter;
		}
        free(temp);
        counter++;
        list->size--;
	}
	struct Node_t* current = (list->pointer);
    while(getNext(current) != NULL)
    {
		if(current->next->data == value)
		{
			struct Node_t* temp = getNext(current);
			setNext(current, getNext(temp));//issues here
			free(temp);
			counter++;
			list->size--;
		}
		else
		{
        	current = getNext(current);
		}
    }
	if(current->data == value)
	{
		free(current);
		current = NULL;
		counter++;
		list->size--;
	}
	return counter;
}


char* traverse2(struct List_t* list)
{
	if(list->size == 0)
	{
		return NULL;
		//return malloc of size 0;
	}
	size_t maxStringSize = ((list->size)*11) + (list->size) + 500;//11 possible ints times number of nodes + number of nodes -1 (= commas)
	char* string = (char*)malloc(maxStringSize * sizeof(char));
	traverse(list, string);
	return string;
}



