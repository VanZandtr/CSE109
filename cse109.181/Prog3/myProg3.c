#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"List.h"

int main(int argc, char **argv)
{
    struct List_t *myList = (struct List_t*)malloc(1 * sizeof(struct List_t));
    myList = makeList(myList);

    struct Node_t* myNode = NULL;
	myNode = insert(myList, 0);
	myNode = insert(myList, 0);
    myNode = insert(myList, 0);
	myNode = insert(myList, 0);
	fprintf(stderr,"List Size: %ld\n", size(myList));
	fprintf(stderr,"Removed: %ld\n", removeItem(myList, 0));
    fprintf(stderr,"List Size: %ld\n", size(myList));
    myNode = insert(myList, 44);


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


	if(myNode == NULL)
    {
       fprintf(stderr, "Insert failed\n");
       return -1;
    }
	fprintf(stderr,"Found: %ld\n", find(myList, 10));
	myList = freeList(myList);
	fprintf(stderr,"List Size: %ld\n", size(myList));
	if(myList == NULL)
	{
		fprintf(stderr,"List Size: NULL\n");
	}

return 0;
}
