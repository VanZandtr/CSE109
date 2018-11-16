all: hash

hash: useHash.o Hash.o
	g++ -g -Wall -Werror -lssl -lcrypto -o hash useHash.o Hash.o

useHash.o: useHash.cpp
	g++ -g -Wall -Werror -c useHash.cpp

Hash.o:Hash.cpp Hash.h
	g++ -g -Wall -Werror -c Hash.cpp



