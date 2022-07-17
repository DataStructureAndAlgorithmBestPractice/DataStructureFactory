#include "CVALHash.h"

// char To int
int CharToInt (char c)
{
    int arr[]={0,1,2,3,4,5,6,7,8,9};
    return arr[c-'0'];
}

// int To char
char IntToChar (int i)
{
    return (char)(i + '0');
}

// Print Tree Data
void InfoTreeBST (const struct BinarySearchTree* bst)
{
    if ( IsTreeEmptyBST(bst) ) return;

    printf("\n---Here Is A Full Summary Of BST---\n");

    if (IsNodeEmptyBST(bst->Root))     printf("Root is empty.\n");
    else                                      printf("BST Root Pointer Address: %p\n", bst->Root);

    if (IsNodeEmptyBST(bst->Reserved)) printf("Reserved is empty.\n");
    else                                      printf("BST Reserved Pointer Address: %p\n", bst->Reserved);


    printf("BST Initial Pool Count: %zu\n",      bst->PoolCapacity);
    printf("BST Future Pool Additions: %zu\n",   bst->FutureCapAdd);


    if (!IsNodeEmptyBST(bst->Root))
    {
        printf("\n---Here Is Root Branch Data---\n");
        PreorderTransversalBST (bst);
    }

    if (!IsNodeEmptyBST(bst->Reserved))
    {
        printf("\n---Here Is Reserved Node Data---\n");
        ReservedNodeMarching (bst);;
    }

}

// Print Node Tree Data
void InfoNodeBST (const struct tree_node* trNode)
{
    if (IsNodeEmptyBST(trNode)) return;
    printf("BST Node Left Pointer Address : %p\n", trNode->left_child);
    printf("BST Node Pointer      Address : %p\n", trNode);
    printf("BST Node CVAL Pointer Address : %p\n", trNode->CVALData);
    printf("BST Node CVAL String Data     : %s\n", trNode->CVALData);
    printf("BST Node Right Pointer Address: %p\n", trNode->right_child);
    printf("\n");
}

// Print Node Tree Data
void ReservedNodeMarching (const struct BinarySearchTree* BST)
{
    struct tree_node* trNodeIter = BST->Reserved;
    unsigned i = 0;
    while (trNodeIter!=NULL)
    {
        printf("(%u)\n", i);
        i++;
        InfoNodeBST (trNodeIter);
        trNodeIter = trNodeIter->right_child;
    }

}

// Checks Whether The Whole Tree Is Empty Or Not
bool IsTreeEmptyBST(const struct BinarySearchTree* bst)
{
    return (bst == NULL);
}

// Checks Whether A Single Tree Node Is Empty Or Not
bool IsNodeEmptyBST(const struct tree_node* trNode)
{
    return (trNode == NULL);
}

// Isolating The Node Pointers (Set All Pointers To NULL)
struct tree_node* IsolateSingleNodeBST (struct tree_node* trNode)
{
    trNode->right_child = NULL;
    trNode->left_child  = NULL;

    if (trNode->CVALData != NULL)
    {
        free(trNode->CVALData);
        trNode->CVALData = NULL;
    }
    else
        trNode->CVALData = NULL;

    return trNode;
}

// PreOrder Transversal
void PreorderTransversalBST (const struct BinarySearchTree* BST)
{
    // Verifying The Existence Of BST
    if (IsTreeEmptyBST(BST) || IsNodeEmptyBST(BST->Root))
    {
        printf ("The Tree Is Empty!");
        return;
    }
    // Perform PreOrder Transversal On A Certain SubTree (Here The Main Root!)
    PreOrderSubTreeBST (BST->Root);
}

// Evaluate The Preorder Transversal For A SubTree
void PreOrderSubTreeBST (const struct tree_node* trNode)
{
    // Verifying The Existence Of BST Node
    if (IsNodeEmptyBST(trNode)) return;

    // Transverse Over The Tree
    InfoNodeBST (trNode);
    PreOrderSubTreeBST(trNode->left_child);
    PreOrderSubTreeBST(trNode->right_child);
}

// Create Single BST Node
struct tree_node* CreateSingleBSTNode (const struct tree_node* lNode, const struct tree_node* rNode, const char* CVALchr)
{
    struct tree_node* trNode = (struct tree_node*) malloc (sizeof(struct tree_node));
    trNode->right_child = (struct tree_node*) rNode;
    trNode->left_child  = (struct tree_node*) lNode;
    trNode->CVALData    = (char*) CVALchr;

    return trNode;
}

// Allocate Tree
struct BinarySearchTree* AllocateBST (const size_t InitNodeCount, const size_t SubsNodeCount)
{
    // Create Tree Object and Set The Main Tree Features
    struct BinarySearchTree* BST  =
            (struct BinarySearchTree*) malloc (sizeof(struct BinarySearchTree));

    BST->PoolCapacity = InitNodeCount;
    BST->FutureCapAdd = SubsNodeCount;

    // Create The Tree Root
    BST->Root     = NULL; // CreateSingleBSTNode(NULL, NULL, NULL);

    // Create Tree Reserved Nodes In A Linked-List Format
    BST->Reserved = CreateSingleBSTNode(NULL, NULL, NULL);
    BST->Reserved->CVALData = (char*) calloc(12, sizeof(char) );

    // Initialize The Reserved Nodes (Pool)
    struct tree_node* trIterator = BST->Reserved;
    struct tree_node* newNodeAdd;
    for (int i = 0; i < BST->PoolCapacity-1; i++)
    {
        newNodeAdd = CreateSingleBSTNode (trIterator, NULL, NULL);
        trIterator->right_child = newNodeAdd;
        trIterator              = newNodeAdd;
    }
    return BST;
}

// ReAllocate Tree
struct BinarySearchTree* ReAllocateBST (struct BinarySearchTree* BST)
{
    // Verifying The Existence Of BST
    if (IsTreeEmptyBST(BST) || IsNodeEmptyBST(BST->Root)) return NULL;

    // Create Tree Reserved Nodes In A Linked-List Format
    BST->Reserved = CreateSingleBSTNode(NULL, NULL, NULL);

    // Create Tree Reserved Nodes (Pool)
    struct tree_node* trIterator = BST->Reserved;
    struct tree_node* newNodeAdd;
    for (int i = 0; i < BST->FutureCapAdd-1; i++)
    {
        newNodeAdd = CreateSingleBSTNode (trIterator, NULL, NULL);
        trIterator->right_child = newNodeAdd;
        trIterator              = newNodeAdd;
    }
    // Update The Tree Pool Size
    BST->PoolCapacity += BST->FutureCapAdd;

    return BST;
}

// Get Node From Pool
struct tree_node* PoolOutBST (struct BinarySearchTree* BST)
{
    // Verifying The Existence Of BST
    if (IsTreeEmptyBST(BST) ) return NULL;

    // If The Pool Is Empty, Reallocate The Pool And Continue
    if ( IsNodeEmptyBST(BST->Reserved) ) BST = ReAllocateBST (BST);

    // Receive Node From Pool And Isolate
    struct tree_node* trNode = BST->Reserved;

    // Update The Next Reserved Node In The Pool QUEUE As The Reserved Node And Setup
    BST->Reserved = BST->Reserved->right_child;
    if ( !IsNodeEmptyBST(BST->Reserved) ) BST->Reserved->left_child = NULL;

    // Isolate The Selected Node
    trNode = IsolateSingleNodeBST (trNode);
    trNode->CVALData = (char*) calloc(12, sizeof(char) );

    return trNode;
}

// Insert CVAL Key
struct BinarySearchTree* InsertNodeBST (struct BinarySearchTree* BST, const char* cvalkey)
{
    // Verifying The Existence Of BST
    if (IsTreeEmptyBST(BST)) return NULL;

    // If it Is The First Node
    if ( IsNodeEmptyBST(BST->Root) )
    {
        BST->Root = PoolOutBST(BST);
        memcpy(BST->Root->CVALData, cvalkey, 12);
        return BST;
    }

    // Allocating The Node At The Appropriate Position
    int res;
    struct tree_node* iterPtrParent;
    struct tree_node* iterPtr = BST->Root;;
    while ( !IsNodeEmptyBST(iterPtr) )
    {
        iterPtrParent = iterPtr;
        res = memcmp(cvalkey,iterPtr->CVALData, 12);
        if      (res > 0) iterPtr = iterPtr->right_child;
        else if (res < 0) iterPtr = iterPtr->left_child;
        else return BST;
    }

    res = memcmp(cvalkey,iterPtrParent->CVALData, 12);

    // Insert The Node
    if ( res > 0 )
    {
        iterPtrParent->right_child = PoolOutBST(BST);
        memcpy(iterPtrParent->right_child->CVALData, cvalkey, 12);
    }
    else
    {
        iterPtrParent->left_child = PoolOutBST(BST);
        memcpy(iterPtrParent->left_child->CVALData, cvalkey, 12);
    }

    return BST;
}

// Returns True/False Whether There Is a Key Or Not
bool IsKeyAvailableBST(const struct BinarySearchTree* BST, const char* cvalKey)
{
    if (IsTreeEmptyBST(BST)) return false;
    return ( SearchKeyBST(BST->Root, cvalKey) != NULL);
}

// Search In Binary Tree
struct tree_node* SearchKeyBST (const struct tree_node* trNode, const char* cvalKey)
{
    // If Node Not Exists On This Leaf!
    if (IsNodeEmptyBST(trNode) || cvalKey == NULL) return NULL;
    // Else Comparing The Key With The Tree Node Values:
    int res = memcmp(cvalKey,trNode->CVALData, 12);
    if      (res == 0) return (struct tree_node*) trNode;
    else if (res  > 0) return SearchKeyBST(trNode->right_child, cvalKey);
    else if (res  < 0) return SearchKeyBST(trNode->left_child,  cvalKey);
}

// Get Min Node Ptr
struct tree_node* GetMinKeyBST (const struct tree_node* trNode)
{
    // Check For NULL
    if (IsNodeEmptyBST(trNode)) return NULL;
    // Find The Most Left Element
    while (trNode->left_child != NULL) trNode = trNode->left_child;
    return (struct tree_node*) trNode;

}

// Send Node To Pool
struct BinarySearchTree* PoolInBST (struct BinarySearchTree* BST, struct tree_node* removedNode)
{
    // Verifying The Existence Of BST
    if (IsTreeEmptyBST(BST) || IsNodeEmptyBST(removedNode) || IsNodeEmptyBST(BST->Root)) return NULL;

    // Isolate The Removed Node From Its Root Neighbors
    removedNode = IsolateSingleNodeBST (removedNode);

    // Select The First Reserved Node
    struct tree_node* trNode = BST->Reserved;

    // Select The Removed Node As The Previous (left) Link Of The First Node
    trNode->left_child       = removedNode;
    // Select The First Node As The Next (right) Link Of The Removed Node
    removedNode->right_child = trNode;
    // Select The Removed Node As The New First Pool Node
    removedNode->left_child = NULL;
    BST->Reserved = removedNode;

    return BST;
}

// Specify Whether A Node Is A Leaf Or Not!
bool IsNodeLeafBST (const struct tree_node* trNode)
{
    if (IsNodeEmptyBST(trNode) ) return false;
    return ( IsNodeEmptyBST(trNode->left_child) &&
             IsNodeEmptyBST(trNode->right_child) );
}

// Sending A Node To The Pool
struct tree_node* SearchAndsDeleteNodeBST (struct tree_node* trNode, const char* cvalkey)
{
    // Verifying The Existence Of BST
    if (IsNodeEmptyBST(trNode)) return NULL;

    int res = memcmp(cvalkey, trNode->CVALData,12);

    if (res>0) {
        trNode->right_child =
                SearchAndsDeleteNodeBST(trNode->right_child, cvalkey);
    }
    else if(res<0) {
        trNode->left_child =
                SearchAndsDeleteNodeBST(trNode->left_child, cvalkey);
    }
    else
    {
        // No Children
        if( IsNodeLeafBST (trNode) )
        {
            FreeSingleNodeBST(trNode);
            return NULL;
        }

        // One Child
        else if( IsNodeEmptyBST(trNode->right_child) || IsNodeEmptyBST(trNode->left_child)  )
        {
            struct tree_node *temp;
            if ( trNode->left_child == NULL ) temp = trNode->right_child;
            else                              temp = trNode->left_child;
            FreeSingleNodeBST(trNode);
            return temp;
        }

        // Two Children
        else
        {
            struct tree_node *temp = GetMinKeyBST(trNode->right_child);
            trNode->CVALData    = temp->CVALData;
            trNode->right_child =
                    SearchAndsDeleteNodeBST(trNode->right_child, temp->CVALData);
        }

    }

    return trNode;
}

// Free A Single Node From BST
bool FreeSingleNodeBST (struct tree_node* trNode)
{
    // Verifying The Existence Of The Given Node
    if (IsNodeEmptyBST(trNode)) return false;

    IsolateSingleNodeBST(trNode);
    free (trNode);
    trNode = NULL;

    return true;
}

bool DeleteAllBST (struct BinarySearchTree* BST)
{
    if (IsTreeEmptyBST(BST)) return false;
    DeleteSubTree(BST->Reserved);
    DeleteSubTree(BST->Root);
    BST->Root = NULL;
    BST->Reserved = NULL;
    BST->PoolCapacity = 0;
    BST->FutureCapAdd = 0;
    return true;
}

bool DeleteSubTree (struct tree_node* trNode)
{
    if (IsNodeEmptyBST(trNode)) return false;

    FreeSingleNodeBST(trNode->right_child);
    FreeSingleNodeBST(trNode->left_child);
    FreeSingleNodeBST(trNode);
    return true;
}


const char* RandomCVALGen()
{
    char* strCVAL = (char*) calloc(12, sizeof(char) );

    // Fixed CHARS
    strCVAL[0] = 'I';
    strCVAL[1] = 'R';
    // Single CHAR
    strCVAL[2] = (char)(65 + rand()%26);
    // Single Number In CHAR Format
    strCVAL[3] = IntToChar(rand()%10);
    // 4 CHARS
    for (int i = 4; i < 8; ++i)
        strCVAL[i] = (char)(65 + rand()%26);
    // 4 Numbers In CHAR Format
    for (int i = 8; i < 12; ++i)
        strCVAL[i] = IntToChar(rand()%10);

    //printf("%s\n", strCVAL);

    return (const char*) strCVAL;
}


/*


bool SearchAndsDeleteNodeBST (struct BinarySearchTree* BST,  const char* cvalkey)
{
    // Verifying The Existence Of BST
    if (IsTreeEmptyBST(BST) || IsNodeEmptyBST(BST->Root)) return 0;

    // Search For CVAL
    struct tree_node* targetNode = SearchKeyBST(BST->Root, cvalkey);

    // Condition (1): Node Not Found
    if ( IsNodeEmptyBST(targetNode) ) return false;

    // Condition (2): Node Is Leaf
    if ( IsNodeLeafBST(targetNode) )
    {
        // Modify parent Pointer To Point To NULL
        if ( IsNodeLeftChildBST(targetNode) )
            targetNode->parent->left_child  = NULL;
        else
            targetNode->parent->right_child = NULL;

        // Transfer Node To Pool
        Root2PoolBST (BST, targetNode);
        return true;
    }

    // Condition (3): Node Is Internal But Has Only Right Child
    else if( IsNodeEmptyBST(targetNode->left_child) )
    {
        // Modify parent Pointer To Point To Right Child
        if ( IsNodeLeftChildBST(targetNode) )
            targetNode->parent->left_child  = targetNode->right_child;
        else
            targetNode->parent->right_child = targetNode->right_child;

        // Modify Child Pointer To Point To The Grand-Parent
        targetNode->right_child->parent = targetNode->parent;

        // Transfer Node To Pool
        Root2PoolBST (BST, targetNode);
        return true;
    }

    // Condition (4): Node Is Internal But Has Only Left Child
    else if( IsNodeEmptyBST(targetNode->right_child) )
    {
        // Modify parent Pointer To Point To Left Child
        if ( IsNodeLeftChildBST(targetNode) )
            targetNode->parent->left_child  = targetNode->left_child;
        else
            targetNode->parent->right_child = targetNode->left_child;

        // Modify Child Pointer To Point To The Grand-Parent
        targetNode->left_child->parent = targetNode->parent;

        // Transfer Node To Pool
        Root2PoolBST (BST, targetNode);
        return true;
    }

    // Condition (5): Node Is Internal And Has Both Children
    else
    {
        // First LVL: Replace The Right Of The Min With It
        struct tree_node* minPtr = GetMinKeyBST (targetNode->right_child);

        // Modify parent Pointer To Point To Right Child
        if ( IsNodeLeftChildBST(minPtr) )
            minPtr->parent->left_child  = minPtr->right_child;
        else
            minPtr->parent->right_child = minPtr->right_child;

        // Modify Child Pointer To Point To The Grand-Parent
        minPtr->right_child->parent = minPtr->parent;

        // Transfer Node To Pool
        Root2PoolBST (BST, targetNode);

        return true;
    }

}

str


struct tree_node* new_node(const char* x, const int number_of_nodes)
{
    struct tree_node *p;
    unsigned int node_index = number_of_nodes%50;
    if(node_index || (number_of_nodes==0))
    {
        temp_nodes=malloc_tree(50);
        temp_keys=malloc_chartable(50,12);
    }
    p =temp_nodes[node_index];
    p->data=temp_keys[node_index];
    memcpy(p->data,x,12);
    p->left_child = NULL;
    p->right_child = NULL;
    return p;
}



struct tree_node** malloc_tree (const int number_of_elements)
{
    struct tree_node** table = (struct tree_node**) malloc(number_of_elements * sizeof(struct tree_node*));
    for(int i=0; i<number_of_elements; i++)
        table[i]=  (struct tree_node*) malloc(sizeof(struct tree_node));
    return table;
}

char** malloc_chartable (const int number_of_elements, const int size_of_elements)
{
    char **table = (char**) malloc(number_of_elements * sizeof(char*));
    for(int i=0; i<number_of_elements; i++)
        table[i]=  (char*) malloc(size_of_elements*sizeof(char));
    return table;
}

int** malloc_inttable (const int number_of_elements, const int size_of_elements)
{
    int **table = (int**) malloc(number_of_elements * sizeof(int*));
    for(int i=0; i<number_of_elements; i++)
        table[i]=  (int*) malloc(size_of_elements*sizeof(int));
    return table;
}


*/

