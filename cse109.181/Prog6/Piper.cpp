/*
    CSE 109: Spring 2018
    Raymond Van Zandt
    rlv220
    Piper's C++ file
    Program #6
*/
#include<memory>
#include<string>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<signal.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"ExecutionPair.h"
using namespace std;

    main(int argc, char** argv)
    {
        //check arg for filename
		if(argc != 2)
		{
			//errno??
			cerr << stderr << "No Command Line (" << errno <<"):" << strerror(errno) << endl;
			return 1;
		}

 		int fd = open(argv[1], O_RDONLY);// I think this is correct
    	if(fd == -1)
    	{
			cerr << "Open file failed (" << errno <<"):" << strerror(errno) << endl;
        	return 2;
    	}

		//cases
  		short cases = 0;
        ssize_t result = 0;
    	result = read(fd, &cases, 2);
    	if(result != sizeof(short))
    	{
            cerr << "Read of number of cases failed (" << errno <<"):" << strerror(errno) << endl;
        	close(fd);
        	return 2;
    	}
		cases /= 2;

		//create/execute pairs
		ExecutionPair** pairArray = (ExecutionPair**)malloc(cases*sizeof(ExecutionPair*));
		for(size_t i = 0; i < cases; i++)
		{
			//pass fd to  execution pair cpp
			pairArray[i]= new ExecutionPair(fd);
		}
		close(fd);
		for(size_t i = 0; i< cases; i++)
		{
			pairArray[i]->execute();
        }

		//wait for children
		pid_t whichChild = 0;
		int status = 0;
		while((whichChild = waitpid(-1,&status,0)) != -1)
    	{
 			//A child has changed state. Let's see what happened:
        	if(WIFEXITED(status))
        	{

            	cerr << "Child " << whichChild <<" terminated with value: " <<  WEXITSTATUS(status) << endl;
				//fprintf(stdout, "Child %d terminated with value %d\n", whichChild, WEXITSTATUS(status));
        	}
        	else if(WIFSIGNALED(status))
        	{
            	cerr << "Child " << whichChild <<" terminated abnormally with signal: " <<  WTERMSIG(status) << endl;
            	//fprintf(stdout, "Child %d terminated by signal %d\n", whichChild, WTERMSIG(status));
        	}
    	}

		//whichChild returned -1 here, therefore we had an error.
    	if(errno != ECHILD)
    	{
     		perror("Wait errored but did not return ECHILD:");
        	exit(5);
    	}
		//clean up
		//delete pair Array?
		for(size_t i = 0; i<cases; i++)
		{
			delete pairArray[i];
		}
		free(pairArray);
		return 1;
    }


