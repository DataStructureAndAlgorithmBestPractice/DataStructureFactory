#include "LinkedList.h"

/* Allocation API For CVAL Manipulations */
struct ContainerData* CVAL2ContainerData (const char* RefChr, size_t StrCount)
{
    // Return If NULL String
    if (RefChr == NULL) return NULL;

    // Allocate The ContainerData
    struct ContainerData* CVAL_ContainerData =
            (struct ContainerData* ) calloc(1, sizeof(struct ContainerData));

    // Add One More bit for NULL Character At The String End
    StrCount+=1;

    // Process The input CVAL String
    CVAL_ContainerData->StrData = (char*) calloc(StrCount, sizeof(char));
    memcpy(CVAL_ContainerData->StrData, RefChr, StrCount-1);

    // Define a NULL At the String End
    CVAL_ContainerData->StrData[StrCount-1] = '\0';
    return CVAL_ContainerData;
}

/* Visualize Data Container (Currently CVAL) */
void PrintContainerData (const struct ContainerData* dt)
{
    if (dt != NULL){
        printf("String   Pointer: %p\n",dt->StrData);
        printf("String: %s\n",dt->StrData);
    }

    else            printf("(nil)\n");
}

/* Free ContainerData Data (Currently CVAL) */
void FreeContainerData (struct ContainerData* dt)
{
    if (dt->StrData != NULL) free(dt->StrData);
    free(dt);
    dt = NULL;
}

/* Checks If LinkedList Is Empty */
bool IsEmptyLinkedList(const LinkedList* Root)
{
    return (Root == NULL);
}

/* Constructing A Linked-List Node */
struct LinkedListNode* CreateNodeLinkedList (struct LinkedListNode* prevPtr, struct LinkedListNode* nextPtr)
{
    // Node Creation
    struct LinkedListNode* newNode = (struct LinkedListNode*) calloc(1,sizeof(struct LinkedListNode));
    // Node Data Allocation
    newNode->next = nextPtr;
    newNode->prev = prevPtr;
    newNode->data = NULL;
    return newNode;
}

/* Initiating The Linked-List */
LinkedList* CreateLinkedList (size_t LLInitialCapacity, size_t LLAppendSize, size_t LLStrSize)
{
    // Creating The First/Last/Filled Node Pointer
    LinkedList* RLL = (LinkedList*) calloc(1,sizeof(LinkedList));
    RLL->RootNode             = NULL;
    RLL->RearNode             = NULL;
    RLL->FilledNode           = NULL;
    // Initializing All Sizes
    RLL->SizeLinkedList       = 0;
    RLL->CapacityLinkedList   = LLInitialCapacity;
    RLL->AppendSizeLinkedList = LLAppendSize;
    RLL->ContainerStrSize     = LLStrSize;
    return RLL;
}

/* Allocating Pool Of Memory Linked-List Elements */
LinkedList* AllocateLinkedList (size_t LLInitialCapacity, size_t LLAppendSize, size_t LLStrSize)
{
    // Create LinkList
    LinkedList* RLL = CreateLinkedList (LLInitialCapacity, LLAppendSize, LLStrSize);

    // Creating The First Node And Associate The First Pointer
    RLL->RootNode = CreateNodeLinkedList(NULL, NULL);

    // Creating Other Nodes (At the Linked-List Beginning)
    struct LinkedListNode* PrevPtrIter = RLL->RootNode;
    struct LinkedListNode* newNodeIter;
    for (int i = 1; i < LLInitialCapacity; i++)
    {
        newNodeIter = CreateNodeLinkedList(PrevPtrIter, NULL);
        PrevPtrIter->next = newNodeIter;
        PrevPtrIter = newNodeIter;
    }
    // Set The Node Ready For Push
    RLL->FilledNode = RLL->RootNode;
    RLL->RearNode   = newNodeIter;

    return RLL;
}

/* Free Single Node Linked-List Elements */
void FreeSingleNodeLinkedList (struct LinkedListNode* LL)
{
    // Free Inner Data Information
    if (LL->data != NULL) FreeContainerData (LL->data);
    // Pointing To NULL For The Current Node
    LL->next = NULL;
    LL->prev = NULL;
    // Free Linked-List Element
    free(LL);
}

/* Free All Linked-List Elements */
void FreeAllNodesLinkedList (LinkedList* RLL)
{
    // Checks The Existence Of Node
    if (IsEmptyLinkedList(RLL) || RLL->RootNode == NULL) return;

    // Removing Nodes From One After Another And Pointing To NULL
    struct LinkedListNode* ItrPtrCurr = RLL->RootNode;
    struct LinkedListNode* ItrPtrNext = ItrPtrCurr->next;
    while (ItrPtrNext != NULL)
    {
        FreeSingleNodeLinkedList(ItrPtrCurr);
        ItrPtrCurr = ItrPtrNext;
        ItrPtrNext = ItrPtrNext->next;
        RLL->CapacityLinkedList--;
    }
    FreeSingleNodeLinkedList(ItrPtrCurr);
    RLL->CapacityLinkedList--;

    RLL->SizeLinkedList = 0;
    // Setting The Pointers To NULL
    RLL->RootNode   = NULL;
    RLL->RearNode   = NULL;
    RLL->FilledNode = NULL;
    free(RLL);
}

/* Reallocate Linked-List Elements */
void ReAllocateLinkedList (LinkedList* RLL)
{
    // Find The Old Last Element
    struct LinkedListNode* PrevPtr = RLL->RearNode;

    // Creating Other Nodes (Add New Elements At The Linked-List End)
    struct LinkedListNode* newNode;
    for (int i = 0; i < RLL->AppendSizeLinkedList; i++)
    {
        newNode       = CreateNodeLinkedList(PrevPtr, NULL);
        PrevPtr->next = newNode;
        PrevPtr       = newNode;
    }
    RLL->CapacityLinkedList += RLL->AppendSizeLinkedList;
    RLL->RearNode            = newNode;
}

/* Set A Single Linked-List Element */
void PushValueLinkedList (LinkedList* RLL, const char* cvalstr)
{
    // Initiating The Linked-List If Not Exists
    if (IsEmptyLinkedList(RLL) || RLL->CapacityLinkedList==0) return;

    // Add If Size Exceeds Current Capacity When Pushing
    if ( RLL->FilledNode == RLL->RearNode ) ReAllocateLinkedList (RLL);

    // Push Node
    RLL->FilledNode->data = CVAL2ContainerData (cvalstr, RLL->ContainerStrSize);
    RLL->SizeLinkedList += 1;
    RLL->FilledNode = RLL->FilledNode->next;
}

/* Search For A Specific Key Inside The Linked-List, Return NULL If Not Found */
struct LinkedListNode* SearchKeyLinkedList (LinkedList* RLL, const char* cvalstr)
{
    // Initiating The Linked-List If Not Exists
    if (IsEmptyLinkedList(RLL)) return NULL;
    struct LinkedListNode* ItrPtrFWD = RLL->RootNode;
    struct LinkedListNode* ItrPtrBWD = RLL->FilledNode->prev;

    // Convert CVAL char To Container Data
    struct ContainerData* cd = CVAL2ContainerData (cvalstr, RLL->ContainerStrSize);

    while (ItrPtrFWD != ItrPtrBWD)
    {
        if ( strcmp(cd->StrData, ItrPtrFWD->data->StrData ) == 0) return ItrPtrFWD;
        if ( strcmp(cd->StrData, ItrPtrBWD->data->StrData ) == 0) return ItrPtrBWD;

        ItrPtrFWD = ItrPtrFWD->next;
        ItrPtrBWD = ItrPtrBWD->prev;
    }
    FreeContainerData(cd);
    return NULL;
}

/* Delete First Node Of The Linked-List, */
struct LinkedListNode* DeleteFirstNodeLinkList (LinkedList* RLL, struct LinkedListNode* FNodePtr)
{
    // Editing The Root Pointer
    struct LinkedListNode* NewFirstPtr = FNodePtr->next;
    RLL->RootNode = NewFirstPtr;

    // Removing The Connection With The Previous First Node
    if (NewFirstPtr != NULL) NewFirstPtr->prev = NULL;

    // Remove The Popped Node Connections
    FNodePtr->next = NULL;
    return FNodePtr;
}

/* Delete Mid Node Of The Linked-List, */
struct LinkedListNode* DeleteMidNodeLinkList (LinkedList* RLL, struct LinkedListNode* MidNodePtr)
{
    // Adjust The Adjacent Pointers
    if (MidNodePtr->prev != NULL) MidNodePtr->prev->next = MidNodePtr->next;
    if (MidNodePtr->next != NULL) MidNodePtr->next->prev = MidNodePtr->prev;

    // Remove The Popped Node Connections
    MidNodePtr->prev = NULL;
    MidNodePtr->next = NULL;
    return MidNodePtr;
}

/* Delete Last Node Of The Linked-List, */
struct LinkedListNode* DeleteRearNodeLinkList (LinkedList* RLL, struct LinkedListNode* RearNodePtr)
{
    // Editing The Root Pointer
    struct LinkedListNode* NewRearPtr = RearNodePtr->prev;
    RLL->RearNode = NewRearPtr;
    // Removing The connection With The Last Node
    if (NewRearPtr != NULL) NewRearPtr->next = NULL;
    // Remove The Popped Node Connections
    RearNodePtr->prev = NULL;
    RearNodePtr->next = NULL;
    // Edit Size Counters
    RLL->CapacityLinkedList--;
    RLL->SizeLinkedList--;
    return RearNodePtr;
}

/* Pop Node From Any Location Of The Linked-List, */
struct LinkedListNode* PopNodeFromAnyLocationLinkList (LinkedList* RLL, struct LinkedListNode* NodePtr)
{
    if (NodePtr == NULL) return false;
    struct LinkedListNode* PoppedNodePtr;
    // Remove Based On The Position
    if      (NodePtr == RLL->RootNode) PoppedNodePtr = DeleteFirstNodeLinkList (RLL, NodePtr);
    else if (NodePtr == RLL->RearNode) PoppedNodePtr = DeleteRearNodeLinkList  (RLL, NodePtr);
    else                               PoppedNodePtr = DeleteMidNodeLinkList   (RLL, NodePtr);
    return PoppedNodePtr;
}

/* Search For A Specific Key Inside The Linked-List, Return 0 If Not Found */
bool DeleteNodeLinkList (LinkedList* RLL, const char* cvalstr)
{
    struct LinkedListNode* NodePtr = SearchKeyLinkedList (RLL, cvalstr);
    if (NodePtr == NULL)    return false;

    FreeSingleNodeLinkedList(PopNodeFromAnyLocationLinkList (RLL, NodePtr));
    RLL->CapacityLinkedList--;
    RLL->SizeLinkedList--;
    return true;
}

/* Print All Linked-List Elements*/
void INFOLinkedList (const LinkedList* RLL)
{
    if ( IsEmptyLinkedList(RLL) ) return;

    int i = 0;
    struct LinkedListNode* itrPtr = RLL->RootNode;
    printf("\n***********************************************\n");
    printf("General INFO:\n");
    printf("Root   Pointer: %p\n",        RLL->RootNode);
    printf("Rear   Pointer: %p\n",        RLL->RearNode);
    printf("Filled Pointer: %p\n",        RLL->FilledNode);
    printf("Linked-List Size: %zu\n",     RLL->SizeLinkedList);
    printf("Linked-List Capacity: %zu\n", RLL->CapacityLinkedList);
    printf("-----------------------------------------------\n");

    while (i != RLL->CapacityLinkedList) //( itrPtr != RLL->FilledNode)
    {
        printf("Number(%d):\n", i);
        printf("Previous Pointer: %p\n", itrPtr->prev);
        printf("Current  Pointer: %p\n", itrPtr);
        printf("Next     Pointer: %p\n", itrPtr->next);
        printf("Data     Pointer: %p\n", itrPtr->data);
        PrintContainerData (itrPtr->data);
        itrPtr = itrPtr->next;
        i++;
    }
    printf("\n***********************************************\n");

}


