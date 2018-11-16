/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
Assigns words to finite buckets in
a bucket array while also
removeing a word if seen twice
Program #2
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

size_t removeDuplicate(char* line, size_t length, char* duplicate, size_t dupSize);


int main(int argc, char** argv)
{
	size_t sizeOfBucketList = 0;
	size_t sizeOfBuckets = 0;
	char** buckets = (char**) malloc(sizeOfBucketList* sizeof(char*));
	if(argc == 2)
	{
		if(atoi(argv[1]) >= 10 || atoi(argv[1]) <= 100000)
		{
			sizeOfBuckets = atoi(argv[1]);
		}
		else
		{
			fprintf(stderr,"Error, bad input.");
			return 1;
		}
	}
	else
	{
		sizeOfBuckets = 100;
	}

	size_t* bucketSize = (size_t*) malloc(sizeOfBucketList* sizeof(size_t));
	int spaceFound = 1;
	int wordRemoved;
	char* newWord = NULL;
	while(fscanf(stdin,"%ms", &newWord) == 1)
	{
		size_t sizeOfWord = strlen(newWord)+1;
		wordRemoved = 0;
	    if(sizeOfWord >sizeOfBuckets)
		{
			free(newWord);
 			newWord = NULL;
			continue;
		}
		for(size_t i = 0; i<sizeOfBucketList; i++)
		{
			size_t removedSize = removeDuplicate(buckets[i], bucketSize[i] , newWord, sizeOfWord);
			if(removedSize < bucketSize[i])
			{
				bucketSize[i] = removedSize;
 				wordRemoved = 1;
			}
		}
		if(wordRemoved == 0 && sizeOfBucketList > 0)
        {
            for(size_t i =0; i<sizeOfBucketList; i++)
            {
               	if((sizeOfBuckets - bucketSize[i])>= sizeOfWord && buckets[i] != NULL)// && noDuplicates == 0)// not null and can fit
               	{
                   	spaceFound = 1;
					for(size_t x = 0; x<sizeOfWord; x++)
					{
						buckets[i][x+bucketSize[i]] = newWord[x];
					}
                   	bucketSize[i] = bucketSize[i] + sizeOfWord;
					break;
               	}
				else if(sizeOfBucketList > i && buckets[i+1] == NULL && spaceFound == 0)// && noDuplicates == 0)// have enough buckets and need to intialize and put word into next created bucket
				{
					spaceFound = 1;
					buckets[i+1] = (char*)malloc(sizeOfBuckets * sizeof(char));
					strcpy(buckets[i+1], newWord);
					bucketSize[i+1] = bucketSize[i+1] + sizeOfWord;
					break;
				}
               	else
               	{
                   	spaceFound = 0;
                }
            }
	 	}
		if(spaceFound == 0 || sizeOfBucketList == 0)
		{
    	    size_t oldCapacity = sizeOfBucketList;
			sizeOfBucketList = (2 * sizeOfBucketList) +1;
			char** incBuckets = (char**)malloc(sizeOfBucketList * sizeof(char*));
			size_t* incBucketSize = (size_t*)malloc(sizeOfBucketList * sizeof(size_t));
			for(size_t j = 0; j <oldCapacity;j++)
			{
				incBuckets[j] = buckets[j];
				incBucketSize[j] = bucketSize[j];
			}
			free(buckets);
   			buckets = incBuckets;
   			incBuckets = NULL;

			free(bucketSize);
			bucketSize = incBucketSize;
			incBucketSize = NULL;

			buckets[oldCapacity] = (char*)malloc(sizeOfBuckets*sizeof(char));
			strcpy(buckets[oldCapacity], newWord);
			bucketSize[oldCapacity] = bucketSize[oldCapacity] + sizeOfWord;
		}
		free(newWord);
		newWord = NULL;
	}
	for(size_t i = 0; i<sizeOfBucketList; i++)
	{
		if(buckets[i] != NULL)
		{
			fprintf(stdout,"%s%ld: ", "    ",bucketSize[i]);
			for(size_t j = 0; j<bucketSize[i]; j++)
			{
				if(buckets[i][j] =='\0' && j == bucketSize[i]-1)
				{
					continue;
				}
				else if(buckets[i][j] == '\0')
				{
					fprintf(stdout," ");
					continue;
				}
				fprintf(stdout, "%c", buckets[i][j]);
			}
				fprintf(stdout,"\n");
		}
	}
 	for(size_t k = 0; k < sizeOfBucketList; k++)
    {
      	free(buckets[k]);
    }
	free(buckets);
	buckets = NULL;
	free(bucketSize);
	bucketSize = NULL;
	return 0;
}

size_t removeDuplicate(char* line, size_t length, char* duplicate, size_t dupSize)
{
	size_t k = 0;
	size_t counter = 0;
	int skipWordFlag = 0;
	int continueFlag = 0;
	if(length == 0)
	{
		continueFlag = 1;
	}
	if(continueFlag == 0)
	{
		for(size_t i = 0; i<length; i++)
		{
			if(line[i] != duplicate[k])
			{
				skipWordFlag = 1;
				k = 0;
				counter = 0;
				if(line[i] == '\0')
				{
					skipWordFlag = 0;
				}
			}
		 	else if(skipWordFlag == 0 )
			{
				while(line[i] == duplicate[k])
				{
					counter++;
					k++;
					i++;
					if(counter == dupSize)
					{
						for(size_t m = 0; m <dupSize; m++)
						{
                    		for(size_t j = i-counter; j < length; j++)
                    		{
                        		line[j] = line[j+1];
                    		}
						}
						length = length - dupSize;
						break;
                	}
				}
			}
		}
	}
	return length;
}
