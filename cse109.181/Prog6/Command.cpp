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
		char* commandptr = (char*)malloc((size + 1)*sizeof(char));
        ssize_t result = 0;
        result = read(fd, commandptr, size);
 		//fprintf(stderr,"size %d\n", size);
		 if(result != size)
        {
           	cerr << "Read of command failed (" << errno <<"):" << endl;
			close(fd);
            return;
        }
		commandptr[size] = '\0';

		//fprintf(stderr, "commandptr: %s\n", commandptr);

		//set args
		stringstream str(commandptr);
		string temp;
		while(str.good())
		{
			str >> temp;
			if(str.fail())//str.good()?
			{
				continue;
			}
			args.push_back(temp);
		}

		//set argv
		argv  =(char const**)malloc((args.size()+1) * sizeof(char const*));
		for(size_t i = 0; i<args.size(); i++)
		{
			argv[i] = args[i].c_str();
		}
		argv[args.size()] = NULL;

//		for(size_t i = 0; i< args.size(); i++)
//		{
//			fprintf(stderr, "Argv[i]:%s\n", argv[i]);
//		}

		//set variables
		this->cmd = commandptr;
		free(commandptr);//?
		return;
	}


    Command::~Command()
	{
		free(argv);
	}

    // Returns argv
    // The user is not expected to free this, you are.
    char const ** Command::getArgs()
	{
		return this->argv;
	}

