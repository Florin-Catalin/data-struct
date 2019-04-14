#pragma once

#include <ccvector.h>


typedef struct _CC_HASH_NODE {
	char* Key;
	int Value;
	int Flag; // 0 I m free . 1 I m not
}CC_HASH_NODE;

typedef struct _CC_HASH_TABLE { 
	 CC_HASH_NODE ** Array;
	int Size;
	int Capacity;

} CC_HASH_TABLE; 





  
int HtCreate(CC_HASH_TABLE** HashTable); 
int HtDestroy(CC_HASH_TABLE** HashTable); 
 
int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value); 
int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value); 
int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key); 
int HtHasKey(CC_HASH_TABLE* HashTable, char* Key); 
int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key); 
int HtClear(CC_HASH_TABLE* HashTable); 
int HtGetKeyCount(CC_HASH_TABLE* HashTable);  
