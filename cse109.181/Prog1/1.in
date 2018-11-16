#include<stdio.h>
#include<stdlib.h>
//#include"myowncode.h"

int main(int argc, char **argv)
{
	fprintf(stdout, "Hello World\n");
	printf("Hello World\n");
	fprintf(stderr, "Uncaught line\n");

	fprintf(stdout, "%s\n", argv[20]);

	for(int i=0; i<argc; i++)
	{
		fprintf(stdout, "Args %d: %s\n", i, argv[i]);
		fprintf(stdout, "Args %d: %s\n", i, *(argv + i));
	}

	int number = 5;
//	double dnumber = 10.3;
//	float fnumber = 4.5;
	char word[10];
	int other = 10;

	word[0] = 'b';
	word[1] = 'i';
	//word[2] = 'r';
	*(word + 2) = 'r';
	word[3] = 'd';
	word[4] = '\0';
	word[4] = (char)0;


	char *wordPtr, letter;
	//Type of wordPtr is (char *)
	//Type of letter is (char)
	letter = 't';
	wordPtr = &letter;

	fprintf(stderr, "word lives at location: '%p'\n", &word);
	fprintf(stderr, "Other lives at location: '%p'\n", &other);
	fprintf(stderr, "Number lives at location: '%p'\n", &number);
	fprintf(stderr, "word lives at location: '%p'\n", word);
	fprintf(stderr, "The word is '%s'\n", word);
/*	fprintf(stderr, "The word is '%c'\n", word);
	fprintf(stderr, "The word is '%c'\n", word[0]);
	fprintf(stderr, "The word is '%c'\n", word[1]);
	fprintf(stderr, "The word is '%c'\n", word[2]);
	fprintf(stderr, "The word(ptr) is '%c'\n", *(word + 0));
	fprintf(stderr, "The word(ptr) is '%c'\n", *(word + 1));
	fprintf(stderr, "The word(ptr) is '%c'\n", *(word + 2));
*/
	char temp = word[1];
	wordPtr = (char *)&word;
	temp = wordPtr[1];
	temp = *(wordPtr + 1);
	*(wordPtr + 1) = wordPtr[3];
	wordPtr[3] = temp;
/*
	fprintf(stderr, "The word is '%s'\n", word);

	fprintf(stdout, "Enter a number: ");
	fscanf(stdin, "%d", &number);
	fprintf(stdout, "The user inputted %d\n", number);
	fprintf(stdout, "Our values are %d %d\n", number, other);

	fprintf(stdout, "Enter a word: ");
	fscanf(stdin, "%9s", wordPtr);
	fprintf(stdout, "User entered: '%9s'\n", wordPtr);
	fprintf(stdout, "User entered: '%s'\n", wordPtr);
	fprintf(stderr, "The word is '%s'\n", wordPtr);
	fprintf(stdout, "Our values are %d %d\n", number, other);

*/
	//TYPE *storage = (TYPE *)malloc(DESIRED_SIZE * sizeof(TYPE));
	//char **sample = (char **)malloc(80 * sizeof(char *));
	int size = 80;
	char *buffer = (char *)malloc(size * sizeof(char));
	fprintf(stdout, "Input up to %d letters: ", size);

	for(int i=0; i<size; i++)
	{
		buffer[i] = 'q';
	}

	fscanf(stdin, "%79s", buffer);

	for(int i=0; i<size; i++)
	{
		fprintf(stdout, "%2d: %c (%d)\n", i, buffer[i], (int)buffer[i]);
	}

	//man getline
	//man getc/fgetc

	free(buffer);
	//char *buffer = NULL;
	buffer = NULL;
	fprintf(stdout, "Input something else, one word, no size limit: ");
	fscanf(stdin, "%m[^\n]s", &buffer);
	fprintf(stdout, "Entered string: '%s'\n", buffer);
	free(buffer);
	buffer = NULL;


/*
	fprintf(stderr, "Letter is '%c'\n", letter);
	fprintf(stderr, "Letter lives at location: '%p'\n", &letter);
	fprintf(stderr, "We think Letter lives at location: '%p'\n", wordPtr);

	*wordPtr = 'q';

    fprintf(stderr, "Letter is '%c'\n", letter);
    fprintf(stderr, "Letter lives at location: '%p'\n", &letter);
    fprintf(stderr, "We think Letter lives at location: '%p'\n", wordPtr);
*/

	return 0;
}








