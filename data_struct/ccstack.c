#include "ccstack.h"
#include "common.h"

int StCreate(CC_STACK **Stack)
{
	CC_STACK* stack = NULL;

	
	if (NULL == Stack)
	{
		return -1;
	}

	stack = (CC_STACK*)malloc(sizeof(CC_STACK));

	if (NULL == stack)
	{
		return -1;
	}

	memset(stack, 0, sizeof(*stack));

	stack->Top = (NODE*)malloc(sizeof(NODE));
	if (NULL == stack->Top)
	{
		free(stack);
		return -1;
	}
	stack->Top->Link = NULL;
	stack->Count = 0;
	stack->Top->Data = -1;
	*Stack = stack;
	
    return 0;
}

int StDestroy(CC_STACK **Stack)
{
	CC_STACK* stack = *Stack;

	if (NULL == Stack)
	{
		return -1;
	}
	
	free(stack->Top);
	free(stack);

	*Stack = NULL;
    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
	if (NULL == Stack)
	{
		return -1;
    }
	NODE* newNode = NULL;
	newNode = (NODE*)malloc(sizeof(NODE));

	if (NULL == newNode)
	{
		return -1;
	}
	newNode->Data = Value;
	newNode->Link = Stack->Top;
	Stack->Top = newNode;
	Stack->Count++;

    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
	if (NULL == Stack)
	{
		return -1;
	}
	if ((NULL == Stack->Top )|| (NULL == Value))
	{
		return -1;
	}
	if (0 == Stack->Count)
	{
		return -1;
	}
	NODE* newNode = NULL;
	newNode = (NODE*)malloc(sizeof(NODE));
	//save top node into a temporary node
	newNode = Stack->Top;
	//assign second node to top 
	Stack->Top = Stack->Top->Link;
	Stack->Count--;
	//destory the connection(pointer) between first and second
	newNode->Link = NULL;
	*Value = newNode->Data;
	free(newNode);

    return  0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
	if (NULL == Stack)
	{
		return -1;
	}
	if (NULL == Stack->Top)
	{
		return -1;
	}
	if (0 == Stack->Count)
	{
		return -1;
	}
	*Value = Stack->Top->Data;
    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}
    return 0 == Stack->Count;
}

int StGetCount(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
   }

    return Stack->Count;
}

int StClear(CC_STACK *Stack)
{
	if (NULL == Stack)
	{
		return -1;
	}

	while (Stack-> Count != 0)
	{
		int temp = 0;
		StPop(Stack, &temp);
	}
    return 0;
}


int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
	if ((NULL == Stack) || (NULL == StackToPush))
	{
		return -1;
	}
	

	NODE* newNode = NULL;
	newNode = (NODE*)malloc(sizeof(NODE));
	newNode = StackToPush->Top;

	while (newNode->Link->Link != NULL)
	{
		newNode = newNode->Link;
		
	}
	newNode->Link = Stack->Top;
	StackToPush->Count += Stack->Count  ;
	
	return 0;
}
