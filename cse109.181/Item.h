#ifndef ITEM_H
#define ITEM_H

#include<stdio.h>

struct Item_t
{
	char* name;
	int weight;
	int cost;
};


struct Item_t* makeItem();
//Can't call it makeItem, no overloading supported
struct Item_t* constructItem(struct Item_t* it);

struct Item_t* freeItem(struct Item_t* it);

char* setName(struct Item_t* it, char* name);
int setWeight(struct Item_t* it, int weight);
int setCost(struct Item_t* it, int cost);

char* getName(struct Item_t* it);
int getWeight(struct Item_t* it);
int getCost(struct Item_t* it);

void outputItem(struct Item_t* it, FILE* fd);


#endif
