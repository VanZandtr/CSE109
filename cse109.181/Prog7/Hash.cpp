/*
    CSE 109: Spring 2018
    Raymond Van Zandt
    rlv220
    Hash's methods and functionality
    Program #7
*/
#include"Hash.h"
#include<memory>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<stdbool.h>
#include<openssl/evp.h>
#include<sys/types.h>
#include<tgmath.h>
#include<cmath>
using namespace std;

Hash_t::Hash_t()
: numBuckets(10), buckets(10), _size(0)
{
	this->hashfunc = *defaultHash;
}

Hash_t::Hash_t(size_t numBuckets)
: numBuckets(numBuckets), buckets(numBuckets), _size(0)
{
	this->hashfunc = *defaultHash;
}

Hash_t::Hash_t(size_t numBuckets, int(*hashfunc)(void* ptr, size_t size))
: numBuckets(numBuckets), buckets(numBuckets), _size(0)
{
	this->hashfunc = *hashfunc;
}

Hash_t::Hash_t(Hash_t& src)
:numBuckets(src.numBuckets), buckets(src.buckets), hashfunc(src.hashfunc),_size(src._size)
{
}

Hash_t::~Hash_t()
{
}

Hash_t& Hash_t::operator=(const Hash_t& src)
{

	if(this == &src)
    {
        return *this;
    }


 	for(size_t i = 0; i < numBuckets; i++)// delete what's in buckets
    {
        buckets.erase(buckets.begin() + i);
    }

	numBuckets = src.numBuckets;
	_size = src._size;
	hashfunc = src.hashfunc;

	for(size_t i = 0; i < src.numBuckets; i++)
	{
		buckets[i] = src.buckets[i];
	}

	return *this;

}

Hash_t& Hash_t::operator+=(unsigned int data)
{
	insert(data);
	return *this;
}

Hash_t& Hash_t::operator+=(char data)
{
	insert(data);
	return *this;
}

Hash_t& Hash_t::operator-=(char data)
{
	remove(data);
	return *this;
}

Hash_t& Hash_t::operator-=(unsigned int data)
{
	remove(data);
	return *this;
}

ostream& operator<<(ostream& out, const Hash_t& rhs)
{
	out << rhs.toString() << endl;
	return out;
}

bool Hash_t::remove(unsigned int data)
{
	int index = getIndex(data);
	if(find(data))
	{
		for(size_t i = 0; i< buckets[index].size(); i++)
		{
			if(data == buckets[index][i])
			{
				buckets[index].erase(buckets[index].begin() + i);
				_size--;
				return true;
			}
		}
	}
	return false;
}

bool Hash_t::remove(char data)
{
	int index = getIndex(data);
	char* array = new char[8];
	if(find(data))
	{
		for(size_t i = 0; i< buckets[index].size(); i++)
		{
			for(size_t j = 4; j < 8; j++)
			{
				unpack(buckets[index][i], array);
				if(array[j] == data)
				{
					int index2 = j - 4;
					unsigned int temp = (buckets[index][i]);

					if(index2 == 0)
					{
						temp = (temp & 0xFFFFF80F);
						temp = (temp & 0xFFFFFFFE);
						buckets[index][i] = temp;
					}
					else if(index2 == 1)
					{
						temp = (temp & 0xFFFC07FF);
						temp = (temp & 0xFFFFFFFD);
						buckets[index][i] = temp;
					}
					else if(index2 == 2)
					{
						temp = (temp & 0xFE03FFFF);
						temp = (temp & 0xFFFFFFFB);
						buckets[index][i] = temp;
					}
					else if(index2 == 3)
					{
						temp = (temp & 0x1FFFFFF);
						temp = (temp & 0xFFFFFFF7);
						buckets[index][i] = temp;
					}
					_size--;
					delete array;
					return true;
				}
			}
		}
	}
	delete array;
	return false;
}

bool Hash_t::insert(unsigned int data)
{
	int index = getIndex(data);
	if(!find(data))
	{
		buckets[index].push_back(data);
		_size++;
		return true;
	}
	return false;
}

bool Hash_t::insert(char data)
{
	int index = getIndex(data);
	if(!find(data))
	{
		int freeValue = findFreeSpace(index);
		if(freeValue != -1)
		{
			buckets[index][freeValue] = pack(buckets[index][freeValue], data);
			_size++;
			return true;
		}
		else
		{
			buckets[index].push_back(0);
			buckets[index][buckets[index].size()-1] = pack(buckets[index][buckets[index].size()-1], data);
			_size++;
			return true;
		}
	}
	return false;
}

bool Hash_t::find(unsigned int data)
{
	size_t index = getIndex(data);
	for(size_t i = 0; i< buckets[index].size(); i++)
	{
		if(data == buckets[index][i])
		{
			return true;
		}
	}
	return false;
}

bool Hash_t::find(char data)
{
	size_t index = getIndex(data);
	char* array = new char[8];
	for(size_t i = 0; i< buckets[index].size(); i++)
	{
		unpack(buckets[index][i], array);
		for(size_t j = 4; j<8; j++)
		{
			if(array[j] == data)
			{
				free(array);
				return true;
			}
		}
	}
	delete array;
	return false;
}

string Hash_t::toString() const
{
	string retval;
	int space = log10(numBuckets) + 1;
	char* formatString = (char*)malloc(space*sizeof(char));
	for(size_t i = 0; i<buckets.size(); i++)
	{
		sprintf(formatString,"%*lu", space, i);
		string str(formatString);
		retval += str + ": ";
		if(buckets[i].empty())
		{
			retval+= "(Empty)";
			retval+= '\n';
		}
		else
		{
			//cerr << "I'm in generic toString" << endl;
			for(size_t j = 0; j<buckets[i].size(); j++)
			{
				retval+= to_string(buckets[i][j]);
				if(j == buckets[i].size() - 1)
				{
					break;
				}
				retval+= " ";
			}
			retval+= '\n';
		}
	}
	free(formatString);
	return retval;
}

string Hash_t::toString(unsigned int data) const
{
	//same as toString()
	string retval;
	int space = log10(numBuckets) + 1;
	char* formatString = (char*)malloc(space*sizeof(char));
	for(size_t i = 0; i<buckets.size(); i++)
	{
		sprintf(formatString,"%*lu", space, i);
		string str(formatString);
		retval += str + ": ";
		if(buckets[i].empty())
		{
			retval+= "(Empty)\n";
			retval+= '\n';
		}
		else
		{
				//cerr << "I'm in int toString" << endl;
			for(size_t j = 0; j<buckets[i].size(); j++)
			{
				retval+= to_string(buckets[i][j]);
				if(j == buckets[i].size() - 1)
				{
					break;
				}
				retval+= " ";
			}
			retval+= '\n';
		}
	}
	free(formatString);
	return retval;
}

string Hash_t::toString(char data) const
{
 //unpack the int packet
 //retval += return string
	string retval;
	int space = log10(numBuckets) + 1;
	char* formatString = (char*)malloc(space*sizeof(char));
	for(size_t i = 0; i<buckets.size(); i++)
	{
		sprintf(formatString,"%*lu", space, i);
		string str(formatString);
		retval += str + ": ";
		if(buckets[i].empty())
		{
			retval+= "(Empty)";
			retval+= "\n";
		}
		else
		{
			unsigned int temp;
			char* array = new char[8];
			for(size_t j = 0; j<buckets[i].size(); j++)
			{
				temp = buckets[i][j];
				unpack(temp, array);

				if(array[0] == 0 && array[1] == 0 && array[2] == 0 && array[3] == 0)
				{
					retval+= "(Empty)";
					continue;
				}
				for(size_t i = 4; i < 8; i++)
				{
					if(array[i - 4] != 0)
					{
						//cerr << i << endl;
						//cerr << array[i] << endl;
						retval+= (char)array[i];
						if(i == 7)
						{
							break;
						}
						retval+= " ";
					}
				}
			}
			delete array;
			retval+= "\n";
		}
	}
	free(formatString);
	return retval;
}

size_t Hash_t::size() const
{
	return this->_size;
}

size_t Hash_t::getIndex(char data) const
{
	return this->hashfunc(&data, sizeof(char)) % numBuckets;
}

size_t Hash_t::getIndex(unsigned int data) const
{
	return this->hashfunc(&data, sizeof(unsigned int)) % numBuckets;
}

int defaultHash(void *data, size_t size)
{
	int bytes = 0;
	for(size_t i = 0; i < size; i++)
	{
		bytes += *(((char*)data) + i);
	}
	return bytes;
}

int basic_hash(void* data, size_t size)
{
	EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    OpenSSL_add_all_digests();

    md = EVP_get_digestbyname("sha1");

    if(!md)
	{
        printf("Unknown message digest %s\n", "sha1");
        exit(1);
    }

    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data, size);
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_destroy(mdctx);

	int retval = 0;
    for(size_t i = 0; i < md_len; i+=4)
	{
		retval = retval^*((int*)md_value + i/4);
    }
	return retval;
}

void Hash_t::unpack(unsigned int packet, char* retval) const
{
	int status1 = packet & 0x1;
	int status2 = packet & 0x2;
	int status3 = packet & 0x4;
	int status4 = packet & 0x8;
	char char1, char2, char3, char4;
	if(status1 != 0)
	{
		retval[0] = 1;
	}
	else
	{
		retval[0] = 0;
	}
	if(status2 != 0)
	{
		retval[1] = 1;
	}
	else
	{
		retval[1] = 0;
	}
	if(status3 != 0)
	{
		retval[2] = 1;
	}
	else
	{
		retval[2] = 0;
	}
	if(status4 != 0)
	{
		retval[3] = 1;
	}
	else
	{
		retval[3] = 0;
	}
	char1 = (packet >> 4) & 0x7F;
	retval[4] =  char1;

	char2 = (packet >> 11) & 0x7F;
	retval[5] = char2;

	char3 = (packet >> 18) & 0x7F;
	retval[6] = char3;

	char4 = (packet >> 25) & 0x7F;
	retval [7] = char4;

	//cerr << retval[0] << endl;
	return;
}

int Hash_t::findFreeSpace(int index)
{
 //-1 = no free space
 //index = first free space
 //all empty = put in 0/ return 0;
	for(size_t i = 0; i < buckets[index].size(); i++)
	{
		int status1 = buckets[index][i] & 0x1;
		int status2 = (buckets[index][i] >> 1) & 0x1;
		int status3 = (buckets[index][i] >> 2) & 0x1;
		int status4 = (buckets[index][i] >> 3) & 0x1;

		if(status1 == 0 || status2 == 0 || status3 == 0 || status4 == 0)
		{
			//will return 0 if bucket is empty or index if is space is free
			return i;
		}
	}
	//bucket's full
	return -1;
}

unsigned int Hash_t::pack(unsigned int packet, char toPack)
{
	//index is given by findFreeSpace
	//packet = buckets[index][i]
	int status1 = (packet) & 0x1;
	int status2 = (packet >> 1) & 0x1;
	int status3 = (packet >> 2) & 0x1;
	int status4 = (packet >> 3) & 0x1;

	if(status1 == 0)
	{
		unsigned int temp = (packet & 0xFFFFF80F);//mask first char
		unsigned int temp2 = temp >> 4;//shift first char over

		temp2 |= (unsigned int)toPack;//or the char with empty space
		temp2 = temp2 << 4;//shift data  back over...have 0's now?

		temp |= temp2;//or temp 1 with 2 to replace trailing 0's and fill in new data
		temp |= 0x1; // or with one to set bit checker value to 1
		return temp;
	}
	else if(status2 == 0)
	{
		unsigned int temp = (packet & 0xFFFC07FF);//mask first char
		unsigned int temp2 = temp >> 11;//shift first char over

		temp2 |= (unsigned int)toPack;//or the char with empty space
		temp2 = temp2 << 11;//shift data  back over...have 0's now?

		temp |= temp2;//or temp 1 with 2 to replace trailing 0's and fill in new data
		temp |= 0x2; // or with one to set bit checker value to 1
		return temp;
	}
	else if(status3 == 0)
	{
		unsigned int temp = (packet & 0xFE03FFFF);//mask first char
		unsigned int temp2 = temp >> 18;//shift first char over

		temp2 |= (unsigned int)toPack;//or the char with empty space
		temp2 = temp2 << 18;//shift data  back over...have 0's now?

		temp |= temp2;//or temp 1 with 2 to replace trailing 0's and fill in new data
		temp |= 0x4; // or with one to set bit checker value to 1
		return temp;
	}
	else if(status4 == 0)
	{
		unsigned int temp = (packet & 0x1FFFFFF);//mask first char
		unsigned int temp2 = temp >> 25;//shift first char over

		temp2 |= (unsigned int)toPack;//or the char with empty space
		temp2 = temp2 << 25;//shift data  back over...have 0's now?

		temp |= temp2;//or temp 1 with 2 to replace trailing 0's and fill in new data
		temp |= 0x8; // or with one to set bit checker value to 1
		return temp;
	}
	fprintf(stderr, "HUGE ERROR IN PACK METHOD");
	return packet;
}

