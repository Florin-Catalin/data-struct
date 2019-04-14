#include "ccheap.h"
#include "common.h"

static void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void PrettyPrint(int *Array, int Size, int Index, int  Level)
{
	if (Index < Size) {
		int st = 2 * Index + 1;
		int dr = 2 * Index + 2;
		PrettyPrint(Array, Size, dr, Level + 1);
		for (int j = 0; j < Level; j++)
			printf("\t");
		printf("%d\n\n", Array[Index]);
		PrettyPrint(Array, Size, st, Level + 1);
	}
}
static void MaxHeapify(int *Arr , int Index ,int Size) 
{
	int st, dr, ind_max;

	st = 2 * Index + 1;
	dr = 2 * Index + 2;

	if (st < Size && Arr[st] > Arr[Index])
		ind_max = st;
	else
		ind_max = Index;
	if (dr < Size && Arr[dr] > Arr[ind_max])
		ind_max = dr;
	if (ind_max != Index)
	{
		swap(&Arr[Index], &Arr[ind_max]);
		MaxHeapify(Arr, ind_max, Size);
	}
}
static void MinHeapify(int *Arr, int Index, int Size)
{
	int st, dr, ind_min;

	st = 2 * Index + 1;
	dr = 2 * Index + 2;

	if (st < Size && Arr[st] < Arr[Index])
		ind_min = st;
	else
		ind_min = Index;
	if (dr < Size && Arr[dr] < Arr[ind_min])
		ind_min = dr;
	if (ind_min != Index)
	{
		swap(&Arr[Index], &Arr[ind_min]);
		MinHeapify(Arr, ind_min, Size);
	}
}
static void BottomUpBuildMax(int *Array, int Size)
{
	int i; 
	for (i = Size / 2; i >= 0; i--)
		MaxHeapify(Array, i, Size);
}
static void BottomUpBuildMin(int *Array, int Size)
{
	int i;
	for (i = Size / 2; i >= 0; i--)
		MinHeapify(Array, i, Size);
}
int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
	if (NULL == MaxHeap)
	{
		return -1;
	}
	(*MaxHeap) = (CC_HEAP *)malloc(sizeof(CC_HEAP));
	if (*MaxHeap == NULL)
	{
		return -1;
	}

	
	if (NULL == InitialElements)
	{
		(*MaxHeap)->Size = 0;
		(*MaxHeap)->Capacity = 10;
		(*MaxHeap)->Array = malloc(sizeof(int)*(*MaxHeap)->Capacity);
	}
	else
	{
		(*MaxHeap)->Size = InitialElements->Size;
		(*MaxHeap)->Capacity = InitialElements->Capacity;
		(*MaxHeap)->Array = InitialElements->Array;
	}
	(*MaxHeap)->HeapTypeFlag = 1;
	BottomUpBuildMax((*MaxHeap)->Array, (*MaxHeap)->Size);
   
	 
    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
	if (NULL == MinHeap)
	{
		return -1;
	}
	(*MinHeap) = (CC_HEAP *)malloc(sizeof(CC_HEAP));
	if (*MinHeap == NULL)
	{
		return -1;
	}


	if (NULL == InitialElements)
	{
		(*MinHeap)->Size = 0;
		(*MinHeap)->Capacity = 10;
		(*MinHeap)->Array = malloc(sizeof(int)*(*MinHeap)->Capacity);
	}
	else
	{
		(*MinHeap)->Size = InitialElements->Size;
		(*MinHeap)->Capacity = InitialElements->Capacity;
		(*MinHeap)->Array = InitialElements->Array;
	}
	(*MinHeap)->HeapTypeFlag = 0;
	BottomUpBuildMin((*MinHeap)->Array, (*MinHeap)->Size);
	
    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{

	if (Heap == NULL)
		return -1;

	if (*Heap == NULL)
	{
		return -1;
	}
	(*Heap)->Capacity = 0;
	(*Heap)->Size = 0;
	(*Heap)->HeapTypeFlag = 0;
	if ((*Heap)->Array != NULL)
	{
		free((*Heap)->Array);
		free(*Heap);
	}

	return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{   
	if (NULL == Heap)
	{
		return -1;
	}
	if (Heap->Size >= Heap->Capacity) {
		Heap->Capacity *= 2;
		Heap->Array = realloc(Heap->Array, sizeof(int)*Heap->Capacity);
		if (Heap->Array == NULL)
			return -1;
	}

	Heap->Array[Heap->Size++] = Value;

	if (Heap ->HeapTypeFlag == 1 )
	BottomUpBuildMax(Heap->Array, Heap->Size);
	else 
		BottomUpBuildMin(Heap->Array, Heap->Size);

	


    
    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
	int i;
	int j;
	if (NULL == Heap)
	{
		return -1;

	}

	
	for (i = 0; i < Heap->Size; i++)
	{
		if (Heap->Array[i] == Value)
		{
			for (j = i ; j < Heap->Size; j++)
			Heap->Array[j] = Heap->Array[j + 1];
			Heap->Size--;
		}
	}




	if (Heap->HeapTypeFlag == 1)
		BottomUpBuildMax(Heap->Array, Heap->Size);
	else
		BottomUpBuildMin(Heap->Array, Heap->Size);
 
    return -1;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	
	int i = 0;
	
	if (NULL == Heap)
	{
		return -1;
	}

	if (Heap->HeapTypeFlag == 0)
	{
		*ExtremeValue = 9999999;//or INT_MAX whatever
		for (i = 0; i < Heap->Size; i++)
		{
			if (Heap->Array[i] < *ExtremeValue)
				*ExtremeValue = Heap->Array[i];
		}
	}
	else
	{
		*ExtremeValue = 0;
		for (i = 0; i < Heap->Size; i++)
		{
			if (Heap->Array[i] > *ExtremeValue)
				*ExtremeValue = Heap->Array[i];
		}
	}

    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
	HpGetExtreme(Heap, ExtremeValue);
	HpRemove(Heap, *ExtremeValue);
    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
	if (NULL == Heap)
	{
		return -1;

	}
	return Heap->Size;
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
	if (NULL == Heap)
	{
		return -1;
	}
	if (NULL == SortedVector)
	{
		VecCreate(&SortedVector);
	}
	CC_HEAP* tempHeap;
	CC_VECTOR* tempVector;

	VecCreate(&tempVector);

	int i = 0;
	for (i = 0; i < Heap->Size; i++)
	{
		VecInsertTail(tempVector, Heap->Array[i]);
	}


	if (Heap->HeapTypeFlag)
	{
		HpCreateMaxHeap(&tempHeap, tempVector);
		
		for (i = tempHeap->Size - 1; i >= 0; i--)
		{
			swap(&tempHeap->Array[0], &tempHeap->Array[i]);
			tempHeap->Size = i;
			BottomUpBuildMax(tempHeap->Array, i);
		}
		tempHeap->Size = Heap->Size;
		SortedVector->Array = tempHeap->Array;
		SortedVector->Capacity = tempHeap->Capacity; 
		SortedVector->Size = tempHeap->Size;
		
	}
	else
	{
		HpCreateMinHeap(&tempHeap, tempVector);
		while (tempHeap->Size != 0)
		{
			VecInsertTail(SortedVector, tempHeap->Array[0]);
			HpRemove(tempHeap, tempHeap->Array[0]);
		}
	}

	

    return 0;
}
