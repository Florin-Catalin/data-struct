#include "cchashtable.h"
#include "common.h"



size_t strlen1(const char* _str)
{
	size_t i = 0;
	while (_str[i++]);
	return i;
}
int strcmp1(char string1[], char string2[])
{
	for (int i = 0; ; i++)
	{
		if (string1[i] != string2[i])
		{
			return string1[i] < string2[i] ? -1 : 1;
		}

		if (string1[i] == '\0')
		{
			return 0;
		}
	}
}

char* strcpy0(char* d, char* s) {
	char* saved = d;
	while ((*d++ = *s++) != '\0');

	return saved; //returning starting address of s1
}

char* strcpy1(char* destination, const char* source)
{
	// return if no memory is allocated to the destination
	if (destination == NULL)
		return NULL;

	// take a pointer pointing to the beginning of destination string
	char* ptr = destination;

	// copy the C-string pointed by source into the array
	// pointed by destination
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	// include the terminating null character
	*destination = '\0';

	// destination is returned by standard strcpy()
	return ptr;
}

unsigned long hash(char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}
CC_HASH_NODE* initNode(CC_HASH_NODE* Node)
{
	Node->Flag = 0;
	return Node;
}

int HtCreate(CC_HASH_TABLE * *HashTable)
	{


	if (HashTable == NULL)
	{
		return -1;
	}
		if (NULL == ((*HashTable = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE)))))
		{
			return -1;

		}
		(*HashTable)->Size = 0;
		(*HashTable)->Capacity = 10;
		(*HashTable)->Array = malloc(sizeof(CC_HASH_NODE) * (*HashTable)->Capacity);

		

		int i = 0;

		for (i = 0; i < (*HashTable)->Capacity; i++)
		{
			(*HashTable)->Array[i] = malloc(sizeof(CC_HASH_NODE));
			(*HashTable)->Array[i]->Flag = 0;
			(*HashTable)->Array[i]->Key = "null";
			(*HashTable)->Array[i]->Value = -1;
		}


		return 0;
	}

int HtDestroy(CC_HASH_TABLE **HashTable)
{
	if (NULL == HashTable)
		return -1;

	if (NULL == *HashTable)
		return -1;

	if ((*HashTable)->Array != NULL)
	{
		free((*HashTable)->Array);
		free(*HashTable);
	}


	return 0;
}

int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
	if (HashTable == NULL)
		return -1;

	if ((float)(HashTable->Size / HashTable->Capacity) > 0.75)
	{
		int i = 0;
		for (i = HashTable->Capacity; i < 2 * HashTable->Capacity; i++)
		{
			HashTable->Array[i] = malloc(sizeof(CC_HASH_NODE));
			HashTable->Array[i]->Flag = 0;
		}
		HashTable->Capacity *= 2;
	}

	int Index = hash(Key) % HashTable->Capacity;
	while (HashTable->Array[Index]->Flag != 0)
	{
		Index++;
		Index %= HashTable->Capacity;
	}

	if (HashTable->Array[Index]->Flag == 0)
	{
		HashTable->Size++;
		HashTable->Array[Index]->Value = Value;
		HashTable->Array[Index]->Key = Key;
		HashTable->Array[Index]->Flag = 1;
	}
	return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
	if (NULL == HashTable)
		return -1;

	int Index = hash(Key) % HashTable->Capacity;

	while (HashTable->Array[Index]->Flag != 0)
	{
		int counter = 0;
		if (counter++ > HashTable->Capacity)
			return -1;
		if (strcmp(HashTable->Array[Index]->Key, Key) == 0)
		{
			*Value = HashTable->Array[Index]->Value;
			return 0;
		}
		Index++;
		Index %= HashTable->Capacity;
	}
	return -1;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
	if (NULL == HashTable)
		return -1;

	int Index = hash(Key);

	while (HashTable->Array[Index]->Flag != 0)
	{

		int counter = 0;
		if (counter++ > HashTable->Capacity)
			return -1;
		if (strcmp(HashTable->Array[Index]->Key, Key) == 0)
		{
			HashTable->Array[Index]->Flag = 0;
			HashTable->Array[Index]->Key = "null";
			HashTable->Array[Index]->Value = -1;
			HashTable->Size--;
			return 0;
		}
		Index++;
		Index %= HashTable->Capacity;

	}

	return 0;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
	int found = 0;
	if (NULL == HashTable)
		return -1;



	int i = 0;
	for (i = 0; i < HashTable->Capacity; i++)
	{
		if (HashTable->Array[i]->Flag != 0)
			if (strcmp(HashTable->Array[i]->Key, Key) == 0)
				found = 1;
	}
	if (found)
	{
		return 0;
	}

	return -1;

}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    CC_HASH_TABLE_ITERATOR *iterator = NULL;


    if (NULL == HashTable)
    {
        return -1;
    }
    if (NULL == Iterator)
    {
        return -1;
    }
    if (NULL == Key)
    {
        return -1;
    }

    iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
    if (NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;
    // INITIALIZE THE REST OF THE FIELDS OF iterator

    *Iterator = iterator;

    // FIND THE FIRST KEY AND SET Key
	for (int i = 0; i < (*Iterator) ->HashTable->Capacity; i++)
	{
		if(HashTable->Array[i]->Flag != 0) {
			strcpy1((*Key), HashTable->Array[i]->Key);
			(*Iterator)->State = i;
			break;
		}
	}
    return 0;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
	if (NULL == Iterator)
	{
		return -1;
	}
	if (NULL == Key)
	{
		return -1;
	}

	for (int i = Iterator->State; i < Iterator->HashTable->Capacity; i++)
	{
		if (Iterator->HashTable->Array[i]->Flag != 0) {
			strcpy1((*Key), Iterator->HashTable->Array[i]->Key);
			Iterator->State = i;
			break;
		}
	}
    return -1;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
	if (NULL == Iterator)
		return -1;

	if (NULL == *Iterator)
		return -1;

	memset(Iterator, 0, sizeof(*Iterator));
	free((*Iterator)->HashTable);
    return -1;
}

int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key)
{
	if (HashTable == NULL)
		return -1;
	if (Index > HashTable->Size)
		return -1;


	int i = 0;
	for (i = Index; i < HashTable->Capacity; i++)
	{
		if (HashTable->Array[i]->Flag != 0) {
			strcpy1((*Key), HashTable->Array[i]->Key);
			break;
		}

	}


	return 0;
}
int HtClear(CC_HASH_TABLE *HashTable)
{
	if (NULL == HashTable)
		return -1;

	int i;
	for (i = 0; i < HashTable->Capacity; i++)
	{

		HashTable->Array[i]->Flag = 0;
		HashTable->Array[i]->Key = "null";
		HashTable->Array[i]->Value = -1;
	}
	return 0;


}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
	if (NULL == HashTable)
		return -1;
	return HashTable->Size;
}
