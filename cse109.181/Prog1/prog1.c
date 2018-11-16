/*CSE 109: Spring 2018
Raymond Van Zandt
rlv220
Main: Program takes reads in lines via file(until end) or command line(until ctrl$
reverseLine: reverses an entire line.
reverseWord: reverses each individual word in a line.
toggle: changes uppercase to lowercasee and vice versa.
removeDigits: removes digits from a line.
Program #1
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
void reverseLine(char* line, size_t);
void reverseWord(char* line, size_t);
void toggle(char* line, size_t);
size_t removeDigits(char* line, size_t);

int main(int argc, char** argv)
{
 	int  reverseWordFlag  = 0;
    int  reverseLineFlag = 0;
    int  toggleFlag = 0;
    int  deleteDigitsFlag = 0;
    int i;
    for( i = 1; i<argc; i++)
    {
        if(strcmp(argv[i], "-r") == 0)
        {
            reverseWordFlag  = 1;
        }
        else if(strcmp(argv[i], "-e") == 0)
        {
            reverseLineFlag  = 1;
        }
        else if(strcmp(argv[i], "-t") == 0 )
        {
            toggleFlag = 1;
  		}
        else if(strcmp(argv[i], "-n") == 0)
        {
            deleteDigitsFlag = 1;
        }
        else
        {
            fprintf(stdout,"Invalid command line option.\n");
            return 1;
        }
    }
    char* newLine = NULL;
   	size_t result;
    size_t ignore = 0;
    int go = 1;
    while(go)
    {
    	result = getline(&newLine,&ignore,stdin);
        if(result == -1)
        {
        	go = 0;
            return 1;
        }
        if(reverseWordFlag == 1)
        {
            reverseWord(newLine, result);
        }
        if(reverseLineFlag == 1)
        {
            newLine[result-1] = '\0';
            result--;
            reverseLine(newLine, result);
            newLine[result] = '\n';
        }
        if(toggleFlag == 1)
        {
            toggle(newLine, result);
        }
        if(deleteDigitsFlag == 1)
        {
            removeDigits(newLine, result);
        }
        fprintf(stdout,"%s",newLine);
 	}
    return 0;
}

void reverseLine(char* line, size_t length)
{
    size_t i;
    char temp;
    size_t left;
    size_t right;
    left = 0;
    right = length-1;
    for(i = 0; i<(length)/2; i++)
    {
        temp = line[left];
        line[left] = line[right];
        line[right] = temp;
        right--;
        left++;
    }
}

void reverseWord(char* line,size_t length)
{
    char temp;
    size_t i = 0;
    size_t j;
    size_t  left;
    size_t  right;
    size_t  counter = 0;
    int nospaceFlag = 0;
    for(i = 0; i<length; i++)
    {
        if(isspace(line[i]))
        {
            nospaceFlag = 0;
        }
        else
        {
            nospaceFlag = 1;
        }
        if(nospaceFlag == 1)
        {

			for(j = i; !isspace(line[j]) && j<length; j++)
            {
                i++;
                counter++;
            }
            left = i - counter;
            right = i-1;
            for(j = 0; j<(counter+1)/2; j++)
            {
                temp = line[left];
                line[left] = line[right];
                line[right] = temp;
                right--;
                left++;
            }
        counter = 0;
        nospaceFlag = 0;
        }
    }
}

void toggle(char* line, size_t length)
{
    size_t i;
    for(i=0; i<length; i++)
    {
        if('a'<=line[i] && line[i]<= 'z')
        {
            char toggle1 = (((int)line[i])-32);
            line[i] = toggle1;
        }
        else if('A'<=line[i] && line[i]<= 'Z')
        {
            char toggle2 = (((int)line[i])+32);
            line[i] = toggle2;
        }
    }
}

size_t removeDigits(char* line, size_t length)
{
    size_t i;
    size_t j;
 	for(i = 0; i<length; i++)
    {
        if(isdigit(line[i]))
        {
            for(j = i;j<length; j++)
            {
                    line[j] = line[j+1];
            }
            i--;
            length--;
        }
    }
    return length;
}
