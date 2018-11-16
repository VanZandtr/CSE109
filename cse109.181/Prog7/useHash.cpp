/*
CSE 109: Spring 2018
Raymond Van Zandt
rlv220
test program for the hash
Program #7
*/

#include<stdio.h>
#include"Hash.h"
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

int main(int argc, char** argv)
{

	//unsigned int tests
	Hash_t hash(1001);
	cout << "Hash: " << endl;
	cout << hash;
	//srand(2);

    //for(int i=0; i<20; i++)
    //{
      //  unsigned int val = rand() % 10000;
        //hash.insert(val);
    //}
	hash.insert('a');
	hash.insert('b');
	hash.insert('y');
	hash.insert('z');
	cout << "Hash(" << hash.size() << "):" << endl;
	cout << hash.toString('a') << endl;

	hash.remove('b');
	hash.remove('y');
	cout << "Hash(" << hash.size() << "):" << endl;
	cout << hash.toString('a') << endl;

	if(hash.find('z') == true)
	{
		fprintf(stderr, "YAY\n");
	}

	unsigned int dupInsert = 5290;
	hash.insert(dupInsert);
	cout << "Hash (check dup insert of 5290: "<< hash.size() << endl;
	cout << hash << endl;

	unsigned int finder = 5290;
	if(hash.find(finder) == true)
	{
		cout << "FOUND 5290!"<< endl;
	}
	else
	{
		cout << "False: You should have found 5290!"<< endl;
	}
	cout << hash << endl;

	unsigned int toRemove = 5290;
	hash.remove(toRemove);
	cout << "Hash removed 5290: " << hash.size() << endl;
	cout << hash << endl;

	if(hash.find(finder) == true)
	{
		cout << "FOUND 5290???????"<< endl;
	}
	else
	{
		cout << "False. YAY! 5290 is gone!"<< endl;
	}
	cout << hash << endl;

	hash += (unsigned int) 1000;
	cout << "Hash += 1000: " << hash.size() << endl;
	cout << hash << endl;

	hash -= (unsigned int) 1000;
	cout << "Hash -= 1000: " << hash.size() << endl;
	cout << hash << endl;

//testing = operator
	Hash_t equalHash = hash;
	cout << "equalHash: " << equalHash.size() << endl;
	cout << equalHash << endl;

//testing if insert into hash inserts into equalHash
	unsigned int temp = (unsigned int)3333;
	hash.insert(temp);
	cout << "hash inserted 3333: " << hash.size() << endl;
	cout << hash << endl;
	cout << "Does equalHash have 3333 ?: " << equalHash.size() << endl;
	cout << equalHash << endl;

	unsigned int toInsert2 = (unsigned int)5290;
	equalHash.insert(toInsert2);
	cout << "equalHash inserted 5290: " << equalHash.size() << endl;
	cout << equalHash << endl;

	unsigned int toRemove2 = (unsigned int)5290;
	equalHash.remove(toRemove2);
	cout << "equalHash removed 5290: " << equalHash.size() << endl;
	cout << equalHash << endl;

	equalHash += (unsigned int) 1000;
	cout << "equalHash += 1000: " << equalHash.size() << endl;
	cout << equalHash << endl;

	equalHash -= (unsigned int) 1000;
	cout << "equalHash -= 1000: " << equalHash.size() << endl;
	cout << equalHash << endl;

// testing other constructors
	size_t someBuckets = 5;
	Hash_t hashWithBuckets(someBuckets);
    for(int i=0; i<20; i++)
    {
        unsigned int val = rand() % 10000;
        hashWithBuckets.insert(val);
    }
	cout << "Hash with 5 buckets (" << hashWithBuckets.size() << "):" << endl;
	cout << hashWithBuckets << endl;

	Hash_t hashWithFunction(someBuckets, basic_hash); 
    for(int i=0; i<20; i++)
    {
        unsigned int val = rand() % 10000;
        hashWithFunction.insert(val);
    }
	cout << "Hash with basic hash(" << hashWithFunction.size() << "):" << endl;
	cout << hashWithFunction << endl;




//Now the char stuff
	Hash_t charHash;
	cout << "Hash: " << endl;
	cout << charHash << endl;
	char letter = 'a';
	while (letter >= 'a' && letter <= 'z')
	{
        charHash.insert(letter);
		letter++;
    }
	cout << "charHash(" << charHash.size() << "):" << endl;
	cout << charHash.toString(letter) << endl;

	char charDupInsert = 'a';
	charHash.insert(charDupInsert);
	cout << "charHash(" << charHash.size() << "):" << endl;
	cout << charHash.toString(letter) << endl;

	char charfinder = 'a';
	if(charHash.find(charfinder) == true)
	{
		cout << "FOUND a!"<< endl;
	}
	else
	{
		cout << "False: You should have found a!"<< endl;
	}
	cout << "Hash(" << charHash.size() << "):" << endl;
	cout << charHash.toString(letter) << endl;

	char chartoRemove = 'a';
	while (chartoRemove >= 'a' && chartoRemove <= 'y')
	{
        charHash.remove(chartoRemove);
		chartoRemove++;
    }
	cout << "charHash (" << charHash.size() << "): (removed all but z)" << endl;
	cout << charHash.toString(letter) << endl;

	if(charHash.find(charfinder) == true)
	{
		cout << "FOUND a? Wrong!"<< endl;
	}
	else
	{
		cout << "YAY! You did not find a!"<< endl;
	}
	cout << "Hash(" << charHash.size() << "):" << endl;
	cout << charHash.toString(letter) << endl;


//testing = operator
	Hash_t equalCharHash = charHash;
	cout << "equalCharHash: " << equalCharHash.size() << endl;
	cout << equalCharHash.toString(letter) << endl;

//testing if insert into hash inserts into equalCharHash
	char chartemp = 'e';
	charHash.insert(chartemp);
	cout << "charHash inserted e: " << charHash.size() << endl;
	cout << charHash.toString(letter) << endl;
	cout << "Does equalCharHash have e?: " << equalCharHash.size() << endl;
	cout << equalCharHash.toString(letter) << endl;

	char chartoInsert2 = 'r';
	equalCharHash.insert(chartoInsert2);
	cout << "equalCharHash inserted r: " << equalCharHash.size() << endl;
	cout << equalCharHash.toString(letter) << endl;

	char chartoRemove2 = 'r';
	equalCharHash.remove(chartoRemove2);
	cout << "equalCharHash removed r: " << equalCharHash.size() << endl;
	cout << equalCharHash.toString(letter) << endl;

	equalCharHash += 'a';
	cout << "equalCharHash += a: " << equalCharHash.size() << endl;
	cout << equalCharHash.toString(letter) << endl;

	equalCharHash -= 'a';
	cout << "equalCharHash -= a: " << equalCharHash.size() << endl;
	cout << equalCharHash.toString(letter) << endl;


// testing other constructors
	size_t somecharBuckets = 15;
	Hash_t charhashWithBuckets(somecharBuckets);
	char letter2 = 'a';
	while (letter2 >= 'a' && letter2 <= 'z')
	{
        charhashWithBuckets.insert(letter2);
		letter2++;
    }
	cout << "Char Hash with 15 buckets (" << charhashWithBuckets.size() << "):" << endl;
	cout << charhashWithBuckets.toString(letter) << endl;


	Hash_t charHashWithFunction(somecharBuckets, basic_hash); 
	letter2 = 'a';
	while (letter2 >= 'a' && letter2 <= 'z')
	{
        charHashWithFunction.insert(letter2);
		letter2++;
    }
	cout << "Char Hash with basic hash(" << charHashWithFunction.size() << "):" << endl;
	cout << charHashWithFunction.toString(letter2) << endl;

	return 0;
}
