/*
    CSE 109: Spring 2018
    Raymond Van Zandt
    rlv220
    Hash's prototypes and variables
    Program #7
*/
#ifndef HASH_H
#define HASH_H

#include<memory>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<stdbool.h>
#include<sys/types.h>
#include<openssl/sha.h>

using namespace std;
int defaultHash(void *data, size_t size);
int basic_hash(void* data, size_t size);
class Hash_t
{

public:
    Hash_t();
    Hash_t(size_t buckets);
    Hash_t(size_t buckets, int(*hashfunc)(void*, size_t));
    Hash_t(Hash_t& src);
    ~Hash_t();

	Hash_t& operator=(const Hash_t& src);
	Hash_t& operator+=(unsigned int data);
	Hash_t& operator+=(char data);
	Hash_t& operator-=(unsigned int data);
	Hash_t& operator-=(char data);

	friend ostream& operator<<(ostream& out, const Hash_t& rhs);

    bool remove(unsigned int data);
    bool remove(char data);
    bool insert(unsigned int data);
    bool insert(char data);
	bool find(unsigned int data);
	bool find(char data);

	string toString() const;
	string toString(unsigned int data) const;
	string toString(char data) const;

	size_t size() const;


private:
	size_t numBuckets;
    vector<vector<unsigned int>> buckets;
	int(*hashfunc)(void*, size_t);
	size_t _size;

	size_t getIndex(char data) const;
	size_t getIndex(unsigned int data) const;

	unsigned int pack(unsigned int packet, char toPack);
	int findFreeSpace(int index);
	void unpack(unsigned int packet, char* retval) const;
};


#endif
