/*
	CSE 109: Spring 2018
	Raymond Van Zandt
	rlv220
	Command's prototypes
	Program #6
*/
#ifndef COMMAND_H
#define COMMAND_H

#include<string>
#include<vector>
#include<sstream>

using namespace std;

class Command
{
public:

	// File constructor:
	// fd: open file descriptor (for reading) that points to a file containing our command.
	// size: The amount of data we need to read from the file.
	// cmd is initialized from the file contents.
	// args is the tokenized version of cmd.
	// argv is a dynamically allocated set of pointers to the contents of args, with a NULL (for execvp purposes)
	Command(int fd, unsigned int size);
	~Command();

	// Returns argv
	// The user is not expected to free this, you are.
	char const** getArgs();

private:
	// The complete command line
	string cmd;

	// Tokenized version of cmd
	vector<string> args;


	// Pointers to the const char* elements with args.
	char const** argv;
};


#endif
/*
	CSE 109: Spring 2018
	Raymond Van Zandt
	rlv220
	Command's C++ file
	Program #6
*/
#include"Command.h"
#include<string>
#include<cstring>
#include<vector>
#include<sstream>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<iterator>
#include<algorithm>
#include<iostream>
#include<bits/stdc++.h>
#include<unistd.h>
#include<stdio.h>
using namespace std;

    Command::Command(int fd, unsigned int size)
	{
		//set string cmd
		char* commandptr = (char*)malloc(size*sizeof(char));
        ssize_t result = 0;
        result = read(fd, commandptr, size);
        if(result != sizeof(unsigned int))
        {
           	cerr << "Read of command failed (" << errno <<"):" << endl;
			close(fd);
            return;//correct? - return 2?
        }
		commandptr[size] = '\0';

		//set args
		vector<string> tokens;
		stringstream str(commandptr);
		string temp;

		while(getline(str, temp, ' '))
		{
			tokens.push_back(temp);
		}

		//set argv
		char** temp2 =(char**)malloc(tokens.size()+1 * sizeof(char*));
		for(size_t i = 0; i<tokens.size(); i++)
		{
			temp2[i] =(char*)malloc(tokens[i].size()*sizeof(char));
			strcpy(temp2[i],tokens[i].c_str());
		}
		temp2[tokens.size()] = NULL;
		char const** temp3 = const_cast<char const**>(temp2);

		//set variables
		this->cmd = commandptr;
		this->args = tokens;
		this->argv = temp3;

		return;
	}


    Command::~Command()
	{
	}

    // Returns argv
    // The user is not expected to free this, you are.
    char const** Command::getArgs()
	{
		return this->argv;
	}

