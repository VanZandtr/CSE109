#include"Item.h"
#include<stdlib.h>
#include<string.h>

// Item_t x = new Item_t();		//Java equivalent
// struct Item_t* x = makeItem();
struct Item_t* makeItem()
{
	struct Item_t* retval = (struct Item_t*)malloc(1 * sizeof(struct Item_t));
	retval->name = NULL;
	retval->weight = 0;
	retval->cost = 0;
//	(*retval).cost = 0;
	return retval;
}


//Proper way to create an Item_t, 
//All functions of an object take the object itself as explicit argument in C
//unlike implicitly in Java/C++ with the "this" argument.
struct Item_t* constructItem(struct Item_t* it)
{
	it->name = NULL;
	it->weight = 0;
	it->cost = 0;
	return it;
}


/*
	freeItem(x);
	x = NULL;

	x = freeItem(x);

*/
struct Item_t* freeItem(struct Item_t* it)
{
	free(it->name);
//	it->name = NULL;
	free(it);
//	it = NULL;
//	return it;
	return NULL;
}

int setWeight(struct Item_t* it, int weight)
{
	if(weight < 0)
	{
		return -1;
	}
	if(it == NULL)
	{
		return -1;
	}
	it->weight = weight;
	return weight;
}

int setCost(struct Item_t* it, int cost)
{
	if(cost < 0)
	{
		return -1;
	}
	if(it == NULL)
	{
		return -1;
	}
	return it->cost = cost;
}

char* setName(struct Item_t* it, char* name)
{
	if(it == NULL)
	{
		return NULL;
	}
	size_t length = strlen(name) + 1;
	if(it->name != NULL)
	{
		free(it->name);
//		it->name = NULL;
	}
	it->name = (char*)malloc(length * sizeof(char));
	strcpy(it->name, name);

//	it->name = name;
	return it->name;
}

char* getName(struct Item_t* it)
{
	if(it == NULL)
	{
		return NULL;
	}
	return it->name;
}

int getWeight(struct Item_t* it)
{
	if(it == NULL)
	{
		return -1;
	}
	return it->weight;
}

int getCost(struct Item_t* it)
{
	if(it == NULL)
	{
		return -1;
	}
	return it->cost;
}

void outputItem(struct Item_t* it, FILE* fd)
{
	if(it == NULL)
	{
		return;
	}

	fprintf(fd, "%s: $%d, %d\n", it->name, it->cost, it->weight);
}
