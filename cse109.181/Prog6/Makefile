all: piper

piper: Piper.o Command.o ExecutionPair.o
	g++ -g -Wall -Werror -o piper Piper.o Command.o ExecutionPair.o

piper.o: Command.h ExecutionPair.h

Command.o: Command.h Command.cpp
	g++ -g -Wall -Werror -c Command.cpp

ExecutionPair.o: ExecutionPair.h ExecutionPair.cpp Command.h
	g++ -g -Wall -Werror -c ExecutionPair.cpp

clean:
	rm -rf Command.o ExecutionPair.o Piper.o piper

