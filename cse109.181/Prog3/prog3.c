#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"List.h"

int main(int argc, char **argv)
{
	struct List_t *myList = (struct List_t*)malloc(1 * sizeof(struct List_t));
	myList = makeList(myList);

	if(argc != 3)
	{
		fprintf(stderr, "Not enough arguments: %s <count> <seed>\n", argv[0]);
		return 1;
	}
	int count = atoi(argv[1]);
	int seed = atoi(argv[2]);

	srand(seed);

	char commands[8] = "csifr";
	for(int i=0; i<count; i++)
	{
		char rCommand = commands[rand() % 5];
		int rOption = rand() % 64;
		struct Node_t* myNode = NULL;
		//size_t howMany = 0;

		char command = ' ';
		char rBuffer[100];
		sprintf(rBuffer, "-%c:%d", rCommand, rOption);
		int option = 0;
		fprintf(stderr, "Processing command '%s'.\n", rBuffer);
		sscanf(rBuffer, "-%c:%d", &command, &option);
		switch(command)
		{
		case 'c':
			myList = freeList(myList);
			myList = (struct List_t*)malloc(1 * sizeof(struct List_t));
			myList = makeList(myList);
			break;
		case 's':
			//howMany = size(myList);
			size(myList);
			break;
		case 'i':
			myNode = insert(myList, option);
			if(myNode == NULL)
			{
				fprintf(stderr, "Insert failed\n");
				return 3;
			}
			break;
		case 'f':
			//howMany = find(myList, option);
			find(myList, option);
			break;
		case 'r':
			//howMany = removeItem(myList, option);
			removeItem(myList, option);
			break;
		}



		//Dangerous estimate
		char *buffer = (char *)calloc(1, 250000 * sizeof(char));
		if(traverse(myList, buffer) == 0)
		{
			fprintf(stdout, "List is empty.\n");
		}
		else
		{
			fprintf(stdout, "List: %s.\n", buffer);
		}
		free(buffer);

		char *printable = traverse2(myList);
		fprintf(stdout, "List: %s.\n", printable);
		free(printable);
	}

	//Dangerous estimate but we don't want to answer a part of the assignment.
	char *buffer = (char *)calloc(1, 250000 * sizeof(char));
	traverse(myList, buffer);
	fprintf(stdout, "%s\n", buffer);
	free(buffer);

	char *printable = traverse2(myList);
	fprintf(stdout, "%s\n", printable);
	free(printable);

	myList = freeList(myList);
	//valgrind should report no memory leaks at this point

	return 0;
}
