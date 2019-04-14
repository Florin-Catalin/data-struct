#include "cctree.h"
#include "common.h"

static int Height(CC_NODE *Node)
{
	if (NULL == Node)
	{
		return -1;
	}
	return Node->height;
}

static int GetBalance(CC_NODE *Node)
{
	if (NULL == Node)
	{
		return -1;
	}
 
	return  Height(Node->left) - Height(Node->right);
}

CC_NODE* MinValueNode(CC_NODE* Node)
{
	CC_NODE* current = Node;

	//loop down to find the leftmost leaf
	while (current->left != NULL)
		current = current->left;
	return current;
}


/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
CC_NODE* NewNode(int Key)
{
	CC_NODE* node = (CC_NODE*) malloc(sizeof( CC_NODE));
	node->data = Key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;  // new node is initially added at leaf 
	node->count = 1;
	return(node);
}
static CC_NODE *RightRotate(CC_NODE *Y)
{
	CC_NODE *x = Y->left;
	CC_NODE *T2 = x->right;

	// Perform rotation 
	x->right = Y;
	Y->left = T2;

	// Update heights 
	Y->height = max(Height(Y->left), Height(Y->right)) + 1;
	x->height = max(Height(x->left), Height(x->right)) + 1;

	// Return new root 
	return x;
}
 static CC_NODE *LeftRotate( CC_NODE *X)
{
	CC_NODE *y = X->right;
	CC_NODE *T2 = y->left;

	// Perform rotation 
	y->left = X;
	X->right = T2;

	//  Update heights 
	X->height = max(Height(X->left), Height(X->right)) + 1;
	y->height = max(Height(y->left), Height(y->right)) + 1;

	// Return new root 
	return y;
}

 CC_NODE* Insert(CC_NODE* Node, int Key)
 {
	 /* 1.  Perform the normal BST insertion */
	 if (Node == NULL)
		 return(NewNode(Key));

	 //If key already exists in BST, increment count and return
	 if (Key == Node->data)
	 {
		 (Node->count)++;
		 return Node;
	 }


	
	 if (Key < Node->data)
		 Node->left = Insert(Node->left, Key);
	 else if (Key > Node->data)
		 Node->right = Insert(Node->right, Key);
	 

	 Node->height = 1 + max(Height(Node->left),
		 Height(Node->right));


	 int balance = GetBalance(Node);

	  
	 if (balance > 1 && Key < Node->left->data)
		 return RightRotate(Node);

	
	 if (balance < -1 && Key > Node->right->data)
		 return LeftRotate(Node);

	 if (balance > 1 && Key > Node->left->data)
	 {
		 Node->left = LeftRotate(Node->left);
		 return RightRotate(Node);
	 }

	 // Right Left Case 
	 if (balance < -1 && Key < Node->right->data)
	 {
		 Node->right = RightRotate(Node->right);
		 return LeftRotate(Node);
	 }

	 /* return the (unchanged) node pointer */
	 return Node;
 }

 CC_NODE* DeleteNode(CC_NODE* Root, int Data) 
{ 
 
	 if (NULL == Root)
	 {
		 return Root;
	 }
  
    
    if ( Data < Root->data ) 
        Root->left = DeleteNode(Root->left, Data); 
  
    else if( Data > Root->data ) 
        Root->right = DeleteNode(Root->right, Data); 
  

    else
    { 
        /* Deoarece stergem toate nodurile cu valoare respectiva
        if (Root->count > 1) 
        { 
            (Root->count)--; 
           return 0; 
        } 
		*/
       
        if( (Root->left == NULL) || (Root->right == NULL) ) 
        { 
            CC_NODE *temp = Root->left ? Root->left : Root->right; 
  
            
            if(temp == NULL) 
            { 
                temp = Root; 
                Root = NULL; 
            } 
            else 
             *Root = *temp; 
  
            free(temp); 
        } 
        else
        { 
            
            CC_NODE* temp = MinValueNode(Root->right); 
  
            
            Root->data = temp->data; 
  
         
            Root->right = DeleteNode(Root->right, temp->data); 
        } 
    } 
  
    
	if (Root == NULL)
	{
		return Root;
	}
  
    
    Root->height = max(Height(Root->left), Height(Root->right)) + 1; 
  
   
    int balance = GetBalance(Root); 
  
     
    if (balance > 1 && GetBalance(Root->left) >= 0) 
        return RightRotate(Root); 
  
    
    if (balance > 1 && GetBalance(Root->left) < 0) 
    { 
        Root->left =  LeftRotate(Root->left); 
        return RightRotate(Root); 
    } 
  
    
    if (balance < -1 && GetBalance(Root->right) <= 0) 
        return LeftRotate(Root); 
  
    
    if (balance < -1 && GetBalance(Root->right) > 0) 
    { 
        Root->right = RightRotate(Root->right); 
        return LeftRotate(Root); 
    } 
  
    return Root; 
} 

 // A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
 void preOrder(CC_NODE *root)
 {
	 if (root != NULL )
	 {
		 printf("%d(%d) ", root->data,root->count);
		 preOrder(root->left);
		 preOrder(root->right);
	 }
 }


int TreeCreate(CC_TREE **Tree)
{
	if (NULL == Tree)
		return -1;
	*Tree = (CC_TREE*)malloc(sizeof(CC_TREE));
	if (NULL == (*Tree))
		return -1;
	(*Tree)->root = NULL;
	(*Tree)->size = 0;
	
    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{   
	if (NULL == Tree)
		return -1;
	if (NULL == *Tree)
		return -1;
	(*Tree)->size = 0;
	
	if ((*Tree)->root != NULL)
	{
		free((*Tree)->root);
		free(*Tree);
	}

    
    return 0;
}

int TreeInsert(CC_TREE *Tree, int Value)
{ 
	if (NULL == Tree)
		return -1;

	Tree->root = Insert(Tree->root, Value);
	Tree->size++;

    return 0;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
	if (NULL == Tree)
		return -1;
	Tree->root = DeleteNode(Tree->root, Value);
	Tree->size--;
    return 0;
}


int IsNode(CC_NODE* Root, int key)
{
	
	if (NULL == Root) return 0;
	if (key == Root->data) return 1;
	if (key < Root->data) return IsNode(Root->left, key);
	return IsNode(Root->right, key);
	
}
int TreeContains(CC_TREE *Tree, int Value)
{
    if (NULL == Tree)
    return -1;
	return IsNode(Tree->root,Value);
}

int TreeGetCount(CC_TREE *Tree)
{
	if (NULL == Tree)
		return -1;
   
    return Tree->size;
}

int TreeGetHeight(CC_TREE *Tree)
{
	if (NULL == Tree)
		return -1;

    return Height(Tree->root);
}

int TreeClear(CC_TREE *Tree)
{
	if (NULL == Tree)
		return -1;

    return 0;
}

int NthPreordernode(CC_NODE* Node, int Index)
{
	static int flag = 0;
	static int data = 0;

	if (NULL == Node)
		return -1;

	if (flag <= Index) {
		flag++;
		//prints the Index-th node of preorder traversal
		if(flag == Index)
		data = Node->data;
		NthPreordernode(Node->left, Index);
		NthPreordernode(Node->right, Index);
	}
	return data;

}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{ 
	if (NULL == Tree)
		return -1;
	if (Index > Tree->size)
		return -1;
    
	*Value = NthPreordernode(Tree->root, Index);
    return 0;
}



int NthInordernode(CC_NODE* Node, int Index)
{
	static int flag = 0;
	static int data = 0;

	if (NULL == Node)
		return -1;


	if (flag <= Index) {
		//first recur on left child
		NthInordernode(Node->left, Index);
		flag++;  

		if (flag == Index)
			data = Node->data;

		NthInordernode(Node->right, Index);
	}
	return data;

}
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
	if (NULL == Tree)
		return -1;
	if (Index > Tree->size)
		return -1;

	*Value = NthInordernode(Tree->root, Index);
	return 0;
}



int NthPostordernode(CC_NODE* Node, int Index)
{
	static int flag = 0;
	static int data = 0;

	if (NULL == Node)
		return -1;

	if (flag <= Index) {
		//first recur on left child
		NthPostordernode(Node->right, Index);
		NthPostordernode(Node->left, Index);
		flag++;

		if (flag == Index)
			data = Node->data;


	
	}
	return data;

}
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{

	if (NULL == Tree)
		return -1;
	if (Index > Tree->size)
		return -1;

	*Value = NthPostordernode(Tree->root, Index);
	return 0;
    
}

