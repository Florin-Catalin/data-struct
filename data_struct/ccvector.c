#include "ccvector.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE   3

void debug(int arr[] , int size)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	
}
int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;

 

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));

    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );

    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
		Vector->Size *= 2;
		int* newArray = NULL;
			newArray = realloc(Vector->Array, sizeof(int) * Vector->Size);
			if (NULL != newArray)
			{
				
				Vector->Array = newArray;
		    }
			else
			{
				/* realloc cannot find enough space */
				return -1;
			}
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
 

    if (NULL == Vector)
    {
        return -1;
    }
	
    if (Vector->Count >= Vector->Size)
    {
		Vector->Size *= 2;
		int* newArray = NULL;
		 newArray = realloc(Vector->Array, sizeof(int) * Vector->Size);
		if (NULL != newArray)
		{

			Vector->Array = newArray;
		}
		else
		{
			/* realloc cannot find enough space */
			return -1;
		}
    }
	
	for (int i = Vector->Count - 1; i >= 0; i--)
	{
		
			Vector->Array[i + 1] = Vector->Array[i];
		
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR* Vector, int Index, int Value)
{


	if (NULL == Vector)
	{
		return -1;
	}

	if ((Index < 0) || (Index >= Vector->Count))
	{
		return -1;
	}

	if (Vector->Count >= Vector->Size)
	{   
		Vector->Size *= 2;
		int* newArray = NULL;
		newArray = realloc(Vector->Array, sizeof(int) * Vector->Size);
		if (NULL != newArray)
		{

			Vector->Array = newArray;
		}
		else
		{
			/* realloc cannot find enough space */
			return -1;
		}


		for (int i = Vector->Count ; i > Index; i--)
		{
			Vector->Array[i ] = Vector->Array[i - 1];
		}
		Vector->Array[ Index + 1 ] = Value;
		Vector->Count++;

		return 0;
	}
	return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
  
	if (NULL == Vector)
	{
		return -1; 
	}
	
	if ( (Index < 0) || (Index >= Vector->Count))
	{
		return -1;
	}
	for (int i = Index; i <= Vector->Count; i++)
	{
		Vector->Array[Index] = Vector->Array[Index + 1];
	}

	--Vector->Count;

	if (Vector->Count <= Vector->Size / 2)
	{
		Vector->Size /= 2;
		int* newArray = NULL;
		newArray = realloc(Vector->Array, sizeof(int) * Vector->Size);
		if (NULL != newArray)
		{

			Vector->Array = newArray;
		}
		else
		{
			/* realloc cannot find enough space */
			return -1;
		}
	}

    return 0;
}


int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
	if (NULL == Vector)
	{
		return -1;
	}
	if ((Index < 0) || (Index >= Vector->Count))
	{
		return -1;
	}

	*Value = Vector->Array[Index];
    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
   
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
   
	if (NULL == Vector)
	{
		return -1; 
	}
	Vector->Size = INITIAL_SIZE;
	Vector->Count = 0;
	int* newArray = NULL;
	newArray = realloc(Vector->Array, sizeof(int) * Vector->Size);
	if (NULL != newArray)
	{

		Vector->Array = newArray;
	}
	else
	{
		/* realloc cannot find enough space */
		return -1;
	}
    return 0;
}


// A utility function to swap two elements
static void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
	array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
static int partition(int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is bigger than the pivot 
		if (arr[j] > pivot)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
static void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int VecSort(CC_VECTOR *Vector)
{
	if (NULL == Vector)
	{
		return -1;
	}
	quickSort(Vector->Array, 0, Vector->Count-1);
    return 0;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
	if ((NULL == DestVector) && (NULL == SrcVector))
	{
		return -1;
	}

	for (int i = 0; i <= SrcVector->Count -1 ; i++)
	{
		VecInsertTail(DestVector, SrcVector->Array[i]);

	}



    return 0;
}
