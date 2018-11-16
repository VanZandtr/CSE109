/*
	CSE 109: Spring 2018
	Raymond Van Zandt
	rlv220
	ExecutionPair's C++ file
	Program #6
*/
#include"ExecutionPair.h"
#include<memory>
#include<string>
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
#include<iostream>
using namespace std;

ExecutionPair::ExecutionPair(int fd)
{

	//read in bits
	int communicationModule = 0;
	ssize_t result = 0;
	result = read(fd, &communicationModule, 1);
	if(result != 1)
    {
		//fprintf(stderr,"%d\n", errno);
        //fprintf(stderr,"%ld\n", result);
		cerr << "Read of communication Module failed (" << errno <<"):" << endl;
        close(fd);
        return;//correct? - return 2?
	}
	int inPipe1 = (communicationModule) & 0x3;
	int outPipe1 = (communicationModule >> 2) & 0x3;
	int inPipe2 = (communicationModule >> 4) & 0x3;
	int outPipe2 = (communicationModule >> 6) & 0x3;
	//fprintf(stderr,"1: %d\n", inPipe1);
  	//fprintf(stderr,"2: %d\n", outPipe1);
    //fprintf(stderr,"3: %d\n", inPipe2);
    //fprintf(stderr,"4: %d\n", outPipe2);

	//read cmd1's size
	int cmd1Size = 0;
    result = read(fd, &cmd1Size, 4);
    if(result != 4)
    {
		cerr<< "Read of Command 1's size failed (" << errno <<"):" << endl;
        close(fd);
        return;//correct? - return 2?
	}

	//read cmd2's size
	int cmd2Size = 0;
	result = read(fd, &cmd2Size, 4);
    if(result != 4)
    {
    	cerr << "Read of Command 2's size failed (" << errno <<"):" << endl;
        close(fd);
        return;//correct?
    }

	//pass fd to Command.cpp
	this->cmd1 =  new Command(fd, cmd1Size);//correct?
	this->cmd2 =  new Command(fd, cmd2Size);

	//set variables
	this->in1 = inPipe1;
	this->out1 = outPipe1;
	this->in2 = inPipe2;
	this->out2 = outPipe2;
	//this->cmd1 = command1;
	//this->cmd2 = command2;

	//returns newPair back to piper to be executed
	return;
	}

ExecutionPair::~ExecutionPair()
{
	delete cmd1;
	delete cmd2;
}


// Executes cmd1 and cmd2, setting up communication as specified
void ExecutionPair::execute()
{
	//1.) create pipes if communication...??
	int pipe1[2];
    if(pipe(pipe1) == -1)
   	{
       	perror("Pipe creation failed");
       	return;
   	}

    int pipe2[2];
    if(pipe(pipe2) == -1)
   	{
       	perror("Pipe creation failed");
       	return;
   	}

	if(in1 == 0 && out1 == 1)// don't need pipes
	{
		close(pipe1[0]);
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
	}

	//2.) fork here 
	pid_t pid1 = fork();

	//child 1
    if(pid1 == 0)
    {
		if(in1 == 3 && out2 == 0) //Option 2
		{
			//close pipes
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe1[1]);
			//write2 = pipe1's in
			dup2(pipe1[0], STDIN_FILENO);
			close(pipe1[0]);
		}
		if(out1 == 2)//Option 1
		{
			//close
			close(pipe2[0]);
            close(pipe1[1]);
			close(pipe1[0]);

       	    //write1 = pipe2's in
	        dup2(pipe2[1], STDOUT_FILENO);
			close(pipe2[1]);
		}
    	if(execvp((*cmd1).getArgs()[0], (char* const*)(*cmd1).getArgs())== -1)
		{
	    	perror("Exec response");
	    	cerr <<  "Child 1 failed to execute\n" << endl;
			exit(3);
		}
        //Exit here to avoid letting the child grow up
	    exit(0);
	}
	else
	{
		pid_t pid2 = fork();

		//child 2
		if(pid2 == 0)
		{
		if(in1 == 3 && out2 == 0) //Option 2
		{
			//close pipes
			close(pipe2[0]);
			close(pipe2[1]);
			close(pipe1[0]);

			//write2 = pipe1's in
			dup2(pipe1[1], STDOUT_FILENO);
			close(pipe1[1]);
		}
		if(out1 == 2)//Option 1
		{
			//close
			close(pipe1[1]);
            close(pipe2[1]);
			close(pipe1[0]);

       	    //write1 = pipe2's in
	        dup2(pipe2[0], STDIN_FILENO);
			close(pipe2[0]);
		}
			//similar to 1
    		if(execvp((*cmd2).getArgs()[0], (char* const*)(*cmd2).getArgs()) == -1)//how to use
	    	{
				perror("Exec response");
				cerr << "Child 2 failed to execute" << endl;
				exit(3);
			}
    		//Exit here to avoid letting the child grow up
			exit(0);
		}
	}
	//4.)Close all pipes?
    close(pipe1[0]);
	close(pipe1[1]);
	close(pipe2[0]);
	close(pipe2[1]);
	return;
}







