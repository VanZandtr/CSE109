#include<stdio.h>
#include<stdlib.h>
#include"Item.h"

int main(int argc, char** argv)
{
//	struct Item_t* it = makeItem();
	struct Item_t* it;
	it = (struct Item_t*)malloc(1 * sizeof(struct Item_t));
	it = constructItem(it);

	//Java Equivalent
	//it.setWeight(10);
	setCost(it, 20);
	setWeight(it, 30);

	char word[10] = "bird";
//	int* x = (int*)(&word[0]);
//	x[0] = 0x64726962;
//	x[1] = 0; 
	setName(it, &word[0]);
	outputItem(it, stdout);

	word[0] = 'z';
	outputItem(it, stdout);

	setName(it, &word[0]);
	outputItem(it, stdout);

	it = freeItem(it);
	return 0;
}
