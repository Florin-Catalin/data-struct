#include "ccvector.h"
#include "common.h"
#include <stdio.h>

void Swap(int* A, int*B )
{
	int t = *A;
	*A = *B;
	*B = t;
}


int Partition(int Array[], int Low, int High)
{
	int pivot = Array[High];    
	int i = (High - 1);  

	for (int j = Low; j <= High - 1; j++)
	{
		 
		if (Array[j] <= pivot)
		{
			i++;    
			Swap(&Array[i], &Array[j]);
		}
	}
	Swap(&Array[i + 1], &Array[High]);
	return (i + 1);
}

void QuickSort(int Array[], int Low, int High)
{
	if (Low < High)
	{
		
		int pi = Partition(Array, Low, High);

		
		QuickSort(Array, Low, pi - 1);
		QuickSort(Array, pi + 1, High);
	}
}

void PrintVector(CC_VECTOR *Vector)
{ 
	if (Vector == NULL)
	{
		printf("Null vector");
	}
	else {
		int i;
		printf("\n[ ");
		for (i = 0; i < Vector->Size; i++)
			printf("%d ", Vector->Array[i]);
		printf(" ]\n");
	}
}



int VecCreate(CC_VECTOR **Vector)
{
	if (Vector == NULL)
	{
		return -1;
	}
	(*Vector) = (CC_VECTOR *)malloc(sizeof(CC_VECTOR));
	
	if (*Vector == NULL)
	{
		return -1;
	}

	
	(*Vector)->Size = 0;
	(*Vector)->Capacity = 100;
	(*Vector)->Array = (int*)malloc(sizeof(int)* (*Vector)->Capacity);


	return 0;
}


int VecDestroy(CC_VECTOR **Vector)
{  
	if (Vector == NULL)
	{
		return -1;
	}

	if (*Vector == NULL)
	{
		return -1;
	}	
	(*Vector)->Capacity = 0;
	(*Vector)->Size = 0;
	if ((*Vector)->Array != NULL)
	{
		free((*Vector)->Array);
		free(*Vector);
	}
	
	return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{  
	if (Vector == NULL)
	{
		return -1;
	}
	if (Vector->Size >= Vector->Capacity) {
		Vector->Capacity *= 2;
		Vector->Array = realloc(Vector->Array, sizeof(int)*Vector->Capacity);
	if (Vector->Array == NULL)
		return -1;

	}
	


	Vector->Array[Vector->Size++] = Value;
	return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
	VecInsertTail(Vector, Value);
	int i, j;
	for (j= 0; j < Vector->Size - 1; j++) {
		int temp = Vector->Array[0];
		for (i = 0; i < Vector->Size - 1; i++)
			Vector->Array[i] = Vector->Array[i + 1];
		Vector->Array[i] = temp;
	}
	return 0; 
	
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
	VecInsertHead(Vector, Value);

	int i; 
	int temp = Value;
	for (i = 0; i < Index + 1 ; i++)
	{
		temp = Vector->Array[i + 1];
		Vector->Array[i + 1] = Vector->Array[i];
		Vector->Array[i] = temp;
	}
		
	
	return 0;
   
   
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
	if (NULL == Vector)
	{
		return -1;
	}
	 if (Index >= Vector->Size)

		 return -1;
	 int i; 
	 for (i = 0; i <= Vector->Size; i++)
		 Vector->Array[Index] = Vector->Array[Index + 1];

	 Vector->Size--; 
	 return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{ 
	
	if (NULL == Vector)
	{

		return -1;
	}
	if (Index >= Vector->Size)
		return -1;
	 
	*Value = Vector->Array[Index ];
	return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
	if (NULL == Vector)
	{
		return -1;
	}
	return Vector->Size;
}

int VecClear(CC_VECTOR *Vector)
{  
	
	if (NULL == Vector)
	{
		return -1;
	}
	Vector->Size = 0;
	Vector->Array = realloc(Vector->Array, sizeof(int)*Vector->Capacity);

	
    return 0;
}

int VecSort(CC_VECTOR *Vector)
{
	
	if (NULL == Vector)
	{
		return -1;
	}

	QuickSort(Vector->Array, 0, Vector->Size - 1);
	
	return 0;
}
