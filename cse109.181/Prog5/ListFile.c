/*
	CSE 109: Spring 2018
	Raymond Van Zandt
	rlv220
	C file that controls operations of the list
	Program #5
*/

#include"ListFile.h"
#include"Node.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>

void constructList(struct ListFile_t* it)
{
    it->head = NULL;
    it->size = 0;
}

void copyList(struct ListFile_t* it, struct ListFile_t* src)
{
    struct Node_t* srcCurrent = src->head;
    //  struct Node_t* itCurrent = it->head;
    //  size_t counter = 0;
    for(size_t i = 0; i< src->size; i++)
    {
        insert(it, srcCurrent->name, srcCurrent->data, srcCurrent->size);
        srcCurrent = srcCurrent->next;
    }
    free(srcCurrent);
/*
    while(srcCurrent)
    {
        struct Node_t* temp = (struct Node_t*)malloc(sizeof(struct Node_t));
        if(counter == 0)
        {
			setName(temp,srcCurrent->name);
            setData(temp,srcCurrent->data, srcCurrent->size);
            setNext(temp,getNext(srcCurrent));
	        temp->size = srcCurrent->size;
            itCurrent = temp;
            srcCurrent = getNext(srcCurrent);
            counter++;
        }
        else
        {
			setName(temp,srcCurrent->name);
            setData(temp,srcCurrent->data, srcCurrent->size);
            setNext(temp,getNext(srcCurrent));
            temp->size = srcCurrent->size;
            setNext(itCurrent,temp);
            itCurrent = getNext(itCurrent);
            srcCurrent = getNext(srcCurrent);
            counter++;
		}
    }
    it->size = counter;
*/
	return;
}

void cloneList(struct ListFile_t* it, struct ListFile_t* src)
{
    destroyList(it);//assume initailized so have to destroyList(it)
    struct Node_t* srcCurrent = src->head;
    for(size_t i = 0; i< src->size; i++)
    {
		insert(it, srcCurrent->name, srcCurrent->data, srcCurrent->size);
		srcCurrent = srcCurrent->next;
    }

	free(srcCurrent);
	return;
}

void destroyList(struct ListFile_t* it)
{
    if(it == NULL)
    {
		 return;
    }
    if(it->head == NULL)
    {
        return;
    }
    helper((it->head));
    return;
}

struct Node_t* helper(struct Node_t* node)
{
    if(getNext(node) != NULL)
    {
        helper(getNext(node));
    }
    destroyNode(node);
    free(node);
    return NULL;
}

int readFile(struct ListFile_t* it, const char* filename)
{
    int fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        fprintf(stderr, "Open file failed (%d): %s\n", errno, strerror(errno));
        return -1;
    }

    struct ListFile_t* tempList = (struct ListFile_t*)malloc(sizeof(struct ListFile_t));
    constructList(tempList);

    size_t numEle = 0;
    ssize_t result = 0;
    result = read(fd, &numEle, 8);
    if(result != sizeof(size_t))
    {
        fprintf(stderr, "Read of num elements failed (%d): %s\n", errno, strerror(errno));
        close(fd);
        return -1;
	}

    struct Node_t* current = tempList->head;
    for(size_t i = 0; i<numEle; i++)
    {
        size_t nameLength = 0;
        size_t size = 0;

        result = read(fd, &nameLength, 8);
        if(result != sizeof(size_t))
        {
            fprintf(stderr, "Read of name length failed (%d): %s\n", errno, strerror(errno));
            close(fd);
            destroyList(tempList);
            destroyList(it);
            destroyNode(current);
            return -1;
        }

        result = read(fd, &size, 8);
        if(result != sizeof(size_t))
        {
            fprintf(stderr, "Read of size failed (%d): %s\n", errno, strerror(errno));
            close(fd);
            destroyList(tempList);
            destroyList(it);
            destroyNode(current);
            return -1;
        }

        char* nameBuffer = (char*)malloc((nameLength+1) * sizeof(char));//+1 for '\0'
        result = read(fd, nameBuffer, nameLength);
        if(result != nameLength)
        {
            fprintf(stderr, "Read of name failed (%d): %s\n", errno, strerror(errno));
            free(nameBuffer);
            close(fd);
            destroyList(tempList);
            destroyList(it);
            destroyNode(current);
            return -1;
        }
		nameBuffer[nameLength] = '\0';

        void* dataBuffer = malloc(size);
        result = read(fd, dataBuffer, size);
        if(result != size)
        {
            fprintf(stderr, "Read of data failed (%d): %s\n", errno, strerror(errno));
            free(dataBuffer);
            close(fd);
            destroyList(tempList);
            destroyList(it);
            destroyNode(current);
            return -1;
        }
        insert(tempList, nameBuffer, dataBuffer, size);
        free(nameBuffer);
        free(dataBuffer);

    }
    if(close(fd) == -1)
    {
        fprintf(stderr, "Close file failed (%d): %s\n", errno, strerror(errno));
        return -1;
    }
	cloneList(it, tempList);
	destroyList(tempList);
	free(tempList);
    return 0;
}

size_t getSize(struct ListFile_t* it)
{
    if(it == NULL)
    {
        return 0;
    }
    return it->size;
}

int find(struct ListFile_t* it, const char* name)
{
    if(it == NULL)
	{
    	return 0;
    }
    if(it->head == NULL)
    {
        return 0;
    }

    struct Node_t* current = it->head;
    while(getNext(current) != NULL)
    {
        if(strcmp(current->name,name) == 0)
        {
            return 1;
        }
        current = getNext(current);
    }
    if(strcmp(current->name,name) == 0)
    {
        return 1;
    }
    return 0;
}

int removeByName(struct ListFile_t* it, const char* name)
{
    if(it == NULL)
    {
        return 0;
    }
    if(it->head == NULL)
    {
        return 0;
    }
    if(name == NULL)
    {
        return 0;
    }

    while(strcmp(it->head->name, name)== 0)
    {
		 struct Node_t* temp = it->head;
        it->head = getNext(temp);
        if(getNext(temp) == NULL)
        {
            destroyNode(temp);
            free(temp);
            it->size--;
            return 1;
        }
        destroyNode(temp);
        free(temp);
        it->size--;
        return 1;
    }
    struct Node_t* current = (it->head);
    while(getNext(current) != NULL)
    {
        if(strcmp(current->next->name, name)== 0)
        {
            struct Node_t* temp = getNext(current);
            setNext(current, getNext(temp));
            destroyNode(temp);
            free(temp);
            it->size--;
            return 1;
        }
        else
        {
            current = getNext(current);
        }
    }
    if(strcmp(current->name,name) == 0)
    {
        destroyNode(current);
        free(current);
        current = NULL;
        it->size--;
        return 1;
    }
    return 0;
}

int insert(struct ListFile_t* it, const char* name, void* data, size_t size)
{
    if(it->head  == NULL)
    {
        it->head = (struct Node_t*)malloc(1*sizeof(struct Node_t));
        constructNode(it->head, name, data, size, NULL);
        it->size = (it->size +1);
//		fprintf(stderr,"Head: %s\n", it->head->name);
        return 1;
    }

	struct Node_t* dup = it->head;
    while(getNext(dup) != NULL)
    {
        if(strcmp(dup->name,name) == 0)
        {
            return 0;
        }
        dup = dup->next;
    }
	struct Node_t* previous = it->head;
    struct Node_t* current = previous->next;
	if(strcmp(getName(previous), name) > 0)
	{
		struct Node_t* newNode = (struct Node_t*)malloc(sizeof(struct Node_t));
		constructNode(newNode,name,data,size,previous);
		it->head = newNode;
		it->size += 1;
		return 1;
	}
    while(current!= NULL)
    {
//		fprintf(stderr,"strcmp: %d to %d", strcmp(getName(current),name), strcmp(getName(getNext(current)),name));
        if(strcmp(getName(previous),name) < 0 && strcmp(getName(current),name) > 0)
        {
			//fprintf(stderr,"new name %s is bigger than %s and less than %s\n", name, current->name, current->next->name);

            struct Node_t* newNode = (struct Node_t*)malloc(1*sizeof(struct Node_t));
            constructNode(newNode, name,data,size,current);
            setNext(previous,newNode);//maybe not setting right?
            it->size = it->size +1;
            return 1;
        }
		//fprintf(stderr,"new name %s does not go here; %s and %s\n", name, current->name, current->next->name);
        previous = getNext(previous);
		current = getNext(current);
    }
    //if new node needs to go at the very end
    struct Node_t* newNode = (struct Node_t*)malloc(1*sizeof(struct Node_t));
    constructNode(newNode, name,data,size,NULL);
    setNext(previous,newNode);
    it->size = it->size +1;
    return 1;
}

ssize_t appendFromFile(struct ListFile_t* it, const char* filename)
{
    struct ListFile_t* newList =(struct ListFile_t*)malloc(sizeof(struct ListFile_t));
    constructList(newList);
    if(readFile(newList, filename) != 0)
    {
        free(newList);
        return -1;
    }
    int retval = newList->size;

    struct Node_t* newListCurrent = newList->head;
    while(newListCurrent)
    {
        insert(it,newListCurrent->name, newListCurrent->data, newListCurrent->size);
        newListCurrent = getNext(newListCurrent);
    }
    destroyList(newList);
    free(newList);
    return retval;
}

int saveToFile(struct ListFile_t* it, const char* filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        fprintf(stderr, "Open file failed (%d): %s\n", errno, strerror(errno));
        return -1;
    }

    ssize_t result = 0;
    size_t numElements = getSize(it);
    result = write(fd, &numElements, sizeof(size_t));
    if(result != sizeof(size_t))
    {
        fprintf(stderr, "Write of number of elements failed");
        close(fd);
        return -1;
 	}
    struct Node_t* current = it->head;
    for(size_t i = 0; i<numElements; i++)
    {
        size_t nameLength = 0;
        size_t size = getNodeSize(current);

		if(getName(current) == NULL)
		{
			nameLength = 0;
		}
		else
		{
			nameLength = strlen(getName(current));
		}

        result = write(fd, &nameLength, sizeof(size_t));
        if(result != sizeof(size_t))
        {
            fprintf(stderr, "Write of nameLength failed (%d): %s\n", errno, strerror(errno));
            close(fd);
            return -1;
        }


        result = write(fd, &size, sizeof(size_t));
        if(result != sizeof(size_t))
        {
            fprintf(stderr, "Write of size failed (%d): %s\n", errno, strerror(errno));
            close(fd);
            return -1;
        }


        result = write(fd, getName(current), nameLength);
        if(result != nameLength)
        {
            fprintf(stderr, "Write of name failed (%d): %s\n", errno, strerror(errno));
            close(fd);
			return -1;
        }


        result = write(fd, getData(current), size);
        if(result != size)
        {
            fprintf(stderr, "Write of data failed (%d): %s\n", errno, strerror(errno));
            close(fd);
            return -1;
        }
		current = current->next;
    }


    if(close(fd) == -1)
    {
        fprintf(stderr, "Close file failed (%d): %s\n", errno, strerror(errno));
        return -1;
    }
    return 1;
}

size_t getElementSize(struct ListFile_t* it, size_t index)
{
    if(it == NULL)
    {
        return 0;
    }
    if(index > it->size)
    {
        return 0;
    }
    size_t counter = 0;
    struct Node_t* current = it->head;
    while(current)
    {
        if(counter == index)
        {
            return current->size;
        }
        current = current->next;
        counter++;
	}
    return 0;
}

void* getElementData(struct ListFile_t* it, size_t index)
{
    if(it == NULL)
    {
        return NULL;
    }
    if(index > it->size)
    {
        return NULL;
    }
    size_t counter = 0;
    struct Node_t* current = it->head;
    while(current)
    {
        if(counter == index)
        {
            return current->data;
        }
        current = current->next;
        counter++;
    }
    return NULL;
}

const char* getElementName(struct ListFile_t* it, size_t index)
{
    if(it == NULL)
    {
        return NULL;
    }
  if(index > it->size)
    {
        return NULL;
    }
    struct Node_t* current = it->head;
    size_t counter = 0;
    while(current)
    {
        if(counter == index)
		{
            return current->name;
        }
        current = current->next;
        counter++;
    }
    return NULL;
}

