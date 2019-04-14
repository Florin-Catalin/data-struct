#include "ccstack.h"

#include "common.h"


void printStack(CC_STACK *Stack)
{
	int i;
	printf("\nTOP ->: ");
	for (i = StGetCount(Stack) - 1 ; i >= 0; i--)
	{ 
   
		printf("\n| ");
		printf("%d ", Stack->StackPtr[i]);
		printf(" |");
	}

	printf(" \n");
}

int StCreate(CC_STACK **Stack)
{
	
	if (Stack == NULL)
	{
		return -1;
	}
	(*Stack) = (CC_STACK *)malloc(sizeof(CC_STACK));
	if (*Stack == NULL)
	{
		return -1;
	}


	(*Stack)->Size = 0;
	(*Stack)->Capacity = 100;
	(*Stack)->StackPtr = (int*)malloc (sizeof(int)*(*Stack) ->Capacity );
	
	return 0;
}

int StDestroy(CC_STACK **Stack)
{
	if (Stack == NULL)
	{
		return -1;
	}


	if (*Stack == NULL)
	{
		return -1;
	}	
	(*Stack)->Capacity = 0;
	(*Stack)->Size = 0;
	if ((*Stack)->StackPtr != NULL)
	{
		free((*Stack)->StackPtr);
		free(*Stack);
	}
	return 0; 
}

int StPush(CC_STACK *Stack, int Value)
{
	if (NULL == Stack)
	{
		return -1;
	}
	if (Stack->Size >= Stack->Capacity) {
		Stack->Capacity *= 2;
		Stack->StackPtr = realloc(Stack->StackPtr, sizeof(int)*Stack->Capacity);
		if (Stack->StackPtr == NULL)
			return -1;

	}
	Stack->StackPtr[Stack->Size++] = Value;
	return 0;
}
	

int StPop(CC_STACK *Stack, int *Value)
{
	if (NULL == Stack)
	{
		return -1;
	}
	*Value = Stack->StackPtr[Stack->Size -1 ];
	Stack->Size--;
	if (0 == Stack->Size)
	{
		Stack->StackPtr = NULL;
	}
	
    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
	if (NULL == Stack)
	{
		return -1;
	}
	*Value = Stack->StackPtr[Stack->Size - 1];
    return 0;
}


int StIsEmpty(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}
	if (0 != Stack->Size)
	{
		return 0;
	}
	else

    return 1;
}

int StGetCount(CC_STACK *Stack)
{  
	if (NULL == Stack)
	{
		return -1;
	}
    
    return Stack->Size;
}

int StClear(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}
	Stack->Size = 0;
	Stack->StackPtr = realloc(Stack->StackPtr, sizeof(int)*Stack->Capacity);

    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{ 
	if ((NULL == Stack) || (NULL == StackToPush))
	{
		return -1;
	}
	int i; 
	for (i = 0; i < StackToPush->Size; i++)
		StPush(Stack, StackToPush->StackPtr[i]);
	StClear(StackToPush);
	return 0;
}
